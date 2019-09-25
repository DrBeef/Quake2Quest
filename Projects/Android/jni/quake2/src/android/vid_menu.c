#include "../client/client.h"
#include "../client/qmenu.h"

/*
====================================================================

REF stuff ...
Used to dynamically load the menu with only those vid_ref's that
are present on this system

====================================================================
*/

/* this will have to be updated if ref's are added/removed from ref_t */
#ifdef ANDROID
#define NUMBER_OF_REFS 1
#else
#define NUMBER_OF_REFS 5
#endif

/* all the refs should be initially set to 0 */
static char *refs[NUMBER_OF_REFS+1] = { 0 };

/* make all these have illegal values, as they will be redefined */
static int REF_SOFT    = NUMBER_OF_REFS;
static int REF_SOFTX11 = NUMBER_OF_REFS;
static int REF_SOFTSDL = NUMBER_OF_REFS;
static int REF_GLX     = NUMBER_OF_REFS;
static int REF_SDLGL   = NUMBER_OF_REFS;
//static int REF_FXGL    = NUMBER_OF_REFS;
#ifdef ANDROID
static int REF_ANDROID = NUMBER_OF_REFS;
#endif

static int GL_REF_START = NUMBER_OF_REFS;

typedef struct
{
	char menuname[32];
	char realname[32];
	int  *pointer;
} ref_t;

static const ref_t possible_refs[NUMBER_OF_REFS] =
{
#ifdef ANDROID
	{ "[android       ]", "android", &REF_ANDROID    },		
#else
	{ "[software      ]", "soft",    &REF_SOFT    },
	{ "[software X11  ]", "softx",   &REF_SOFTX11 },
	{ "[software SDL  ]", "softsdl", &REF_SOFTSDL },
	{ "[OpenGL GLX    ]", "glx",     &REF_GLX     },
	{ "[SDL OpenGL    ]", "sdlgl",   &REF_SDLGL   }
#endif
};

/*
====================================================================
*/

extern cvar_t *vid_ref;
extern cvar_t *vid_fullscreen;
extern cvar_t *vid_gamma;
extern cvar_t *scr_viewsize;

static cvar_t *gl_mode;
static cvar_t *gl_driver;
static cvar_t *gl_picmip;
static cvar_t *gl_ext_palettedtexture;

static cvar_t *sw_mode;
static cvar_t *sw_stipplealpha;

static cvar_t *_windowed_mouse;

extern void M_ForceMenuOff( void );
extern qboolean VID_CheckRefExists( const char *name );

/*
====================================================================

MENU INTERACTION

====================================================================
*/
#define SOFTWARE_MENU 0
#define OPENGL_MENU   1

static menuframework_s  s_software_menu;
static menuframework_s	s_opengl_menu;
static menuframework_s *s_current_menu;
static int				s_current_menu_index;

static menulist_s		s_mode_list[2];
static menulist_s		s_ref_list[2];
static menuslider_s		s_tq_slider;
static menuslider_s		s_screensize_slider[2];
static menuslider_s		s_brightness_slider[2];
static menulist_s  		s_fs_box[2];
static menulist_s  		s_stipple_box;
static menulist_s  		s_paletted_texture_box;
static menulist_s  		s_windowed_mouse;
static menuaction_s		s_apply_action[2];
static menuaction_s		s_defaults_action[2];

static void DriverCallback( void *unused )
{
	s_ref_list[!s_current_menu_index].curvalue = s_ref_list[s_current_menu_index].curvalue;

	if ( s_ref_list[s_current_menu_index].curvalue < GL_REF_START )
	{
		s_current_menu = &s_software_menu;
		s_current_menu_index = 0;
	}
	else
	{
		s_current_menu = &s_opengl_menu;
		s_current_menu_index = 1;
	}

}

static void ScreenSizeCallback( void *s )
{
	menuslider_s *slider = ( menuslider_s * ) s;

	Cvar_SetValue( "viewsize", slider->curvalue * 10 );
}

static void BrightnessCallback( void *s )
{
	menuslider_s *slider = ( menuslider_s * ) s;

	if ( s_current_menu_index == 0)
		s_brightness_slider[1].curvalue = s_brightness_slider[0].curvalue;
	else
		s_brightness_slider[0].curvalue = s_brightness_slider[1].curvalue;

	if ( stricmp( vid_ref->string, "soft" ) == 0 ||
		 stricmp( vid_ref->string, "softx" ) == 0 ||
		 stricmp( vid_ref->string, "softsdl" ) == 0 ||
		 stricmp( vid_ref->string, "glx" ) == 0 )
	{
		float gamma = ( 0.8 - ( slider->curvalue/10.0 - 0.5 ) ) + 0.5;

		Cvar_SetValue( "vid_gamma", gamma );
	}
}

static void ResetDefaults( void *unused )
{
	VID_MenuInit();
}

static void ApplyChanges( void *unused )
{
	float gamma;
	int ref;

	/*
	** make values consistent
	*/
	s_fs_box[!s_current_menu_index].curvalue = s_fs_box[s_current_menu_index].curvalue;
	s_brightness_slider[!s_current_menu_index].curvalue = s_brightness_slider[s_current_menu_index].curvalue;
	s_ref_list[!s_current_menu_index].curvalue = s_ref_list[s_current_menu_index].curvalue;

	/*
	** invert sense so greater = brighter, and scale to a range of 0.5 to 1.3
	*/
	gamma = ( 0.8 - ( s_brightness_slider[s_current_menu_index].curvalue/10.0 - 0.5 ) ) + 0.5;

	Cvar_SetValue( "vid_gamma", gamma );
	Cvar_SetValue( "sw_stipplealpha", s_stipple_box.curvalue );
	Cvar_SetValue( "gl_picmip", 3 - s_tq_slider.curvalue );
	Cvar_SetValue( "vid_fullscreen", s_fs_box[s_current_menu_index].curvalue );
	Cvar_SetValue( "gl_ext_palettedtexture", s_paletted_texture_box.curvalue );
	Cvar_SetValue( "sw_mode", s_mode_list[SOFTWARE_MENU].curvalue );
	Cvar_SetValue( "gl_mode", s_mode_list[OPENGL_MENU].curvalue );
	Cvar_SetValue( "_windowed_mouse", s_windowed_mouse.curvalue);

	/*
	** must use an if here (instead of a switch), since the REF_'s are now variables
	** and not #DEFINE's (constants)
	*/
	ref = s_ref_list[s_current_menu_index].curvalue;
	if ( ref == REF_SOFT )
	{
		Cvar_Set( "vid_ref", "soft" );
	}
	else if ( ref == REF_SOFTX11 )
	{
		Cvar_Set( "vid_ref", "softx" );
	}
	else if ( ref == REF_SOFTSDL )
	{
		Cvar_Set( "vid_ref", "softsdl" );
	}
	else if ( ref == REF_GLX )
	{
		Cvar_Set( "vid_ref", "glx" );
		// below is wrong if we use different libs for different GL reflibs
		Cvar_Get( "gl_driver", "libGL.so.1", CVAR_ARCHIVE ); // ??? create if it doesn't exit
		if (gl_driver->modified)
			vid_ref->modified = true;
	}
	else if ( ref == REF_SDLGL )
	{
		Cvar_Set( "vid_ref", "sdlgl" );
		// below is wrong if we use different libs for different GL reflibs
		Cvar_Get( "gl_driver", "libGL.so.1", CVAR_ARCHIVE ); // ??? create if it doesn't exist
		if (gl_driver->modified)
			vid_ref->modified = true;
	}

#if 0
	/*
	** update appropriate stuff if we're running OpenGL and gamma
	** has been modified
	*/
	if ( stricmp( vid_ref->string, "gl" ) == 0 )
	{
		if ( vid_gamma->modified )
		{
			vid_ref->modified = true;
			if ( stricmp( gl_driver->string, "3dfxgl" ) == 0 )
			{
				char envbuffer[1024];
				float g;

				vid_ref->modified = true;

				g = 2.00 * ( 0.8 - ( vid_gamma->value - 0.5 ) ) + 1.0F;
				Com_sprintf( envbuffer, sizeof(envbuffer), "SST_GAMMA=%f", g );
				putenv( envbuffer );

				vid_gamma->modified = false;
			}
		}
	}
#endif

	M_ForceMenuOff();
}

/*
** VID_MenuInit
*/
void VID_MenuInit( void )
{
	int i, counter;

	static const char *resolutions[] = 
	{
		"[320 240  ]",
		"[400 300  ]",
		"[512 384  ]",
		"[640 480  ]",
		"[800 600  ]",
		"[960 720  ]",
		"[1024 768 ]",
		"[1152 864 ]",
		"[1280 1024]",
		"[1600 1200]",
		"[2048 1536]",
		"[1024 480 ]", /* sony vaio pocketbook */
		"[1152 768 ]", /* Apple TiBook */
		"[1280 854 ]", /* apple TiBook */
		"[640 400  ]", /* generic 16:10 widescreen resolutions */
 		"[800 500  ]", /* as found on many modern notebooks    */
 		"[1024 640 ]",
 		"[1280 800 ]",
 		"[1680 1050]",
 		"[1920 1200]",
		0
	};
	static const char *yesno_names[] =
	{
		"no",
		"yes",
		0
	};

	/* make sure these are invalided before showing the menu again */
	REF_SOFT    = NUMBER_OF_REFS;
	REF_SOFTX11 = NUMBER_OF_REFS;
	REF_SOFTSDL = NUMBER_OF_REFS;
	REF_GLX     = NUMBER_OF_REFS;
	REF_SDLGL   = NUMBER_OF_REFS;
	//REF_FXGL    = NUMBER_OF_REFS;
#ifdef ANDROID
	REF_ANDROID = NUMBER_OF_REFS;	
#endif
	
	GL_REF_START = NUMBER_OF_REFS;

	/* now test to see which ref's are present */
	i = counter = 0;
	while ( i < NUMBER_OF_REFS )
	{
		if ( VID_CheckRefExists( possible_refs[i].realname ) )
		{
			*(possible_refs[i].pointer) = counter;

			/* free any previous string */
			if ( refs[i] )
				free ( refs[i] );
			refs[counter] = strdup(possible_refs[i].menuname);

			/*
			** if we reach the 3rd item in the list, this indicates that a
			** GL ref has been found; this will change if more software
			** modes are added to the possible_ref's array
			*/
			if ( i == 3 )
				GL_REF_START = counter;

			counter++;
		}
		i++;
	}
	refs[counter] = (char*) 0;
	
#ifdef ANDROID
	GL_REF_START = 0;
#endif

	if ( !gl_driver )
		gl_driver = Cvar_Get( "gl_driver", "libGL.so", 0 );
	if ( !gl_picmip )
		gl_picmip = Cvar_Get( "gl_picmip", "0", 0 );
	if ( !gl_mode )
		gl_mode = Cvar_Get( "gl_mode", "3", 0 );
	if ( !sw_mode )
		sw_mode = Cvar_Get( "sw_mode", "0", 0 );
	if ( !gl_ext_palettedtexture )
		gl_ext_palettedtexture = Cvar_Get( "gl_ext_palettedtexture", "1", CVAR_ARCHIVE );

	if ( !sw_stipplealpha )
		sw_stipplealpha = Cvar_Get( "sw_stipplealpha", "0", CVAR_ARCHIVE );

	if ( !_windowed_mouse)
		_windowed_mouse = Cvar_Get( "_windowed_mouse", "0", CVAR_ARCHIVE );

	s_mode_list[SOFTWARE_MENU].curvalue = sw_mode->value;
	s_mode_list[OPENGL_MENU].curvalue = gl_mode->value;

	if ( !scr_viewsize )
		scr_viewsize = Cvar_Get ("viewsize", "100", CVAR_ARCHIVE);

	s_screensize_slider[SOFTWARE_MENU].curvalue = scr_viewsize->value/10;
	s_screensize_slider[OPENGL_MENU].curvalue = scr_viewsize->value/10;

	if ( strcmp( vid_ref->string, "soft" ) == 0)
	{
		s_current_menu_index = SOFTWARE_MENU;
		s_ref_list[0].curvalue = s_ref_list[1].curvalue = REF_SOFT;
	}
	else if (strcmp( vid_ref->string, "softx" ) == 0 ) 
	{
		s_current_menu_index = SOFTWARE_MENU;
		s_ref_list[0].curvalue = s_ref_list[1].curvalue = REF_SOFTX11;
	}
	else if (strcmp( vid_ref->string, "softsdl" ) == 0 )
	{
		s_current_menu_index = SOFTWARE_MENU;
		s_ref_list[0].curvalue = s_ref_list[1].curvalue = REF_SOFTSDL;
	}
	else if ( strcmp( vid_ref->string, "glx" ) == 0 )
	{
		s_current_menu_index = OPENGL_MENU;
		s_ref_list[s_current_menu_index].curvalue = REF_GLX;
#if 0
		if ( strcmp( gl_driver->string, "3dfxgl" ) == 0 )
			s_ref_list[s_current_menu_index].curvalue = REF_3DFX;
		else if ( strcmp( gl_driver->string, "pvrgl" ) == 0 )
			s_ref_list[s_current_menu_index].curvalue = REF_POWERVR;
		else if ( strcmp( gl_driver->string, "opengl32" ) == 0 )
			s_ref_list[s_current_menu_index].curvalue = REF_OPENGL;
		else
			s_ref_list[s_current_menu_index].curvalue = REF_VERITE;
#endif
	}
	else if ( strcmp( vid_ref->string, "sdlgl" ) == 0 )
	{
		s_current_menu_index = OPENGL_MENU;
		s_ref_list[s_current_menu_index].curvalue = REF_SDLGL;
#if 0
		if ( strcmp( gl_driver->string, "3dfxgl" ) == 0 )
			s_ref_list[s_current_menu_index].curvalue = REF_3DFX;
		else if ( strcmp( gl_driver->string, "pvrgl" ) == 0 )
			s_ref_list[s_current_menu_index].curvalue = REF_POWERVR;
		else if ( strcmp( gl_driver->string, "opengl32" ) == 0 )
			s_ref_list[s_current_menu_index].curvalue = REF_OPENGL;
		else
			s_ref_list[s_current_menu_index].curvalue = REF_VERITE;
#endif
	}
#ifdef ANDROID
	else if ( strcmp( vid_ref->string, "android" ) == 0 )
	{
		s_current_menu_index = OPENGL_MENU;
		s_ref_list[s_current_menu_index].curvalue = REF_ANDROID;
	}
#endif
	
	s_software_menu.x = viddef.width * 0.50;
	s_software_menu.nitems = 0;
	s_opengl_menu.x = viddef.width * 0.50;
	s_opengl_menu.nitems = 0;

	for ( i = 0; i < 2; i++ )
	{
		s_ref_list[i].generic.type = MTYPE_SPINCONTROL;
		s_ref_list[i].generic.name = "driver";
		s_ref_list[i].generic.x = 0;
		s_ref_list[i].generic.y = 0;
		s_ref_list[i].generic.callback = DriverCallback;
		s_ref_list[i].itemnames = (const char **) refs;

		s_mode_list[i].generic.type = MTYPE_SPINCONTROL;
		s_mode_list[i].generic.name = "video mode";
		s_mode_list[i].generic.x = 0;
		s_mode_list[i].generic.y = 10;
		s_mode_list[i].itemnames = resolutions;

		s_screensize_slider[i].generic.type	= MTYPE_SLIDER;
		s_screensize_slider[i].generic.x		= 0;
		s_screensize_slider[i].generic.y		= 20;
		s_screensize_slider[i].generic.name	= "screen size";
		s_screensize_slider[i].minvalue = 3;
		s_screensize_slider[i].maxvalue = 12;
		s_screensize_slider[i].generic.callback = ScreenSizeCallback;

		s_brightness_slider[i].generic.type	= MTYPE_SLIDER;
		s_brightness_slider[i].generic.x	= 0;
		s_brightness_slider[i].generic.y	= 30;
		s_brightness_slider[i].generic.name	= "brightness";
		s_brightness_slider[i].generic.callback = BrightnessCallback;
		s_brightness_slider[i].minvalue = 5;
		s_brightness_slider[i].maxvalue = 13;
		s_brightness_slider[i].curvalue = ( 1.3 - vid_gamma->value + 0.5 ) * 10;

		s_fs_box[i].generic.type = MTYPE_SPINCONTROL;
		s_fs_box[i].generic.x	= 0;
		s_fs_box[i].generic.y	= 40;
		s_fs_box[i].generic.name	= "fullscreen";
		s_fs_box[i].itemnames = yesno_names;
		s_fs_box[i].curvalue = vid_fullscreen->value;

		s_defaults_action[i].generic.type = MTYPE_ACTION;
		s_defaults_action[i].generic.name = "reset to default";
		s_defaults_action[i].generic.x    = 0;
		s_defaults_action[i].generic.y    = 90;
		s_defaults_action[i].generic.callback = ResetDefaults;

		s_apply_action[i].generic.type = MTYPE_ACTION;
		s_apply_action[i].generic.name = "apply";
		s_apply_action[i].generic.x    = 0;
		s_apply_action[i].generic.y    = 100;
		s_apply_action[i].generic.callback = ApplyChanges;
	}

	s_stipple_box.generic.type = MTYPE_SPINCONTROL;
	s_stipple_box.generic.x	= 0;
	s_stipple_box.generic.y	= 60;
	s_stipple_box.generic.name	= "stipple alpha";
	s_stipple_box.curvalue = sw_stipplealpha->value;
	s_stipple_box.itemnames = yesno_names;

	s_windowed_mouse.generic.type = MTYPE_SPINCONTROL;
	s_windowed_mouse.generic.x  = 0;
	s_windowed_mouse.generic.y  = 72;
	s_windowed_mouse.generic.name   = "windowed mouse";
	s_windowed_mouse.curvalue = _windowed_mouse->value;
	s_windowed_mouse.itemnames = yesno_names;

	s_tq_slider.generic.type	= MTYPE_SLIDER;
	s_tq_slider.generic.x		= 0;
	s_tq_slider.generic.y		= 60;
	s_tq_slider.generic.name	= "texture quality";
	s_tq_slider.minvalue = 0;
	s_tq_slider.maxvalue = 3;
	s_tq_slider.curvalue = 3-gl_picmip->value;

	s_paletted_texture_box.generic.type = MTYPE_SPINCONTROL;
	s_paletted_texture_box.generic.x	= 0;
	s_paletted_texture_box.generic.y	= 70;
	s_paletted_texture_box.generic.name	= "8-bit textures";
	s_paletted_texture_box.itemnames = yesno_names;
	s_paletted_texture_box.curvalue = gl_ext_palettedtexture->value;

	Menu_AddItem( &s_software_menu, ( void * ) &s_ref_list[SOFTWARE_MENU] );
	Menu_AddItem( &s_software_menu, ( void * ) &s_mode_list[SOFTWARE_MENU] );
	Menu_AddItem( &s_software_menu, ( void * ) &s_screensize_slider[SOFTWARE_MENU] );
	Menu_AddItem( &s_software_menu, ( void * ) &s_brightness_slider[SOFTWARE_MENU] );
	Menu_AddItem( &s_software_menu, ( void * ) &s_fs_box[SOFTWARE_MENU] );
	Menu_AddItem( &s_software_menu, ( void * ) &s_stipple_box );
	Menu_AddItem( &s_software_menu, ( void * ) &s_windowed_mouse );

	Menu_AddItem( &s_opengl_menu, ( void * ) &s_ref_list[OPENGL_MENU] );
	Menu_AddItem( &s_opengl_menu, ( void * ) &s_mode_list[OPENGL_MENU] );
	Menu_AddItem( &s_opengl_menu, ( void * ) &s_screensize_slider[OPENGL_MENU] );
	Menu_AddItem( &s_opengl_menu, ( void * ) &s_brightness_slider[OPENGL_MENU] );
	Menu_AddItem( &s_opengl_menu, ( void * ) &s_fs_box[OPENGL_MENU] );
	Menu_AddItem( &s_opengl_menu, ( void * ) &s_tq_slider );
	Menu_AddItem( &s_opengl_menu, ( void * ) &s_paletted_texture_box );

	Menu_AddItem( &s_software_menu, ( void * ) &s_defaults_action[SOFTWARE_MENU] );
	Menu_AddItem( &s_software_menu, ( void * ) &s_apply_action[SOFTWARE_MENU] );
	Menu_AddItem( &s_opengl_menu, ( void * ) &s_defaults_action[OPENGL_MENU] );
	Menu_AddItem( &s_opengl_menu, ( void * ) &s_apply_action[OPENGL_MENU] );

	Menu_Center( &s_software_menu );
	Menu_Center( &s_opengl_menu );
	s_opengl_menu.x -= 8;
	s_software_menu.x -= 8;
}

/*
================
VID_MenuShutdown
================
*/
void VID_MenuShutdown( void )
{
	int i;

	for ( i = 0; i < NUMBER_OF_REFS; i++ )
	{
		if ( refs[i] )
			free ( refs[i] );
	}
}

/*
================
VID_MenuDraw
================
*/
void VID_MenuDraw (void)
{
	int w, h;

	if ( s_current_menu_index == 0 )
		s_current_menu = &s_software_menu;
	else
		s_current_menu = &s_opengl_menu;

	/*
	** draw the banner
	*/
	re.DrawGetPicSize( &w, &h, "m_banner_video" );
	re.DrawPic( viddef.width / 2 - w / 2, viddef.height /2 - 110, "m_banner_video" );

	/*
	** move cursor to a reasonable starting position
	*/
	Menu_AdjustCursor( s_current_menu, 1 );

	/*
	** draw the menu
	*/
	Menu_Draw( s_current_menu );
}

/*
================
VID_MenuKey
================
*/
const char *VID_MenuKey( int key )
{
	extern void M_PopMenu( void );

	menuframework_s *m = s_current_menu;
	static const char *sound = "misc/menu1.wav";

	switch ( key )
	{
	case K_ESCAPE:
		M_PopMenu();
		return NULL;
	case K_UPARROW:
		m->cursor--;
		Menu_AdjustCursor( m, -1 );
		break;
	case K_DOWNARROW:
		m->cursor++;
		Menu_AdjustCursor( m, 1 );
		break;
	case K_LEFTARROW:
		Menu_SlideItem( m, -1 );
		break;
	case K_RIGHTARROW:
		Menu_SlideItem( m, 1 );
		break;
	case K_ENTER:
		Menu_SelectItem( m );
		break;
	}

	return sound;
}
