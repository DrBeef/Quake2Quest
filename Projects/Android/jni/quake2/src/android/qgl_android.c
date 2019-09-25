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
** QGL_WIN.C
**
** This file implements the operating system binding of GL to QGL function
** pointers.  When doing a port of Quake2 you must implement the following
** two functions:
**
** QGL_Init() - loads libraries, assigns function pointers, etc.
** QGL_Shutdown() - unloads libraries, NULLs function pointers
*/
#include "../ref_gl/gl_local.h"

typedef struct
{
	//void *OpenGLLib; // instance of OpenGL library

	FILE *log_fp;
} glwstate_t;

static glwstate_t glw_state;


void ( APIENTRY * qglLockArraysEXT)( int, int);
void ( APIENTRY * qglUnlockArraysEXT) ( void );

void ( APIENTRY * qglPointParameterfEXT)( GLenum param, GLfloat value );
void ( APIENTRY * qglPointParameterfvEXT)( GLenum param, const GLfloat *value );
void ( APIENTRY * qglColorTableEXT)( GLenum, GLenum, GLsizei, GLenum, GLenum, const GLvoid * );

void ( APIENTRY * qgl3DfxSetPaletteEXT)( GLuint * );
void ( APIENTRY * qglSelectTextureSGIS)( GLenum );
void ( APIENTRY * qglMTexCoord2fSGIS)( GLenum, GLfloat, GLfloat );
void ( APIENTRY * qglActiveTextureARB) ( GLenum );
void ( APIENTRY * qglClientActiveTextureARB) ( GLenum );


/*
** QGL_Shutdown
**
** Unloads the specified DLL then nulls out all the proc pointers.
*/
void QGL_Shutdown( void ) {
}

qboolean QGL_Init( const char *dllname )
{
	qglLockArraysEXT = 0;
	qglUnlockArraysEXT = 0;
	qglPointParameterfEXT = 0;
	qglPointParameterfvEXT = 0;
	qglColorTableEXT = 0;
	//qgl3DfxSetPaletteEXT = 0;
	qglSelectTextureSGIS = 0;


	return true;
}



