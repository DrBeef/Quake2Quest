Quake2Quest
==========

Welcome to the first (and only I think!) 6DoF implementation of the Quake2 Engine, using DarkPlaces as a base for this port.

I am quite pleased with how this has turned out. Getting this to work as a 6DoF game was a bit of a faff, and it isn't perfect (see known issues), but I think you'll agree it's good enough and also very good fun to play.

The easiest way to install this on your Quest is using SideQuest, a Desktop app designed to simplify sideloading apps and games ( even beat saber songs on quest ) on Standalone Android Headsets like Oculus Quest and Oculus Go. It supports drag and drop for installing APK files!

Download SideQuest here:
https://github.com/the-expanse/SideQuest/releases



IMPORTANT NOTE:
---------------

This is just an engine port, the apk does contain the shareware version of Quake2, not the full game. If you wish to play the full game you must purchase it yourself (https://store.steampowered.com/app/2310/QUAKE/).

Copying the Full Game PAK files to your Oculus Quest
----------------------------------------------------
Copy the PAK files from the installed Quake2 game folder on your PC to the Quake2Quest/id1 folder on your Oculus Quest when it is connected to the PC. You have to have run Quake2Quest at least once for the folder to be created and if you don't see it when you connect your Quest to the PC you might have to restart the Quest.

This port DOES support mods, an excellent resource for finding out what you can do is here: https://www.reddit.com/r/quake2gearvr/

Bear in mind that the above sub-reddit is for the Gear VR version, which is not dramatically different, but the folder in which game data/saves etc resides is now Quake2Quest instead of QGVR.


Controls:
---------

* Open the in-game menu with the left-controller menu button
* Left Thumbstick - locomotion
* Right Thumbstick - Turn (if configured to do so in the options)
* A Button - Jump
* B Button - Adjust pitch of weapon to your preference (saved in config)
* Y Button - Bring up the text input "keyboard"
* Dominant Hand Controller - Weapon orientation
* Dominant-Hand trigger - Fire
* Off-Hand Controller - Direction of movement (if configured in settings, otherwise HMD direction is used by default)
* Off-hand Trigger - Run
* Grip Buttons - Switch next/previous weapon
* Right-thumbstick click change the laser-sight mode 

Inputting Text:
---------------

- Press Y to bring up the "keyboard" and Y again to exit text entry mode
- Push left or right thumbstick to select the character in that location in the little diagram, selected character is shown for left right controller below the character layout diagram
- Press grip trigger on each controller to cycle through the available characters for that controller
- Press X to toggle SHIFT on and off
- Press Trigger on the appropriate controller to type the selected character (or select center character if no thumbstick direction is pushed)
- Press B to Delete characters
- Press A for Enter/Return


Things to note / FAQs:
----------------------
* You are the weapon.. to make it truly 6DoF the location of the weapon is what the engine understands to be the player. So you can peek round corners and enemies won't spot you, but if you poke the gun round to shoot, they'll see you.
* The original soundtrack can work, you can find details here: https://www.reddit.com/r/quake2gearvr/comments/7r9eri/got_the_musicsoundtrack_working/
* You can change the right-thumbstick turn mode in the Options -> Controller menu, but be warned possible nausea awaits
* You can change handed-ness (for you left handers) in the Controller settings menu
* By default the direction of movement is where the HMD is facing, this can be changed in the menu to the direction the off-hand controller is facing (strafe-tastic)
* You can change supersampling in the commandline.txt file, though by default it is already set to 1.3, you won't get much additional clarity increasing it more and may adversely affect performance
* A number of the controller buttons are currently unmapped; future updates may give them function (see future to-dos on console commands for example)
* You can now use text input - Please see V1.1.0 release notes for instructions

Known Issues:
-------------
* If you use dpmod, you know that it applies an extra weapon offset (to the right); I've tried and failed to correct it, so for now the weapon doesn't line up with the controller at all, though the laser sight is correct
* Laser Sight out of alignment when very close to wall/object

Future To-Dos:
--------------
* Add an off-hand world entity - such as Flashlight or the HUD
* Left-handed mode needs to have the axe model reflected and a mod created so it uses the left-hand model rather than the right

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

Alternatively you can use the docker image created by BrainSlugs83 which can be found here: https://github.com/BrainSlugs83/DockerOvrSdk

