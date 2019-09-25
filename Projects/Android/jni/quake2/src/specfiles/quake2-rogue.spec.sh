#!/bin/sh
# Generate quake2.spec
# $1 is version
# $2 is release
# $3 is arch
# $4 is install dir (assumed to be in /var/tmp)
cat <<EOF
%define name quake2-rogue
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
Source:		quake2-rogue-%{version}.tar.gz
BuildArchitectures: noarch
Group:		Games
Copyright:	Restricted
Icon:		quake2.gif
BuildRoot:	/var/tmp/%{name}-%{version}
Summary:	Quake2 for Linux

%description

Mission Pack Features

The Alien Assault Continues.
Take out the Big Gun, sounded simple enough, except the Stroggs were waiting. 
You and a few Marines like you, are the lucky ones. The Gravity Well, the 
Stroggs' newest weapon in its arsenal against mankind, is operational. You've 
made it down in one piece and are still able to contact the fleet. With the 
fleet trapped around Stroggos, five percent of ground forces surviving, and 
that number dwindling by the second, your orders have changed: Free your 
comrades in orbit. Destroy the Gravity Well!

New Enemies

Get ready to face the toughest horde of Stroggs, straight from the bio-vats. 
The Stalker, Turrets, Daedalus, Medic Commander, Carrier and the Queen Bitch 
herself, the Black Widow.
     
14 Entirely new levels and 10 new deathmatch levels

Brand new real estate with the same dynamic sense of reality and dramatic 
visuals as Quake II. These new environments will challenge even the biggest 
Quake II aficionado.
 
New Power-ups

Tag 'em and Bag 'em. Deathmatch specific power-ups: the Vengeance Sphere, 
Hunter Sphere, and Anti-matter Bomb. With everything that we've cooked up for 
you here, you're sure to annihilate anyone or anything foolish enough to 
call you foe.

New Weapons 

The Chainsaw, ETF Rifle, and Plasma Beam. If you can't get the job done with 
these babies, it's time to go back to Basic.

Accept no substitutes!
Official, id-authorized mission packs outpace the rest! 

%install

%files

%attr(644,root,root) $4/rogue/pak0.pak
%attr(644,root,root) $4/rogue/docs/license.doc
%attr(644,root,root) $4/rogue/docs/license.txt
%attr(644,root,root) $4/rogue/docs/readme.htm
%attr(644,root,root) $4/rogue/docs/readme.txt
%attr(644,root,root) $4/rogue/docs/release.htm
%attr(644,root,root) $4/rogue/docs/release.txt

EOF

