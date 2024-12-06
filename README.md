# GDENG03 Game Engine
Developed by: 
- Marcus Leocario
---

This program is a work in progress; it must be compiled to run. 

The entry file for the program is `main.cpp`. 

## Unreal Engine `.level` Parser
To run the Unreal Engine parser, import LevelParser.cpp, LevelParser.h, and LevelParser.uasset. A capsule .obj is included and should be placed in Content\Meshes\Capsule.obj. 
Then, run the LevelParser blueprint in the editor. Input a directory for the level to load by copying it as path in the Windows File Explorer.
To save the level, only a folder directory is required.

## Unity Engine `.level` Parser
To run the Unity Engine parser, add LevelParser.cs to the project. The menu is accessible 
in the Unity toolbar. The save and load options will open a file explorer for you.