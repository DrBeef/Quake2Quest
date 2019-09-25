#!/bin/sh
# Generate quake2.spec
# $1 is version
# $2 is release
# $3 is arch
# $4 is install dir (assumed to be in /var/tmp)
cat <<EOF
%define name quake2-data
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
Source:		quake2-data-%{version}.tar.gz
BuildArchitectures: noarch
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

This package contains the data files needed to run Quake2.

%install

%files

%attr(644,root,root) $4/baseq2/pak0.pak
%attr(644,root,root) $4/baseq2/pak1.pak
%attr(644,root,root) $4/baseq2/pak2.pak
%attr(644,root,root) $4/baseq2/players/cyborg/a_grenades.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_bfg.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_blaster.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_chainfist.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_chaingun.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_disrupt.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_etfrifle.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_glauncher.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_grapple.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_hyperblaster.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_machinegun.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_phalanx.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_plasma.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_plauncher.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_railgun.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_ripper.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_rlauncher.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_shotgun.md2
%attr(644,root,root) $4/baseq2/players/cyborg/w_sshotgun.md2
%attr(644,root,root) $4/baseq2/players/female/a_grenades.md2
%attr(644,root,root) $4/baseq2/players/female/w_bfg.md2
%attr(644,root,root) $4/baseq2/players/female/w_blaster.md2
%attr(644,root,root) $4/baseq2/players/female/w_chainfist.md2
%attr(644,root,root) $4/baseq2/players/female/w_chaingun.md2
%attr(644,root,root) $4/baseq2/players/female/w_disrupt.md2
%attr(644,root,root) $4/baseq2/players/female/w_etfrifle.md2
%attr(644,root,root) $4/baseq2/players/female/w_glauncher.md2
%attr(644,root,root) $4/baseq2/players/female/w_grapple.md2
%attr(644,root,root) $4/baseq2/players/female/w_hyperblaster.md2
%attr(644,root,root) $4/baseq2/players/female/w_machinegun.md2
%attr(644,root,root) $4/baseq2/players/female/w_phalanx.md2
%attr(644,root,root) $4/baseq2/players/female/w_plasma.md2
%attr(644,root,root) $4/baseq2/players/female/w_plauncher.md2
%attr(644,root,root) $4/baseq2/players/female/w_railgun.md2
%attr(644,root,root) $4/baseq2/players/female/w_ripper.md2
%attr(644,root,root) $4/baseq2/players/female/w_rlauncher.md2
%attr(644,root,root) $4/baseq2/players/female/w_shotgun.md2
%attr(644,root,root) $4/baseq2/players/female/w_sshotgun.md2
%attr(644,root,root) $4/baseq2/players/male/a_grenades.md2
%attr(644,root,root) $4/baseq2/players/male/w_bfg.md2
%attr(644,root,root) $4/baseq2/players/male/w_blaster.md2
%attr(644,root,root) $4/baseq2/players/male/w_chainfist.md2
%attr(644,root,root) $4/baseq2/players/male/w_chaingun.md2
%attr(644,root,root) $4/baseq2/players/male/w_disrupt.md2
%attr(644,root,root) $4/baseq2/players/male/w_etfrifle.md2
%attr(644,root,root) $4/baseq2/players/male/w_glauncher.md2
%attr(644,root,root) $4/baseq2/players/male/w_grapple.md2
%attr(644,root,root) $4/baseq2/players/male/w_hyperblaster.md2
%attr(644,root,root) $4/baseq2/players/male/w_machinegun.md2
%attr(644,root,root) $4/baseq2/players/male/w_phalanx.md2
%attr(644,root,root) $4/baseq2/players/male/w_plasma.md2
%attr(644,root,root) $4/baseq2/players/male/w_plauncher.md2
%attr(644,root,root) $4/baseq2/players/male/w_railgun.md2
%attr(644,root,root) $4/baseq2/players/male/w_ripper.md2
%attr(644,root,root) $4/baseq2/players/male/w_rlauncher.md2
%attr(644,root,root) $4/baseq2/players/male/w_shotgun.md2
%attr(644,root,root) $4/baseq2/players/male/w_sshotgun.md2
%attr(644,root,root) $4/baseq2/players/female/athena.pcx
%attr(644,root,root) $4/baseq2/players/female/athena_i.pcx
%attr(644,root,root) $4/baseq2/players/female/brianna.pcx
%attr(644,root,root) $4/baseq2/players/female/brianna_i.pcx
%attr(644,root,root) $4/baseq2/players/female/cobalt.pcx
%attr(644,root,root) $4/baseq2/players/female/cobalt_i.pcx
%attr(644,root,root) $4/baseq2/players/female/ensign.pcx
%attr(644,root,root) $4/baseq2/players/female/ensign_i.pcx
%attr(644,root,root) $4/baseq2/players/female/jezebel.pcx
%attr(644,root,root) $4/baseq2/players/female/jezebel_i.pcx
%attr(644,root,root) $4/baseq2/players/female/jungle.pcx
%attr(644,root,root) $4/baseq2/players/female/jungle_i.pcx
%attr(644,root,root) $4/baseq2/players/female/lotus.pcx
%attr(644,root,root) $4/baseq2/players/female/lotus_i.pcx
%attr(644,root,root) $4/baseq2/players/female/stiletto.pcx
%attr(644,root,root) $4/baseq2/players/female/stiletto_i.pcx
%attr(644,root,root) $4/baseq2/players/female/tris.md2
%attr(644,root,root) $4/baseq2/players/female/venus.pcx
%attr(644,root,root) $4/baseq2/players/female/venus_i.pcx
%attr(644,root,root) $4/baseq2/players/female/voodoo.pcx
%attr(644,root,root) $4/baseq2/players/female/voodoo_i.pcx
%attr(644,root,root) $4/baseq2/players/female/weapon.md2
%attr(644,root,root) $4/baseq2/players/female/weapon.pcx
%attr(644,root,root) $4/baseq2/players/male/cipher.pcx
%attr(644,root,root) $4/baseq2/players/male/cipher_i.pcx
%attr(644,root,root) $4/baseq2/players/male/claymore.pcx
%attr(644,root,root) $4/baseq2/players/male/claymore_i.pcx
%attr(644,root,root) $4/baseq2/players/male/flak.pcx
%attr(644,root,root) $4/baseq2/players/male/flak_i.pcx
%attr(644,root,root) $4/baseq2/players/male/grunt.pcx
%attr(644,root,root) $4/baseq2/players/male/grunt_i.pcx
%attr(644,root,root) $4/baseq2/players/male/howitzer.pcx
%attr(644,root,root) $4/baseq2/players/male/howitzer_i.pcx
%attr(644,root,root) $4/baseq2/players/male/major.pcx
%attr(644,root,root) $4/baseq2/players/male/major_i.pcx
%attr(644,root,root) $4/baseq2/players/male/nightops.pcx
%attr(644,root,root) $4/baseq2/players/male/nightops_i.pcx
%attr(644,root,root) $4/baseq2/players/male/pointman.pcx
%attr(644,root,root) $4/baseq2/players/male/pointman_i.pcx
%attr(644,root,root) $4/baseq2/players/male/psycho.pcx
%attr(644,root,root) $4/baseq2/players/male/psycho_i.pcx
%attr(644,root,root) $4/baseq2/players/male/rampage.pcx
%attr(644,root,root) $4/baseq2/players/male/rampage_i.pcx
%attr(644,root,root) $4/baseq2/players/male/razor.pcx
%attr(644,root,root) $4/baseq2/players/male/razor_i.pcx
%attr(644,root,root) $4/baseq2/players/male/recon.pcx
%attr(644,root,root) $4/baseq2/players/male/recon_i.pcx
%attr(644,root,root) $4/baseq2/players/male/scout.pcx
%attr(644,root,root) $4/baseq2/players/male/scout_i.pcx
%attr(644,root,root) $4/baseq2/players/male/sniper.pcx
%attr(644,root,root) $4/baseq2/players/male/sniper_i.pcx
%attr(644,root,root) $4/baseq2/players/male/tris.md2
%attr(644,root,root) $4/baseq2/players/male/viper.pcx
%attr(644,root,root) $4/baseq2/players/male/viper_i.pcx
%attr(644,root,root) $4/baseq2/players/male/weapon.md2
%attr(644,root,root) $4/baseq2/players/male/weapon.pcx
%attr(644,root,root) $4/baseq2/players/cyborg/bump1.wav
%attr(644,root,root) $4/baseq2/players/cyborg/death1.wav
%attr(644,root,root) $4/baseq2/players/cyborg/death2.wav
%attr(644,root,root) $4/baseq2/players/cyborg/death3.wav
%attr(644,root,root) $4/baseq2/players/cyborg/death4.wav
%attr(644,root,root) $4/baseq2/players/cyborg/drown1.wav
%attr(644,root,root) $4/baseq2/players/cyborg/fall1.wav
%attr(644,root,root) $4/baseq2/players/cyborg/fall2.wav
%attr(644,root,root) $4/baseq2/players/cyborg/gurp1.wav
%attr(644,root,root) $4/baseq2/players/cyborg/gurp2.wav
%attr(644,root,root) $4/baseq2/players/cyborg/jump1.wav
%attr(644,root,root) $4/baseq2/players/cyborg/oni911.pcx
%attr(644,root,root) $4/baseq2/players/cyborg/oni911_i.pcx
%attr(644,root,root) $4/baseq2/players/cyborg/pain100_1.wav
%attr(644,root,root) $4/baseq2/players/cyborg/pain100_2.wav
%attr(644,root,root) $4/baseq2/players/cyborg/pain25_1.wav
%attr(644,root,root) $4/baseq2/players/cyborg/pain25_2.wav
%attr(644,root,root) $4/baseq2/players/cyborg/pain50_1.wav
%attr(644,root,root) $4/baseq2/players/cyborg/pain50_2.wav
%attr(644,root,root) $4/baseq2/players/cyborg/pain75_1.wav
%attr(644,root,root) $4/baseq2/players/cyborg/pain75_2.wav
%attr(644,root,root) $4/baseq2/players/cyborg/ps9000.pcx
%attr(644,root,root) $4/baseq2/players/cyborg/ps9000_i.pcx
%attr(644,root,root) $4/baseq2/players/cyborg/tris.md2
%attr(644,root,root) $4/baseq2/players/cyborg/tyr574.pcx
%attr(644,root,root) $4/baseq2/players/cyborg/tyr574_i.pcx
%attr(644,root,root) $4/baseq2/players/cyborg/weapon.md2
%attr(644,root,root) $4/baseq2/players/cyborg/weapon.pcx
%attr(644,root,root) $4/baseq2/players/cyborg/weapon.pcx.pcx
%attr(644,root,root) "$4/docs/Commercial Exploitation.doc"
%attr(644,root,root) $4/docs/Manual.html
%attr(644,root,root) "$4/docs/QII License Information.doc"
%attr(644,root,root) "$4/docs/Quake II License.doc"
%attr(644,root,root) "$4/docs/Release Notes.doc"
%attr(644,root,root) $4/docs/commexp.txt
%attr(644,root,root) $4/docs/license.txt
%attr(644,root,root) $4/docs/licinfo.txt
%attr(644,root,root) $4/docs/readme.doc
%attr(644,root,root) $4/docs/readme.txt
%attr(644,root,root) $4/docs/release.txt
%attr(644,root,root) $4/docs/quake2_manual/bottom.html
%attr(644,root,root) $4/docs/quake2_manual/credits.html
%attr(644,root,root) $4/docs/quake2_manual/customer_support.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_barracuda_shark.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_berserker.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_brains.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_enforcer.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_flyer.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_gladiator.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_gunner.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_icarus.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_iron_maiden.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_light_guard.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_machinegun_guard.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_medic.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_mutant.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_parasite.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_shotgun_guard.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_tank.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_tank_commander.html
%attr(644,root,root) $4/docs/quake2_manual/enemy_technician.html
%attr(644,root,root) $4/docs/quake2_manual/images/adrenaline.gif
%attr(644,root,root) $4/docs/quake2_manual/images/amor_body.gif
%attr(644,root,root) $4/docs/quake2_manual/images/armor_combat.gif
%attr(644,root,root) $4/docs/quake2_manual/images/armor_jacket.gif
%attr(644,root,root) $4/docs/quake2_manual/images/armor_shard.gif
%attr(644,root,root) $4/docs/quake2_manual/images/bandoleer.gif
%attr(644,root,root) $4/docs/quake2_manual/images/barracuda_shark.gif
%attr(644,root,root) $4/docs/quake2_manual/images/berserker.gif
%attr(644,root,root) $4/docs/quake2_manual/images/bfg.gif
%attr(644,root,root) $4/docs/quake2_manual/images/blaster.gif
%attr(644,root,root) $4/docs/quake2_manual/images/bluekey.gif
%attr(644,root,root) $4/docs/quake2_manual/images/bottom_id_link_transparent.gif
%attr(644,root,root) $4/docs/quake2_manual/images/brains.gif
%attr(644,root,root) $4/docs/quake2_manual/images/breather.gif
%attr(644,root,root) $4/docs/quake2_manual/images/bullets.gif
%attr(644,root,root) $4/docs/quake2_manual/images/buttons.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/cells.gif
%attr(644,root,root) $4/docs/quake2_manual/images/chaingun.gif
%attr(644,root,root) $4/docs/quake2_manual/images/cloaker.gif
%attr(644,root,root) $4/docs/quake2_manual/images/commandant_james.gif
%attr(644,root,root) $4/docs/quake2_manual/images/credits_main.gif
%attr(644,root,root) $4/docs/quake2_manual/images/door.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/elevator_base_exit_sign.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/enemy_groupshot.gif
%attr(644,root,root) $4/docs/quake2_manual/images/energy_armour.gif
%attr(644,root,root) $4/docs/quake2_manual/images/enforcer.gif
%attr(644,root,root) $4/docs/quake2_manual/images/envirosuit.gif
%attr(644,root,root) $4/docs/quake2_manual/images/explosive_barrels.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/first_aid.gif
%attr(644,root,root) $4/docs/quake2_manual/images/flyer.gif
%attr(644,root,root) $4/docs/quake2_manual/images/gladiator.gif
%attr(644,root,root) $4/docs/quake2_manual/images/goggles.gif
%attr(644,root,root) $4/docs/quake2_manual/images/grenades.gif
%attr(644,root,root) $4/docs/quake2_manual/images/grenade_launcher.gif
%attr(644,root,root) $4/docs/quake2_manual/images/gunner.gif
%attr(644,root,root) $4/docs/quake2_manual/images/hand_grenade.gif
%attr(644,root,root) $4/docs/quake2_manual/images/heavy_pack.gif
%attr(644,root,root) $4/docs/quake2_manual/images/hyper_blaster.gif
%attr(644,root,root) $4/docs/quake2_manual/images/icarus.gif
%attr(644,root,root) $4/docs/quake2_manual/images/invisibility.gif
%attr(644,root,root) $4/docs/quake2_manual/images/invulnerability.gif
%attr(644,root,root) $4/docs/quake2_manual/images/iron_maiden.gif
%attr(644,root,root) $4/docs/quake2_manual/images/lava.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/lever.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/light_guard.gif
%attr(644,root,root) $4/docs/quake2_manual/images/machinegun.gif
%attr(644,root,root) $4/docs/quake2_manual/images/machinegun_guard.gif
%attr(644,root,root) $4/docs/quake2_manual/images/main_cover_image.gif
%attr(644,root,root) $4/docs/quake2_manual/images/manual_back.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/manual_bottom.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/manual_cover_image.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/manual_top.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/medic.gif
%attr(644,root,root) $4/docs/quake2_manual/images/medkit.gif
%attr(644,root,root) $4/docs/quake2_manual/images/mega_health.gif
%attr(644,root,root) $4/docs/quake2_manual/images/menu.gif
%attr(644,root,root) $4/docs/quake2_manual/images/multiplayer_main.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/multiplayer_menu1.gif
%attr(644,root,root) $4/docs/quake2_manual/images/multiplayer_screen1.gif
%attr(644,root,root) $4/docs/quake2_manual/images/mutant.gif
%attr(644,root,root) $4/docs/quake2_manual/images/no_data.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/parasite.gif
%attr(644,root,root) $4/docs/quake2_manual/images/player_properties_screen1.gif
%attr(644,root,root) $4/docs/quake2_manual/images/quad_damage.gif
%attr(644,root,root) $4/docs/quake2_manual/images/rail_gun.gif
%attr(644,root,root) $4/docs/quake2_manual/images/rockets.gif
%attr(644,root,root) $4/docs/quake2_manual/images/rocket_launcher.gif
%attr(644,root,root) $4/docs/quake2_manual/images/scope.gif
%attr(644,root,root) $4/docs/quake2_manual/images/secret_door.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/shells.gif
%attr(644,root,root) $4/docs/quake2_manual/images/shotgun.gif
%attr(644,root,root) $4/docs/quake2_manual/images/shotgun_guard.gif
%attr(644,root,root) $4/docs/quake2_manual/images/sights.gif
%attr(644,root,root) $4/docs/quake2_manual/images/silencer.gif
%attr(644,root,root) $4/docs/quake2_manual/images/slime.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/start_network_server_screen1.gif
%attr(644,root,root) $4/docs/quake2_manual/images/stimpack.gif
%attr(644,root,root) $4/docs/quake2_manual/images/story_main.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/strogg_environ_1.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/strogg_environ_2.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/strogg_environ_3.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/supershotgun.gif
%attr(644,root,root) $4/docs/quake2_manual/images/tank.gif
%attr(644,root,root) $4/docs/quake2_manual/images/tank_commander.gif
%attr(644,root,root) $4/docs/quake2_manual/images/technician.gif
%attr(644,root,root) $4/docs/quake2_manual/images/top_nav_imagemap.gif
%attr(644,root,root) $4/docs/quake2_manual/images/unit_exit_door.jpg
%attr(644,root,root) $4/docs/quake2_manual/images/water.jpg
%attr(644,root,root) $4/docs/quake2_manual/intel_brief.html
%attr(644,root,root) $4/docs/quake2_manual/intel_brief2.html
%attr(644,root,root) $4/docs/quake2_manual/intel_brief3.html
%attr(644,root,root) $4/docs/quake2_manual/intel_brief4.html
%attr(644,root,root) $4/docs/quake2_manual/intel_brief5.html
%attr(644,root,root) $4/docs/quake2_manual/intel_brief6.html
%attr(644,root,root) $4/docs/quake2_manual/intel_brief7.html
%attr(644,root,root) $4/docs/quake2_manual/intel_brief8.html
%attr(644,root,root) $4/docs/quake2_manual/intel_brief_enemy.html
%attr(644,root,root) $4/docs/quake2_manual/main.html
%attr(644,root,root) $4/docs/quake2_manual/multiplayer.html
%attr(644,root,root) $4/docs/quake2_manual/page_index.html
%attr(644,root,root) $4/docs/quake2_manual/setup_controls_screenmenus.html
%attr(644,root,root) $4/docs/quake2_manual/story.html
%attr(644,root,root) $4/docs/quake2_manual/technical_information.html
%attr(644,root,root) $4/docs/quake2_manual/top_nav.html

EOF

