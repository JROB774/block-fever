/// <J_WINDOW> ////////////////////////////////////////////////////////////////

const std::string J_Window::WINDOW_FILE = RES_DIR_DATA "Window.dat";
std::string J_Window::title = "\0";
int J_Window::width = 0, J_Window::height = 0;
int J_Window::screenWidth = 0, J_Window::screenHeight = 0;
int J_Window::desktopWidth = 0, J_Window::desktopHeight = 0;
int J_Window::screenScale = 0;
bool J_Window::fullscreen = false;
SDL_Window* J_Window::window = nullptr;



void J_Window::initialise (void) {

    // If the window is already initialised, end the process.
    if (window != nullptr) { return; }


    int startWidth = 640;
    int startHeight = 480;


    // Open the window data file to extract data.
    std::ifstream windowFile(WINDOW_FILE, std::ifstream::in);

    if (windowFile.is_open()) {

        std::string rawData = "\0";
        std::istringstream data;

        std::getline(windowFile, rawData);
        data.str(rawData);
        data >> title >> screenWidth >> screenHeight;

        windowFile.close();
    }
    else { J_Error::log("J_ERROR_WINDOW_FILE_READ"); }


    // The window itself is created using the informaation gathered from the data file.
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, startWidth, startHeight, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr) { J_Error::log("J_ERROR_WINDOW_CREATE"); }


    // Set the window's scale.
    updateScale(false);


    // Set the window's minimum size to the screen dimensions.
    SDL_SetWindowMinimumSize(window, screenWidth, screenHeight);
}



void J_Window::handle (const SDL_Event& arg_event, const bool arg_debug) {

    // Handle all the window related events.
    if (arg_event.type == SDL_WINDOWEVENT) {

        if (arg_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {

            updateScale(true);
        }
    }

    if (arg_event.type == SDL_KEYDOWN) {

        switch (arg_event.key.keysym.sym) {

            case (SDLK_f) : { toggleFullscreen(); break; }
        }
    }
}



void J_Window::show (void) {

    SDL_ShowWindow(window);
}

void J_Window::hide (void) {

    SDL_HideWindow(window);
}



void J_Window::toggleFullscreen (void) {

    // Toggle the fullscreen value then set the window fullscreen based on what it now is.
    fullscreen = !fullscreen;

    if (fullscreen) { if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0) { J_Error::log("J_ERROR_WINDOW_FULLSCREEN_ON"); } }
    else { if (SDL_SetWindowFullscreen(window, 0) != 0) { J_Error::log("J_ERROR_WINDOW_FULLSCREEN_OFF"); } }
}



void J_Window::updateScale (const bool arg_updateRenderScaleAndViewport) {

    // Calculate the new screen scale based on the current window size.
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    screenScale = 1;
    while(((screenWidth * (screenScale+1)) <= windowWidth) && ((screenHeight * (screenScale+1)) <= windowHeight)) { screenScale++; }

    int screenWidthScaled = screenWidth * screenScale;
    int screenHeightScaled = screenHeight * screenScale;

    // Set the renderer scale and viewport.
    if(arg_updateRenderScaleAndViewport) {

        J_Renderer::setScale(static_cast <float> (screenScale), static_cast <float> (screenScale));
        updateViewport(screenScale);
    }
}

void J_Window::updateViewport (const int arg_screenScale) {

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    int screenWidthScaled = screenWidth * screenScale;
    int screenHeightScaled = screenHeight * screenScale;

    J_Quad viewport;
    viewport.quad.x = ((windowWidth - screenWidthScaled) / 2) / arg_screenScale;
    viewport.quad.y = ((windowHeight - screenHeightScaled) / 2) / arg_screenScale;
    viewport.quad.w = screenWidth;
    viewport.quad.h = screenHeight;

    J_Renderer::setViewport(viewport);
}



int J_Window::getWidth (void) { return width; }

int J_Window::getHeight (void) { return height; }

int J_Window::getScreenWidth (void) { return screenWidth; }

int J_Window::getScreenHeight (void) { return screenHeight; }

int J_Window::getDesktopWidth (void) { return desktopWidth; }

int J_Window::getDesktopHeight (void) { return desktopHeight; }

int J_Window::getScreenScale (void) { return screenScale; }

bool J_Window::getFullscreen (void) { return fullscreen; }

SDL_Window* J_Window::getWindow (void) { return window; }



void J_Window::terminate (void) {

    title = "\0";
    width = 0, height = 0;
    screenWidth = 0, screenHeight = 0;
    desktopWidth = 0, desktopHeight = 0;
    screenScale = 0;
    fullscreen = false;

    SDL_DestroyWindow(window);
    window = nullptr;
}

/// <\J_WINDOW> ///////////////////////////////////////////////////////////////
