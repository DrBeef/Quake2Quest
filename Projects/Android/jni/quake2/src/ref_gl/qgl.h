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
/*
** QGL.H
*/

#ifndef __QGL_H__
#define __QGL_H__

#ifdef _WIN32
#  include <windows.h>
#endif

#include "../../../gl4es/include/GL/gl.h"

#ifndef SOLARIS
//#include <GL/glext.h>
#endif

qboolean QGL_Init( const char *dllname );
void     QGL_Shutdown( void );

#ifndef APIENTRY
#  define APIENTRY
#endif

extern	void ( APIENTRY * qglPointParameterfEXT)( GLenum param, GLfloat value );
extern	void ( APIENTRY * qglPointParameterfvEXT)( GLenum param, const GLfloat *value );
extern	void ( APIENTRY * qglColorTableEXT)( GLenum, GLenum, GLsizei, GLenum, GLenum, const GLvoid * );

extern	void ( APIENTRY * qglLockArraysEXT) (int , int);
extern	void ( APIENTRY * qglUnlockArraysEXT) (void);

extern	void ( APIENTRY * qglMTexCoord2fSGIS)( GLenum, GLfloat, GLfloat );
extern	void ( APIENTRY * qglSelectTextureSGIS)( GLenum );

extern	void ( APIENTRY * qglActiveTextureARB)( GLenum );
extern	void ( APIENTRY * qglClientActiveTextureARB)( GLenum );

/* deprecated */
#define GL_TEXTURE0_SGIS					0x835E
#define GL_TEXTURE1_SGIS					0x835F

extern int QGL_TEXTURE0, QGL_TEXTURE1; /* ARB/SGIS texture defs */

#ifdef SOLARIS /* these are in glext.h, on platforms that have it */
/*
** extension constants
*/
#define GL_POINT_SIZE_MIN_EXT				0x8126
#define GL_POINT_SIZE_MAX_EXT				0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_EXT	0x8128
#define GL_DISTANCE_ATTENUATION_EXT			0x8129
#endif


#ifdef ANDROID /* these are in glext.h, on platforms that have it */
/*
** extension constants
*/
#define GL_POINT_SIZE_MIN_EXT				0x8126
#define GL_POINT_SIZE_MAX_EXT				0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_EXT	0x8128
#define GL_DISTANCE_ATTENUATION_EXT			0x8129
#endif

#ifdef __sgi
#define GL_SHARED_TEXTURE_PALETTE_EXT		GL_TEXTURE_COLOR_TABLE_SGI
#else
#define GL_SHARED_TEXTURE_PALETTE_EXT		0x81FB
#endif

#endif

