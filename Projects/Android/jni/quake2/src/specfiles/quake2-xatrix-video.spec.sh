#!/bin/sh
# Generate quake2.spec
# $1 is version
# $2 is release
# $3 is arch
# $4 is install dir (assumed to be in /var/tmp)
cat <<EOF
%define name quake2-xatrix-video
%define version ${1}
%define release ${2}
%define arch ${3}
%define builddir \$RPM_BUILD_DIR/%{name}-%{version}
Name:		%{name}
Version:	%{version}
Release:	%{release}
Vendor:		id Software/Xatrix Entertainment
Packager:	Dave "Zoid" Kirsch <zoid@idsoftware.com>
URL:		http://www.xatrix.com/
Source:		quake2-xatrix-video-%{version}.tar.gz
BuildArchitectures: noarch
Group:		Games
Copyright:	Restricted
Icon:		quake2.gif
BuildRoot:	/var/tmp/%{name}-%{version}
Summary:	Quake2 Mission Pack #1: The Reckoning Video Files for Linux

%description

Mission Pack Features

The Reckoning is sure to get your heart pumping...well, if you can avoid 
getting gibbed by the Strogg. Check out just some of the features below that 
will give you the cardiac workout you need!

18 ARDUOUS LEVELS TO CONQUER & 7 BRUTAL DEATHMATCH EXCLUSIVE LEVELS

Dive into a series of mission-based campaigns and ransack your way through 
three all-new hazardous episodes. Experience bioluminescent life forms, 
stalagmites and stalactites and other breathtaking environments. 

FRESH FOES TO DEFEAT

Gekks are lighting-fast creatures that will hunt you down, leaping from the 
shadows to claw or bite. Though innocent looking, the Repair Bot has the 
ability to awaken dead Strogg from eternal sleep.
 
ADDED WEAPONS TO WIELD

The Phalanx Particle Canon emits a pulsing stream of deadly energy into 
unsuspecting foes. 

The Trap sucks nearby enemies inside and turns them into food cubes for 
player consumption. 

The Ion Ripper fires a blast of glowing boomerangs capable of ricocheting 
off of walls to track targets.

%install

%files

%attr(644,root,root) $4/xatrix/video/idlog.cin
%attr(644,root,root) $4/xatrix/video/logo.cin
%attr(644,root,root) $4/xatrix/video/xin.cin
%attr(644,root,root) $4/xatrix/video/xout.cin
%attr(644,root,root) $4/xatrix/video/xu1.cin
%attr(644,root,root) $4/xatrix/video/xu2.cin
%attr(644,root,root) $4/xatrix/video/xu3.cin
%attr(644,root,root) $4/xatrix/video/xu4.cin

EOF

