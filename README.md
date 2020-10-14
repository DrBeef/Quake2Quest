Quake2Quest
==========

Welcome to the first (and only I believe) full 6DoF implementation of the Quake 2 Engine in VR.

This is built solely for the Oculus Quest VR HMD and will *not* run on any other device.

The easiest way to install this on your Quest is using SideQuest, a Desktop app designed to simplify sideloading apps and games ( even beat saber songs on quest ) on Standalone Android Headsets like Oculus Quest and Oculus Go. It supports drag and drop for installing APK files!

Download SideQuest here:
https://github.com/the-expanse/SideQuest/releases



IMPORTANT NOTE
--------------

This is just an engine port; though the apk does contain the shareware version of Quake2, not the full game. If you wish to play the full game you must purchase it yourself, steam is most straightforward:  https://store.steampowered.com/app/2320/QUAKE_II/


Copying the Full Game PAK files to your Oculus Quest
----------------------------------------------------

Copy the PAK files from the installed Quake2 game folder on your PC to the /Quake2Quest folder on your Oculus Quest when it is connected to the PC. You have to have run Quake2Quest at least once for the folder to be created and if you don't see it when you connect your Quest to the PC you might have to restart the Quest.



Caveats
-------

This version of Quake2Quest is now updated and based on the excellent Yamagi Quake 2 Engine (https://www.yamagi.org/quake2/). The original project this port is _very_ loosely based on the Quake 2 port created by Stefan Welker for the Open Dive VR headset (https://www.durovis.com/en/opendive.html), however that build has been deprecated.


WARNING:  There is a good chance that unless you have your VR-legs this will probably make you feel a bit sick. The moment you start to feel under the weather YOU MUST STOP PLAYING for a good period of time before you try again. I will not be held responsible for anyone making themselves ill.


Controls
--------

All these controls are for right-handed mode (vr_control_scheme 0), if you wish to use a left-handed control scheme then add the following to the config.cfg file and all buttons/sticks/controls will be switched:

```
set vr_control_scheme "10" 
```

* Open the in-game menu with the left-controller menu button (same irrespective of right/left handed control)
* A Button - Crouch
* B Button - Jump
* Y Button - Show inventory screen (use up and down on the right stick to select inventory item and fire to select)
* X Button - Show the "Help Computer" whilst X is pressed
* Dominant-Hand Controller - Weapon orientation
* Dominant-Hand Thumbstick - left/right Snap turn, up/down weapon change
* Dominant-Hand Thumbstick click - change the laser-sight mode on/off
* Dominant-Hand Trigger - Fire
* Dominant Grip Button - Not used
* Off-Hand Controller - Direction of movement (or if configured in config.cfg HMD direction is used)
* Off-Hand Thumbstick - locomotion
* Off-Hand Trigger - Run
* Off-Hand Grip Button - Weapon Stabilisation - with the machine gun this will reduce the scatter of the projectiles
* Off-Hand Thumbstick click - If cheats are enabled then this will give you ALL pickups/weapons


Useful CVARs
------------

You can set a cvar in the config.cfg in the following manner:

```
set vr_snapturn_angle  "5"
```

|cvar|description|
| --- | --- |
|cheats|If set to 1 then you can click the off-hand thumbstick button to activate "give all", giving you all weapons, pickups etc|
|vr_snapturn_angle|Sets the angle of the snap turn, set to a value < 10 for smooth turning|
|vr_walkdirection|Set to 1 for HMD oriented movement direction|
|vr_control_scheme|Sets the control scheme (default: 0 - Right-handed, 10 - Left handed)|
|vr_height_adjust|Allows you to set a height adjustment (for seated play) value in metres|
|vr_comfort_mask|Enables the movement comfort mask for those who are sensitive to VR sickness (0.0 - 1.0)

Things to note / FAQs:
----------------------

* Mods and Texture packs *do now work*
* The Original Soundtrack in OGG format *does now work too*!
* Multiplayer is unlikely to work very well, if at all I'm afraid. I explain reasons why can be seen here (they apply to this as well as Lambda1VR):  https://www.reddit.com/r/Lambda1VR/comments/dtutnx/so_whats_with_the_head_aiming_in_multiplayer/
* The folder into which the pak files from the full game and other things like mods and the OST shoud be copied is now called _Quake2Quest_, this is to avoid collision with the older configuration files for the previous version, it also means if you did prefer the vanilla version, you can roll back and all your saves will be intact.

Notes for Users of First released Version
-----------------------------------------

The 2nd release of Quake2Quest updates the underlying engine to Yamagi. This has a number of benefits including but not limited to modding, music support and a reworked save system. However as previously mentioned save files will not be compatible between these two versions. Moving forward any updates to the application will not break save files. To avoid conflicts and to also allow you to revert to the original version should you feel it necessary, there is a new file structure. If you have copied across the full game this will need to be redone. Complete list of installation instructions below:

1) Install the game via SideQuest or by downloading and installing the APK file
2) Run the game once
3) If you own a legal copy of Quake 2, you should copy all .pak files from baseq2 to the newly created Quake2Quest folder on your Quest. 
Optional:
4) If you wish to enjoy the Quake 2 soundtrack you can place the relevant OGG files in the folder Quake2Quest/music.

Known Issues:
-------------

* Left-handed laser sight is still not aligned correctly, I will fix at some point
* Any save games from the previous version will *NOT* work, this is due to the engine change. 
* As mentioned, multiplayer probably doesn't work very well at all, if at all..


Credits:
--------

The game includes Hi Res textures, skins and items previously collected by the user Realistic. We could not find the original author of these weapons, nor does the pack include any licensing at all. If you are the author of these textures please feel free to contact us and we would be happy to credit you or remove.

I would like to thank the following teams and individual for making this possible:

* Emile Belanger - For advice regarding converting the Android build of Yamagi. See his other Android ports [here](http://www.beloko.com/)
* [The Yamagi Team](https://www.yamagi.org/quake2/) - For the excellent engine this based upon.
* Baggyg - My long-time VR friend whose roles in this have been varied and all helpful, also the creator of excellent websites/artwork/assets for this mod as well as altering models to be more VR friendly
* The [SideQuest](https://sidequestvr.com/#/news) team - For making it easy for people to install this
* GLE4ES for the OpenGL -> OpenGLES2 translation: without which this project wouldn't have worked at all: https://github.com/ptitSeb/gl4es


Building:
---------

You need the following:

* Android Developer Studio
* Android SDK API level 24
* Latest Android Native Development Kit
* Oculus Mobile SDK 1.24.0
* The Quake2Quest folder cloned from GitHub should be below VrSamples in the extracted SDK
* Create a local.properties file in the root of the extracted Oculus Mobile SDK that contains the ndk.dir and sdk.dir properties for where your SDK/NDK are located (see Gradle documentation regarding this)
* To build debug you will need a _android.debug.keystore_ file placed in the following folder:
_oculus_sdk_dir_/VrSamples/Quake2Quest/Projects/Android
