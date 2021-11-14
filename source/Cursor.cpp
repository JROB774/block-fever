/// <CURSOR> //////////////////////////////////////////////////////////////////

int Cursor::x = 0, Cursor::y = 0;
J_Image Cursor::image;



void Cursor::initialise (void) {

    // Hide the default cursor.
    SDL_ShowCursor(SDL_DISABLE);
    if (SDL_ShowCursor(SDL_QUERY) != 0) { J_Error::log("GAME_ERROR_CURSOR_HIDE"); }

    // Create the new cursor image.
    image = J_Renderer::createImage("Cursor");
}



void Cursor::handle (void) {

    // If the mouse moved store the position.
    if (J_System::getEvent().type == SDL_MOUSEMOTION) { SDL_GetMouseState(&x, &y); }
}



void Cursor::render (void) {

    // Render the new cursor over the hidden default one, at the center.
    J_Renderer::renderImage(image, x - (J_Renderer::getImageWidth(image) / 2), y - (J_Renderer::getImageHeight(image) / 2), nullptr);
}



int Cursor::getX (void) { return x; }

int Cursor::getY (void) { return y; }



void Cursor::terminate (void) {

    // Destroy the new cursor image.
    J_Renderer::destroyImage(&image);

    // Show the default cursor.
    SDL_ShowCursor(SDL_ENABLE);
    if (SDL_ShowCursor(SDL_QUERY) != 1) { J_Error::log("GAME_ERROR_CURSOR_SHOW"); }
}

/// </CURSOR> /////////////////////////////////////////////////////////////////
