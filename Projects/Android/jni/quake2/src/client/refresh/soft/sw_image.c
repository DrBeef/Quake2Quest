/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "header/local.h"

extern cvar_t *sw_retexturing;

#define	MAX_RIMAGES	1024
static image_t		r_images[MAX_RIMAGES];
static int		numr_images;


/*
===============
R_ImageList_f
===============
*/
void
R_ImageList_f (void)
{
	int		i;
	image_t	*image;
	int		texels;

	R_Printf(PRINT_ALL, "------------------\n");
	texels = 0;

	for (i=0, image=r_images ; i<numr_images ; i++, image++)
	{
		char *in_use = "";

		if (image->registration_sequence == registration_sequence)
		{
			in_use = "*";
		}

		if (image->registration_sequence <= 0)
			continue;
		texels += image->width*image->height;
		switch (image->type)
		{
		case it_skin:
			R_Printf(PRINT_ALL, "M");
			break;
		case it_sprite:
			R_Printf(PRINT_ALL, "S");
			break;
		case it_wall:
			R_Printf(PRINT_ALL, "W");
			break;
		case it_pic:
			R_Printf(PRINT_ALL, "P");
			break;
		default:
			R_Printf(PRINT_ALL, " ");
			break;
		}

		R_Printf(PRINT_ALL,  " %3i %3i : %s %s\n",
			image->width, image->height, image->name,
			in_use);
	}
	R_Printf(PRINT_ALL, "Total texel count: %i\n", texels);
}

//=======================================================

static image_t *
R_FindFreeImage (void)
{
	image_t		*image;
	int			i;

	// find a free image_t
	for (i=0, image=r_images ; i<numr_images ; i++,image++)
	{
		if (!image->registration_sequence)
			break;
	}
	if (i == numr_images)
	{
		if (numr_images == MAX_RIMAGES)
			ri.Sys_Error(ERR_DROP, "%s: Max images", __func__);
		numr_images++;
	}
	image = &r_images[i];

	return image;
}

static void
R_ImageShrink(const unsigned char* src, unsigned char *dst, int width, int realwidth, int height, int realheight)
{
	int x, y;
	float xstep, ystep;

	xstep = (float)height / realheight;
	ystep = (float)width / realwidth;

	for (y=0; y<realheight; y++)
	{
		for (x=0; x<realwidth; x++)
		{
			// inplace update
			dst[x + y * realwidth] = src[(int)(x * xstep)  + (int)(y * ystep) * width];
		}
	}
}

static void
R_RestoreMips(image_t *image, int min_mips)
{
	int i;

	for (i=min_mips+1; i<NUM_MIPS; i++)
	{
		R_ImageShrink(image->pixels[i-1], image->pixels[i],
			      image->height / (1 << (i - 1)), image->height / (1 << i),
			      image->width / (1 << (i - 1)), image->width / (1 << i));
	}
}

static size_t
R_GetImageMipsSize(size_t mip1_size)
{
	size_t full_size = 0;
	int i;

	for (i=0; i<NUM_MIPS; i++)
	{
		full_size += mip1_size >> (i * 2);
	}
	return full_size;
}

static void
R_RestoreImagePointers(image_t *image, int min_mips)
{
	int i;

	for (i=min_mips+1; i<NUM_MIPS; i++)
	{
		image->pixels[i] = image->pixels[i - 1] + (
			image->width * image->height / (1 << ((i - 1) * 2)));
	}
}

/*
================
R_LoadPic

================
*/
static image_t *
R_LoadPic (char *name, byte *pic, int width, int height, imagetype_t type)
{
	image_t	*image;
	size_t	i, size, full_size;

	if (!pic)
		return NULL;

	image = R_FindFreeImage();
	if (strlen(name) >= sizeof(image->name))
		ri.Sys_Error(ERR_DROP, "%s: '%s' is too long", __func__, name);
	strcpy (image->name, name);
	image->registration_sequence = registration_sequence;

	image->width = width;
	image->height = height;
	image->type = type;

	size = width * height;
	full_size = R_GetImageMipsSize(size);
	image->pixels[0] = malloc(full_size);
	image->transparent = false;
	for (i=0 ; i<size ; i++)
	{
		if (pic[i] == 255)
		{
			image->transparent = true;
			break;
		}
	}

	memcpy(image->pixels[0], pic, size);
	// restore mips
	R_RestoreImagePointers(image, 0);
	// restore everything from first image
	R_RestoreMips(image, 0);
	return image;
}

/*
================
R_LoadWal
================
*/
static image_t *
R_LoadWal (char *name, imagetype_t type)
{
	miptex_t	*mt;
	int		ofs;
	image_t		*image;
	size_t		size, file_size;

	file_size = ri.FS_LoadFile (name, (void **)&mt);
	if (!mt)
	{
		R_Printf(PRINT_ALL, "R_LoadWal: can't load %s\n", name);
		return r_notexture_mip;
	}

	if (file_size < sizeof(miptex_t))
	{
		R_Printf(PRINT_ALL, "R_LoadWal: can't load %s, small header\n", name);
		ri.FS_FreeFile((void *)mt);
		return r_notexture_mip;
	}

	image = R_FindFreeImage ();
	strcpy (image->name, name);
	image->width = LittleLong (mt->width);
	image->height = LittleLong (mt->height);
	image->type = type;
	image->registration_sequence = registration_sequence;
	ofs = LittleLong(mt->offsets[0]);
	size = R_GetImageMipsSize(image->width * image->height);

	if ((ofs <= 0) || (image->width <= 0) || (image->height <= 0) ||
	    ((file_size - ofs) / image->width < image->height))
	{
		R_Printf(PRINT_ALL, "LoadWal: can't load %s, small body\n", name);
		ri.FS_FreeFile((void *)mt);
		return r_notexture_mip;
	}

	image->pixels[0] = malloc (size);
	R_RestoreImagePointers(image, 0);

	if (size > (file_size - ofs))
	{
		memcpy(image->pixels[0], (byte *)mt + ofs, file_size - ofs);
		// looks short, restore everything from first image
		R_RestoreMips(image, 0);
	}
	else
	{
		memcpy(image->pixels[0], (byte *)mt + ofs, size);
	}

	ri.FS_FreeFile((void *)mt);

	return image;
}

static unsigned char *d_16to8table; // 16 to 8 bit conversion table

static void
R_Convert32To8bit(unsigned char* pic_in, unsigned char* pic_out, size_t size)
{
	size_t i;

	if (!d_16to8table)
		return;

	for(i=0; i<size; i++)
	{
		unsigned int r, g, b, c;

		r = ( pic_in[i * 4 + 0] >> 3 ) & 31;
		g = ( pic_in[i * 4 + 1] >> 2 ) & 63;
		b = ( pic_in[i * 4 + 2] >> 3 ) & 31;

		c = r | ( g << 5 ) | ( b << 11 );

		pic_out[i] = d_16to8table[c & 0xFFFF];
	}
}

static image_t	*
R_LoadHiColorImage(char *name, const char* namewe, const char *ext, imagetype_t type)
{
	image_t	*image = NULL;
	byte *pic = NULL;
	int realwidth = 0, realheight = 0;
	int width = 0, height = 0;

	if (strcmp(ext, "pcx") == 0)
	{
		/* Get size of the original texture */
		GetPCXInfo(name, &realwidth, &realheight);
	}
	else if (strcmp(ext, "wal") == 0)
	{
		/* Get size of the original texture */
		GetWalInfo(name, &realwidth, &realheight);
	}

	/* try to load a tga, png or jpg (in that order/priority) */
	if (  LoadSTB(namewe, "tga", &pic, &width, &height)
	   || LoadSTB(namewe, "png", &pic, &width, &height)
	   || LoadSTB(namewe, "jpg", &pic, &width, &height) )
	{
		if (width >= realwidth && height >= realheight)
		{
			// resulted image
			byte* pic8 = NULL;
			// resulted image memory size
			size_t size8;

			if (realheight == 0 || realwidth == 0)
			{
				realheight = height;
				realwidth = width;
			}

			size8 = R_GetImageMipsSize(width * height);
			pic8 = malloc(size8);

			if (width != realwidth || height != realheight)
			{
				// temporary place for shrinked image
				byte* pic32 = NULL;
				// temporary image memory size
				size_t size32;

				// resize image
				size32 = width * height * 4;
				pic32 = malloc(size32);

				if (ResizeSTB(pic, width, height,
					      pic32, realwidth, realheight))
				{
					R_Convert32To8bit(pic32, pic8, realwidth * realheight);
					image = R_LoadPic(name, pic8, realwidth, realheight, type);
				}
				free(pic32);
			}
			else
			{
				R_Convert32To8bit(pic, pic8, width * height);
				image = R_LoadPic(name, pic8, width, height, type);
			}
			free(pic8);
		}
	}

	if (!pic)
	{
		free(pic);
	}

	return image;
}

static image_t	*
R_LoadImage(char *name, const char* namewe, const char *ext, imagetype_t type)
{
	image_t	*image = NULL;

	// with retexturing and not skin
	if (sw_retexturing->value)
	{
		image = R_LoadHiColorImage(name, namewe, ext, type);
	}

	if (!image)
	{
		if (strcmp(ext, "pcx") == 0)
		{
			byte *pic = NULL;
			byte	*palette = NULL;
			int width = 0, height = 0;

			LoadPCX (name, &pic, &palette, &width, &height);
			if (!pic)
				return NULL;
			image = R_LoadPic(name, pic, width, height, type);
			if (palette)
			{
				free(palette);
			}
			if (!pic)
			{
				free(pic);
			}
		}
		else if (strcmp(ext, "wal") == 0)
		{
			image = R_LoadWal(name, type);
		}
	}

	return image;
}

/*
===============
R_FindImage

Finds or loads the given image
===============
*/
image_t	*
R_FindImage(char *name, imagetype_t type)
{
	image_t	*image;
	int	i, len;
	char *ptr;
	char namewe[256];
	const char* ext;

	if (!name)
	{
		return NULL;
	}

	ext = COM_FileExtension(name);
	if(!ext[0])
	{
		/* file has no extension */
		return NULL;
	}

	len = strlen(name);

	/* Remove the extension */
	memset(namewe, 0, 256);
	memcpy(namewe, name, len - (strlen(ext) + 1));

	if (len < 5)
	{
		return NULL;
	}

	/* fix backslashes */
	while ((ptr = strchr(name, '\\')))
	{
		*ptr = '/';
	}

	// look for it
	for (i=0, image=r_images ; i<numr_images ; i++,image++)
	{
		if (!strcmp(name, image->name))
		{
			image->registration_sequence = registration_sequence;
			return image;
		}
	}

	//
	// load the pic from disk
	//
	return R_LoadImage(name, namewe, ext, type);
}

/*
================
R_FreeUnusedImages

Any image that was not touched on this registration sequence
will be freed.
================
*/
void
R_FreeUnusedImages (void)
{
	int		i;
	image_t	*image;

	for (i=0, image=r_images ; i<numr_images ; i++, image++)
	{
		if (image->registration_sequence == registration_sequence)
		{
			continue; // used this sequence
		}
		if (!image->registration_sequence)
			continue; // free texture
		if (image->type == it_pic)
			continue; // don't free pics
		// free it
		free (image->pixels[0]); // the other mip levels just follow
		memset(image, 0, sizeof(*image));
	}
}

static struct texture_buffer {
	image_t	image;
	byte	buffer[4096];
} r_notexture_buffer;

/*
==================
R_InitTextures
==================
*/
static void
R_InitTextures (void)
{
	int		x,y, m;

	// create a simple checkerboard texture for the default
	r_notexture_mip = &r_notexture_buffer.image;

	r_notexture_mip->width = r_notexture_mip->height = 16;

	r_notexture_mip->pixels[0] = r_notexture_buffer.buffer;
	R_RestoreImagePointers(r_notexture_mip, 0);

	for (m=0 ; m<NUM_MIPS ; m++)
	{
		byte	*dest;

		dest = r_notexture_mip->pixels[m];
		for (y=0 ; y< (16>>m) ; y++)
			for (x=0 ; x< (16>>m) ; x++)
			{
				if (  (y< (8>>m) ) ^ (x< (8>>m) ) )

					*dest++ = 0;
				else
					*dest++ = 0xff;
			}
	}
}

/*
===============
R_InitImages
===============
*/
void
R_InitImages (void)
{
	unsigned char * table16to8;
	registration_sequence = 1;

	d_16to8table = NULL;
	ri.FS_LoadFile("pics/16to8.dat", (void **)&table16to8);

	if ( !table16to8 )
	{
		ri.Sys_Error(ERR_FATAL, "%s: Couldn't load pics/16to8.dat", __func__);
	}
	d_16to8table = malloc(0x10000);
	memcpy(d_16to8table, table16to8, 0x10000);
	ri.FS_FreeFile((void *)table16to8);

	R_InitTextures ();
}

/*
===============
R_ShutdownImages
===============
*/
void
R_ShutdownImages (void)
{
	int	i;
	image_t	*image;

	for (i=0, image=r_images ; i<numr_images ; i++, image++)
	{
		if (!image->registration_sequence)
			continue; // free texture

		// free it
		if (image->pixels[0])
			free(image->pixels[0]); // the other mip levels just follow

		memset(image, 0, sizeof(*image));
	}

	if (d_16to8table)
		free(d_16to8table);
}
