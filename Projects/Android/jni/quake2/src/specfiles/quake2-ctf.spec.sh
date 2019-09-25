#!/bin/sh
# Generate quake2.spec
# $1 is version
# $2 is release
# $3 is arch
# $4 is install dir (assumed to be in /var/tmp)
cat <<EOF
%define name quake2-ctf
%define version ${1}
%define release ${2}
%define arch ${3}
%define builddir \$RPM_BUILD_DIR/%{name}-%{version}
Name:		%{name}
Version:	%{version}
Release:	%{release}
Vendor:		id Software
Packager:	Dave "Zoid" Kirsch <zoid@idsoftware.com>
URL:		http://www.idsoftware.com/q2ctf/
Source:		quake2-ctf-%{version}.tar.gz
BuildArchitectures: noarch
Group:		Games
Copyright:	Restricted
Icon:		quake2.gif
BuildRoot:	/var/tmp/%{name}-%{version}
Summary:	Quake2 Capture the Flag for Linux

%description

Quake II Capture The Flag (Q2CTF) is a multiplayer addon for Quake2 that 
features a simple set of rules for team based play. It features eight unique 
maps and special powerups to enhance and make the gameplay more exciting.

Q2CTF requires the full retail version of Quake II installed in order to 
play. Once installed, you simple need to connect to a Quake2 game server 
that is running the Q2CTF addon.

%install

%files

%attr(644,root,root) $4/ctf/pak0.pak
%attr(644,root,root) $4/ctf/pak1.pak
%attr(644,root,root) $4/ctf/ctf2.ico
%attr(644,root,root) $4/ctf/readme.txt
%attr(644,root,root) $4/ctf/server.cfg

EOF

