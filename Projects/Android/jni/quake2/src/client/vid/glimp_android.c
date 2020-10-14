
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

#include "../../common/header/shared.h"
#include "header/ref.h"

static int framecount;

// The last time input events were processed.
// Used throughout the client.
int sys_frame_time;

// the joystick altselector that turns K_JOYX into K_JOYX_ALT
// is pressed
qboolean joy_altselector_pressed = false;

// Console Variables
cvar_t *vid_fullscreen;
cvar_t *freelook;
cvar_t *lookstrafe;
cvar_t *m_forward;
cvar_t *m_pitch;
cvar_t *m_side;
cvar_t *m_up;
cvar_t *m_yaw;
cvar_t *sensitivity;

void Quest_GetScreenRes(int *width, int *height);
int Quest_GetRefresh();

qboolean GLimp_Init(void) { return true; }
void GLimp_Shutdown(void) {}
qboolean GLimp_InitGraphics(int fullscreen, int *pwidth, int *pheight)
{
    int width = *pwidth;
    int height = *pheight;

    /* We need the window size for the menu, the HUD, etc. */
    viddef.width = width;
    viddef.height = height;

    return true;
}
void GLimp_ShutdownGraphics(void) {}
void GLimp_GrabInput(qboolean grab) {}
int GLimp_GetRefreshRate(void) { return Quest_GetRefresh(); } // Returen Quest refresh rate
qboolean GLimp_GetDesktopMode(int *pwidth, int *pheight)
{
    Quest_GetScreenRes(pwidth, pheight);
    return 1; //bettter
}


/*****************************************************************************/
/* INPUT                                                                     */
/*****************************************************************************/

void IN_Init (void)
{
}

void In_FlushQueue (void)
{
}

void IN_Update(void)
{
    // We need to save the frame time so other subsystems
    // know the exact time of the last input events.
    sys_frame_time = Sys_Milliseconds();
}

void IN_Shutdown (void)
{
}
