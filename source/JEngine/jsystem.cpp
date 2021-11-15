/// <J_SYSTEM> ////////////////////////////////////////////////////////////////

const std::string J_System::SYSTEM_FILE = RES_DIR_DATA "System.dat";
const std::string J_System::CONFIG_FILE = RES_DIR_DATA "Config.dat";
SDL_Event J_System::event;
int J_System::fps = 0, J_System::tpf = 0;
int J_System::frameCount = 0;
double J_System::averageFps = 0.0;
bool J_System::debug = false;
J_SystemState J_System::state = J_SYSTEM_STATE_INACTIVE;



void J_System::initialise (void) {

    // Open the system data file to extract the data.
    std::ifstream systemFile(SYSTEM_FILE, std::ifstream::in);

    if (systemFile.is_open()) {

        std::string rawData = "\0";
        std::istringstream data;

        std::getline(systemFile, rawData);
        data.str(rawData);
        data >> fps >> debug;

        tpf = 1000 / fps;

        systemFile.close();
    }
    else { J_Error::log("J_ERROR_SYSTEM_FILE_READ"); }


    // If the system is not resetting initialise all the SDL sub-systems.
    if (state != J_SYSTEM_STATE_RESETTING) {

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { J_Error::log("J_ERROR_SYSTEM_SDL_INIT"); }
        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0) { J_Error::log("J_ERROR_SYSTEM_MIX_INIT"); }
    }


    // Initialise all the J-Engine sub-systems.
    J_Error::initialise();
    J_Window::initialise();
    J_Renderer::initialise(J_Window::getWindow());
    J_Mixer::initialise();


    // Open the config data file to extract the data.
    std::ifstream configFile(CONFIG_FILE, std::ifstream::in);
    std::string rawData = "\0";

    if (configFile.is_open()) {

        std::getline(configFile, rawData);
        configFile.close();
    }

    std::istringstream data;
    data.str(rawData);

    bool configFullscreen = false;
    int configScale = 0;
    float configSoundVolume = 0.0;
    bool configMuted = false;

    data >> configFullscreen >> configScale >> configSoundVolume >> configMuted;


    // Set some starting values stored in the config file.
    if (configFullscreen && !J_Window::getFullscreen()) { J_Window::toggleFullscreen(); }
    J_Window::setScreenScale(configScale);
    J_Mixer::setSoundVolume(configSoundVolume);
    if (configMuted && !J_Mixer::isMuted()) { J_Mixer::toggleMute(); }


    // Set the system state to active.
    state = J_SYSTEM_STATE_ACTIVE;
}



int J_System::pollEvent (void) {

    // Return the value from SDL's poll event function.
    return SDL_PollEvent(&event);
}



void J_System::handle (void) {

    // Handle the system events.
    switch (event.type) {

        case (SDL_QUIT) : { state = J_SYSTEM_STATE_INACTIVE; break; }

        case (SDL_KEYDOWN) : {

            switch (event.key.keysym.sym) {

                case (SDLK_ESCAPE) : { if (debug) { state = J_SYSTEM_STATE_INACTIVE; } break; }

                case (SDLK_r) : { if (debug) { state = J_SYSTEM_STATE_RESETTING; } break; }
            }

            break;
        }
    }

    // Handle all sub-system events
    if (debug) {

        J_Collision::handle(event);
        J_Mixer::handle(event);
    }

    J_Window::handle(event, debug);
}



void J_System::stepBegin (void) {

    // Set the renderer colour to default and clear the screen.
    J_Renderer::setColour(J_Renderer::getDefaultColour());
    J_Renderer::clear();
}

void J_System::stepEnd (void) {

    // Update the screen with everyting that needs to be rendered.
    J_Renderer::update();

    // Incrment the frame count.
    ++frameCount;
}



void J_System::reset (void) { state = J_SYSTEM_STATE_RESETTING; }

void J_System::exit (void) { state = J_SYSTEM_STATE_INACTIVE; }



SDL_Event J_System::getEvent (void) { return event; }

int J_System::getFps (void) { return fps; }

bool J_System::isDebug (void) { return debug; }

J_SystemState J_System::getState (void) { return state; }



void J_System::terminate (void) {

    // Reset everything.
    frameCount = 0;
    averageFps = 0.0;

    // Terminate all the J-Engine sub-systems.
    J_Mixer::terminate();
    J_Renderer::terminate();
    J_Window::terminate();
    J_Error::terminate();


    // If the system is not resetting then terminate all the SDL sub-systems.
    if (state != J_SYSTEM_STATE_RESETTING) {

        Mix_CloseAudio();
        SDL_Quit();
    }
}

/// </J_SYSTEM> ///////////////////////////////////////////////////////////////
