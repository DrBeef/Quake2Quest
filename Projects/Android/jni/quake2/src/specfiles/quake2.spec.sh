#!/bin/sh
# Generate quake2.spec
# $1 is version
# $2 is release
# $3 is arch
# $4 is install dir (assumed to be in /var/tmp)
cat <<EOF
%define name quake2
%define version ${1}
%define release ${2}
%define arch ${3}
%define builddir \$RPM_BUILD_DIR/%{name}-%{version}
Name:		%{name}
Version:	%{version}
Release:	%{release}
Vendor:		id Software
Packager:	Dave "Zoid" Kirsch <zoid@idsoftware.com>
URL:		http://www.idsoftware.com/
Source:		quake2-%{version}.tar.gz
Group:		Games
Copyright:	Restricted
Icon:		quake2.gif
BuildRoot:	/var/tmp/%{name}-%{version}
Summary:	Quake2 for Linux

%description

                                    Quake2

Shortly after landing on an alien surface you learn that hundreds of your men
have been reduced to just a few.  Now you must fight your way through heavily
fortified military installations, lower the city's defenses and shut down
the enemy's war machine.  Only then will the fate of humanity be known.

LARGER, MISSION-BASED LEVELS

You have a series of complex missions, what you do in one level could affect
another.  One false move and you could alert security, flood an entire
passageway, or worse.

SUPERIOR ARTIFICIAL INTELLIGENCE

This time the enemy has IQs the size of their appetites.  The can evade your
attack, strategically position themselves for an ambush and hunt your ass 
down.

IN-YOUR-FACE SOUND AND GRAPHICS

hear distant combat explosions and rockets whizzing past your head.  And with
a compatible 3-D graphics accelerator, experience smoother 16-bit graphics and
real-time lighting effects.

WICKED MULTIPLAYER CAPABILITIES

More than 32 players, friends or foes, can do at it in a bloody deathmatch via
LAN and over the internet.

----

Quake2 for Linux supports the following video subsystems:

- SVGALib Console Graphics (ref_soft.so)
	- Requires SVGALib 1.2.0 or later
- X11 Window Graphics (ref_softx.so)
	- X11R5 or later, XShm shared memory extension supported
- 3DFX fxMesa with Mesa 3-D (ref_gl.so)
	- Mesa 3-D 2.6 or later, specifically compiled for 3DFX support
	  Mesa 3-D 2.6 compiled with 3DFX support is provided with this archive.
- Generic glX (X11) based OpenGL (ref_glx.so)
	- Requires a glX based hardware accelerated OpenGL implementation.
	  Mesa 3-D 2.6 supports this on 3DFX hardware.

Also included is a specific 3DFX mini-OpenGL implementation for running Quake2
on 3DFX hardware.

For 3DFX based hardware, 3DFXs GLIDE drivers for Linux are required.

%install

%files

%attr(644,root,root) $4/README
%attr(4755,root,root) $4/quake2
%attr(755,root,root) $4/ref_soft.so
%attr(755,root,root) $4/ref_softx.so
%attr(755,root,root) $4/ref_gl.so
%attr(755,root,root) $4/ref_glx.so
%attr(755,root,root) $4/baseq2/game%{arch}.so
%attr(755,root,root) $4/xatrix/game%{arch}.so
%attr(755,root,root) $4/rogue/game%{arch}.so
%attr(755,root,root) $4/ctf/game%{arch}.so
%attr(755,root,root) /usr/lib/lib3dfxgl.so
%attr(755,root,root) /usr/lib/libMesaGL.so.2.6
%attr(644,root,root) /etc/quake2.conf

%post
chmod 1777 $4/baseq2
chmod 1777 $4/ctf
chmod 1777 $4/xatrix
chmod 1777 $4/rogue
EOF

