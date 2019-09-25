#!/bin/sh
# Generate quake2.spec
# $1 is version
# $2 is release
# $3 is arch
# $4 is install dir (assumed to be in /var/tmp)
cat <<EOF
%define name quake2-video
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
Source:		quake2-video-%{version}.tar.gz
BuildArchitectures: noarch
Group:		Games
Copyright:	Restricted
Icon:		quake2.gif
BuildRoot:	/var/tmp/%{name}-%{version}
Summary:	Quake2 Video Data for Linux

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

This package contains the optional Quake2 video files that are played during
the game.

%install

%files

%attr(644,root,root) $4/baseq2/video/end.cin
%attr(644,root,root) $4/baseq2/video/eou1_.cin
%attr(644,root,root) $4/baseq2/video/eou2_.cin
%attr(644,root,root) $4/baseq2/video/eou3_.cin
%attr(644,root,root) $4/baseq2/video/eou4_.cin
%attr(644,root,root) $4/baseq2/video/eou5_.cin
%attr(644,root,root) $4/baseq2/video/eou6_.cin
%attr(644,root,root) $4/baseq2/video/eou7_.cin
%attr(644,root,root) $4/baseq2/video/eou8_.cin
%attr(644,root,root) $4/baseq2/video/idlog.cin
%attr(644,root,root) $4/baseq2/video/ntro.cin

EOF

