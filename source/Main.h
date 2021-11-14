#ifndef INCLUDE_MAIN
#define INCLUDE_MAIN

#ifdef PLATFORM_WEB
#include <emscripten.h>
#endif

#include <cstring>
#include <ctime>
#include <cstdlib>

#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC

#include <stb_image.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "JEngine/jrender.h"
#include "JEngine/jtime.h"
#include "JEngine/jerror.h"
#include "JEngine/jcollision.h"
#include "JEngine/jwindow.h"
#include "JEngine/jaudio.h"
#include "JEngine/jsystem.h"

#include "Button.h"
#include "Pause.h"
#include "Block.h"
#include "Cursor.h"
#include "Highscore.h"
#include "Game.h"
#include "GameOver.h"
#include "Menu.h"
#include "Stage.h"
#include "Platform.h"

#endif // INCLUDE_MAIN
