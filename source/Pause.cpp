/// <PAUSE> ///////////////////////////////////////////////////////////////////

J_Image Pause::title;
J_Quad Pause::darkness;
J_Quad* Pause::bar = nullptr;
Button* Pause::button = nullptr;
int Pause::state = -1;



void Pause::initalise (void) {

    // Load and create the pause title image.
    title = J_Renderer::createImage("Paused");

    // Create the darkness background.
    darkness.quad = { 0, 0, 640, 480 };
    darkness.colour = { 29, 25, 16, 128, SDL_BLENDMODE_BLEND };

    // Create and allocate the memory for the bars.
    bar = new(std::nothrow) J_Quad[2];
    if (bar == nullptr) { J_Error::log("GAME_ERROR_PAUSE_BAR_ALLOCATE"); }

    // Set the positions, dimensions and colours of the bars.
    bar[0].quad = { 0, 0, 640, 80 };
    bar[0].colour = { 29, 25, 16, 255, SDL_BLENDMODE_BLEND };

    bar[1].quad = { 0, 400, 640, 80 };
    bar[1].colour = { 29, 25, 16, 255, SDL_BLENDMODE_BLEND };

    // Create and allocate the memory for the buttons.
    button = new(std::nothrow) Button[2];
    if (button == nullptr) { J_Error::log("GAME_ERROR_PAUSE_BUTTON_ALLOCATE"); }

    // We don't want exit button on the web build.
    #ifdef PLATFORM_WEB
    button[0].create(((640 / 2) - (Button::getWidth() / 2)) - 5, 480 - (86 + 15), Button::TYPE_MENU);
    button[1].create(9999, 9999, Button::TYPE_QUIT); // Off-screen!
    #else
    button[0].create(((640 / 2) - Button::getWidth()) - 5, 480 - (86 + 15), Button::TYPE_MENU);
    button[1].create((640 / 2) + 5, 480 - (86 + 15), Button::TYPE_QUIT);
    #endif

    // Set the state.
    state = STATE_ACTIVE;
}



void Pause::handle (void) {

    // Handle button events.
    if (J_System::getEvent().type == SDL_MOUSEBUTTONDOWN) {

        if (J_System::getEvent().button.button == SDL_BUTTON_LEFT) {

            button[0].handle(&menu);
            button[1].handle(&exit);
        }
    }
}



void Pause::step (void) {

    // Go through the buttons' steps.
    for (int i = 0; i < 2; ++i) { button[i].step(); }
}



void Pause::render (void) {

    // Render the background.
    J_Renderer::drawQuadFilled(darkness);

    // Draw the black bars on the top and bottom of the screen.
    for (int i = 0; i < 2; ++i) { J_Renderer::drawQuadFilled(bar[i]); }

    // Render the buttons
    for (int i = 0; i < 2; ++i) { button[i].render(); }

    // Render the pause title.
    J_Renderer::renderImage(title, (640 / 2) - (J_Renderer::getImageWidth(title) / 2), (J_Renderer::getImageHeight(title) / 2), nullptr);
}



void Pause::menu (void) { state = STATE_MENU; }

void Pause::exit (void) { state = STATE_EXIT; }



void Pause::reset (void) { state = STATE_ACTIVE; }



int Pause::getState (void) { return state; }



void Pause::terminate (void) {

    // Destroy the pause title image.
    J_Renderer::destroyImage(&title);

    // Destroy the darkness background.
    darkness.quad = { 0, 0, 0, 0 };
    darkness.colour = { 0, 0, 0, 255, SDL_BLENDMODE_BLEND };

    // Delete and deallocate the bars.
    delete[] bar;
    bar = nullptr;

    // Destroy and dealloate the buttons.
    for (int i = 0; i < 2; ++i) { button[i].destroy(); }

    delete[] button;
    button = nullptr;

    // Reset the state.
    state = -1;
}

/// </PAUSE> //////////////////////////////////////////////////////////////////
