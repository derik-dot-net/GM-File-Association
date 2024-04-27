<p align="center"><img src="https://raw.githubusercontent.com/derik-dot-net/GM-File-Association/main/file_association_logo.png" style="display:block; margin:auto;"></p>
<h1 align="center">Windows file association for Gamemaker by <b>Derik.NET</b></h1>

[![Made with GameMaker Studio 2](https://img.shields.io/badge/Made%20with-GameMaker_Studio_2-000000.svg?style=plastic&logo=data%3Aimage%2Fpng%3Bbase64%2CiVBORw0KGgoAAAANSUhEUgAAAA4AAAAOCAMAAAAolt3jAAAAZlBMVEX%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2BrG8stAAAAIXRSTlMABg0OFBkfcn1%2Bf4CBgoOFhoeIiouWmNDa5ebp8PX2%2B%2F6o6Vq%2BAAAAY0lEQVR42k2OWQ6AIAwFn%2BIOioobrnD%2FS4o0EeanmQxNAdErRFTWtsFq6%2BiiZozz0CSnTjYBwo0RkF8DWDLf51Ni9K%2FYdq0Fy3KAfzk97M7goK1F%2F4rGH9Kk1OlboQtEDIrmC%2BU3CVxTr%2FRMAAAAAElFTkSuQmCC)](https://www.yoyogames.com/gamemaker)
[![Discord](https://img.shields.io/discord/956865439156273204?label=Discord)](https://discord.gg/w8znaPQJYf)
[![License: CC0-1.0](https://img.shields.io/badge/License-CC0_1.0-lightgrey.svg)](http://creativecommons.org/publicdomain/zero/1.0/)

## Features & Uses

- Define a custom file extension in Windows.
- Define a Program ID, File Type, Content Type, and Percieved Type for your file extension.
- Ability to click files with that extension to open them in your game/program.
- Give Windows context to what your custom files are.
- Define an icon that Windows will show on files using the extension.
- Force icon cache refresh on Windows (optional).


## FAQ

#### What does this do?
File Association allows you to define a custom file extension which Windows will recognize as being associated with your program or game. This can be used for save or project files, for example, that when clicked will open your program. Another benefit of this is that you can provide an icon that will be shown on all files with your defined file extension.

#### How does it work?
First the script will check if a file exists inside of your program directory, this file tells the system if File Association has already been setup. Due to the nature of this system, you do not want to run it when not needed, feel free to implement a different way to check this. 

After that the system generates a PowerShell script using strings that gets saved as a .ps1 file. This script forces Windows to refresh its Icon Cache that you can see changes made by this system immediately. This part of the process is option.

Then the system generates a Batch file also using strings that gets saved into a .bat file. This Batch file checks for admin permisions, as they are required on most systems to manipulate the Registry, an action which is common, necessary, and standard practice for ANY program that does this, even Gamemaker itself.

If admin permisions are not present then the script will close the game/program and re-launch it prompting the user to run the program with administator privileges. Assuming the user does it then generates the rest of the batch file which contains all of the necessary commands to setup file association in the registry as well as to run the PowerShell refresh icons script if enabled. 

The script is executed using the execute_shell_simple extension. On sucessful completion the script creates the previously mentioned flag file in the program directory of your game/program, and an end-user would never need this process to run again.

#### Why would you need this for Gamemaker?
Despite the sometimes very simplified reputation of the engine, many of Gamemakers more advanced users have created things such as level editors (both 2D  & 3D), photo editors, music editors, emulators, and much more all within Gamemaker. I myself (Derik) created this for use in a VTT (Virtual-table-top) program [Derik's VTT](https://github.com/derik-dot-net/Deriks-VTT) that I originally made for use in a Dungeons & Dragons campaign, for which I am the Dungeon Master.  I wanted this feature so I could save the state of a game session, and then simply click on the save file to resume from where we left off, with no other setup necessary. This feature was something I foresaw as very useful in some upcoming projects I had in mind.

#### What platforms are supported?
As of release this has only been tested on two Windows 10 systems of my own, but this should also work on Windows 11. As people use this system I hope to update this section, and possibly provide a more broad support with confirmed uses.
## Required Extensions
 - [YellowAfterLife's execute_shell_simple Extension](https://yellowafterlife.itch.io/gamemaker-execute-shell-simple)
## Acknowledgements
First to implement File Association w/ Gamemaker:
[Juju Adams](https://github.com/JujuAdams)

His implementation: [JujuAdam's Furballs Implementation](https://jujuadams.itch.io/furballs)

Made possible with YellowAfterLife's extension: 
[YellowAfterLife](https://github.com/YellowAfterlife)



## Installation

Simply download the .yympps package file, along with the required extensions, import and add them to your project.

Make sure to disable file system sandbox, which you'll find in Game Options under Windows in the General tab, after that you're set.

## Important Notes on Usage

USE AT YOUR OWN RISK 

When using this system it is likely not a good idea to run this system unless your game/program has been compiled and installed. Running this script while testing from inside of Gamemaker can have unintended and/or unwanted results and effects such as some of the problems listed below:

This system and the inherit way the file association is setup in Windows, despite that fact that many programs commonly do it, is inheritly dangerous if misused. One could hypothetically use this system to overwrite pre-existing file associations which could cause many issues, and be hard and time-consuming to reverse. Please test extensively before releasing any project that uses this system. 

When I tested this system I repeatedly uninstalled, re-compiled, and re-installed my project to ensure that it worked correctly. If your project is in a late enough stage to need the functionality provided by this system, I'd imagine this is a process you're willing to perform. 

To view the changes made in the Windows Registry simple press WIN+R on your keyboard and type in regedit before pressing enter to open the Registry Editor. Here you should find two entries under HKEY_CLASSES_ROOT. One entry will be your file extension, and the other will be named what you provided for the Program ID. Sometimes for testing purposes, you may want to remove or view these entries in the Registry.
## Known Issues
I found that on occasion the part of this system that forces the program to close and reopen with admin permissions will fail. From what I've seen it will succeed on the next launch of the program if this happens.  
## Support

For problems or questions, please [generate an issue](https://github.com/derik-dot-net/GM-File-Association/issues) here on Github. 

Also feel free to contact me on [Discord](https://discord.gg/w8znaPQJYf).

## License
GM File Association by Derik.NET is marked with CC0 1.0 Universal. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/
