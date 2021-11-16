@echo off

set Libraries=-s USE_SDL=2 -s USE_SDL_MIXER=2 -lidbfs.js

set IncludeDirs=-I source\Depends\SDL2\include\SDL2 -I source\Depends\SDL2\include -I source\Depends\SDL2_mixer\include -I source\Depends\STB

set Defines=-D PLATFORM_WEB

set CompilerFlags=-std=c++17
set LinkerFlags=-s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS="['_main','_main_start']" -s EXPORTED_RUNTIME_METHODS="['ccall']"

set AssetPath=assets

set InputSource=source\Main.cpp

set OutputPath=binary\web\
set OutputName=BlockFever

set OutputExecutable=%OutputPath%%OutputName%

set Version=1.1.0
