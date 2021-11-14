#include "Menu.h"

/// <BUTTON> //////////////////////////////////////////////////////////////////

const int BigButton::WIDTH = 112, BigButton::HEIGHT = 112;
const int BigButton::STARTING_Y = -1024, BigButton::ENDING_Y = (480 / 2) + (112 / 2);
const float BigButton::VELOCITY_Y = 0.6;
const float BigButton::TERMINAL_VELOCITY = 21.5;



void BigButton::create (const int arg_x, const int arg_type) {

    // Load and create the buton image.
    image = J_Renderer::createImage("BigButtons");

    // Load and create the button mask.
    mask = J_Renderer::createImage("BigButton_Mask");
    J_Colour maskColour = { 255, 255, 255, 63, SDL_BLENDMODE_BLEND };
    J_Renderer::setImageColour(&mask, maskColour);

    // Set the render flags.
    renderMask = false;
    renderText = false;

    // Set the button position and velocity.
    x = arg_x, y = STARTING_Y - (rand() % 480);
    velY = 0.0;

    // Create and allocate the button sprites.
    sprite = new(std::nothrow) J_Quad[TYPE_TOTAL];
    if (sprite == nullptr) { J_Error::log("GAME_ERROR_BUTTON_ALLOCATE"); }

    for (int i = 0, iy = 0; i < TYPE_TOTAL; ++i, iy += HEIGHT) {

        sprite[i].quad = { 0, iy, WIDTH, HEIGHT };
    }

    // Set the collider.
    collider.quad.quad = { x, y, WIDTH, HEIGHT };
    collider.quad.colour = { 128, 128, 128, 255, SDL_BLENDMODE_BLEND };

    // Load and create all the sounds.
    clickExit = J_Mixer::createSound("Immune");
    clickPlay = J_Mixer::createSound("Healthy");
    clickConfig = J_Mixer::createSound("Sick");
    clickHighscore = J_Mixer::createSound("Corrupt");

    // Set the button type.
    type = arg_type;

    if (type < TYPE_EXIT) { type = TYPE_EXIT; }
    else if (type > TYPE_HIGHSCORE) { type = TYPE_HIGHSCORE; }

    // Set the landed flag.
    landed = false;

    // Create the font.
    font = J_Renderer::createFont("BigNumbers");
}



void BigButton::handle (void (*arg_process) (void)) {

    // If the button was clicked on then call the button's process.
    if (landed) {

        if (J_Collision::handleCollision(Cursor::getX(), Cursor::getY(), collider)) {

            switch (type) {

                // case (TYPE_EXIT) : { J_Mixer::playSound(clickExit, 0); break; }

                case (TYPE_PLAY) : { J_Mixer::playSound(clickPlay, 0); break; }

                case (TYPE_CONFIG) : { J_Mixer::playSound(clickConfig, 0); break; }

                case (TYPE_HIGHSCORE) : { J_Mixer::playSound(clickHighscore, 0); break; }
            }

            (*arg_process)();
        }
    }
}



void BigButton::step (void) {

    // Move the button downwards.
    if (!landed) {

        if (y < ENDING_Y) {

            velY += VELOCITY_Y;
            if (velY > TERMINAL_VELOCITY) { velY = TERMINAL_VELOCITY; }

            y += velY;
            if (y > ENDING_Y) { y = ENDING_Y; }
            collider.quad.quad.y = y;

            landed = false;
        }
        else { landed = true; }
    }
    else {

        // If the mouse is over the button, highlight it.
        if (J_Collision::handleCollision(Cursor::getX(), Cursor::getY(), collider)) { renderMask = true, renderText = true; }
        else { renderMask = false, renderText = false; }
    }
}



void BigButton::render (void) {

    // Render the button.
    J_Renderer::renderImage(image, x, y, &sprite[type]);

    // Render the mask.
    if (renderMask) {

        J_Renderer::renderImage(mask, x, y, nullptr);
    }

    // Render the text based on the button type.
    if (renderText) {

        switch (type) {

            case (TYPE_EXIT) : {

                std::string text = "EXIT";
                J_Renderer::renderFont(font, (640 / 2) - ((text.length() * J_Renderer::getFontCharWidth(font)) / 2), 420, text);

                break;
            }

            case (TYPE_PLAY) : {

                std::string text = "START THE GAME";
                J_Renderer::renderFont(font, (640 / 2) - ((text.length() * J_Renderer::getFontCharWidth(font)) / 2), 420, text);

                break;
            }

            case (TYPE_CONFIG) : {

                std::string text = "OPTIONS";
                J_Renderer::renderFont(font, (640 / 2) - ((text.length() * J_Renderer::getFontCharWidth(font)) / 2), 420, text);

                break;
            }

            case (TYPE_HIGHSCORE) : {

                std::string text = "HIGHSCORES";
                J_Renderer::renderFont(font, (640 / 2) - ((text.length() * J_Renderer::getFontCharWidth(font)) / 2), 420, text);

                break;
            }
        }
    }

    // Render the collider.
    J_Collision::renderCollider(collider);
}



int BigButton::getWidth (void) { return WIDTH; }

int BigButton::getHeight (void) { return HEIGHT; }

bool BigButton::hasLanded (void) const { return landed; }



void BigButton::destroy (void) {

    // Destroy the button image and mask.
    J_Renderer::destroyImage(&image);
    J_Renderer::destroyImage(&mask);

    // Reset the button position and velocity.
    x = 0, y = 0;
    velY = 0.0;

    // Delete and deallocate the button sprites.
    delete[] sprite;
    sprite = nullptr;

    // Destroy the collider.
    collider.quad.quad = { 0, 0, 0, 0 };
    collider.quad.colour = { 0, 0, 0, 255, SDL_BLENDMODE_BLEND };

    // Destroy all the sounds.
    J_Mixer::destroySound(&clickExit);
    J_Mixer::destroySound(&clickPlay);
    J_Mixer::destroySound(&clickConfig);
    J_Mixer::destroySound(&clickHighscore);

    // Reset the button type.
    type = TYPE_PLAY;

    // Reset the landed flag.
    landed = false;

    // Destroy the font.
    J_Renderer::destroyFont(&font);
}

BigButton::~BigButton (void) { destroy(); }

/// <BUTTON> //////////////////////////////////////////////////////////////////

//
//
//
//

/// <MENU> ////////////////////////////////////////////////////////////////////

J_Quad Menu::background;
BigButton* Menu::button = nullptr;
J_Quad Menu::fade;
const Uint8 Menu::FADE_TRANSPARENCY = 255;
const Uint8 Menu::FADE_AMOUNT = 5;
int Menu::state = -1;



void Menu::initialise (void) {

    // Initialise the title.
    Title::initialise();

    // Set the position, diemnsions and colour of the backgroud.
    background.quad = { 0, 0, 640, 480 };
    background.colour = { 29, 25, 16, 255, SDL_BLENDMODE_BLEND };

    // Allocate and create the four buttons.
    button = new(std::nothrow) BigButton[2];
    if (button == nullptr) { J_Error::log("GAME_ERROR_GAME_OVER_BUTTON_ALLOCATE"); }

    button[0].create((640 / 2) - BigButton::getWidth(), BigButton::TYPE_EXIT);
    button[1].create((640 / 2), BigButton::TYPE_PLAY);

    // Set the foreground darkness fade.
    fade.quad = { 0, 0, 640, 480 };
    fade.colour = { 29, 25, 16, 0, SDL_BLENDMODE_BLEND };

    // Set the menu state.
    state = STATE_ACTIVE;
}



void Menu::handle (void) {

    if (state == STATE_ACTIVE) {

        // Handle the buttons' events.
        if (J_System::getEvent().type == SDL_MOUSEBUTTONDOWN) {

            if (J_System::getEvent().button.button == SDL_BUTTON_LEFT) {

                button[BigButton::TYPE_EXIT].handle(&exit);
                button[BigButton::TYPE_PLAY].handle(&play);
                // button[BigButton::TYPE_CONFIG].handle(&config);
                // button[BigButton::TYPE_HIGHSCORE].handle(&highscore);
            }
        }

        // If the user presses any key or mouse button skip parts of the game over screen animation.
        if ((J_System::getEvent().type == SDL_MOUSEBUTTONDOWN) || (J_System::getEvent().type == SDL_KEYDOWN)) {

            // Skip the title falling.
            if (!Title::hasLanded()) {

                for (int i = 0; i < Title::LENGTH; ++i) {

                    Title::letterY[i] = Title::LETTER_ENDING_Y;
                }

                return;
            }

            // Skip the buttons falling.
            for (int i = 0; i < 2; ++i) {

                if (!button[i].hasLanded()) {

                    button[i].y = BigButton::ENDING_Y;
                    button[i].collider.quad.quad.y = button[i].y;
                }
            }
        }
    }
}



void Menu::step (void) {

    if (state == STATE_ACTIVE) {

        // Handle the title's step.
        Title::step();

        // Handle the buttons' step events.
        for (int i = 0; i < 2; ++i) { button[i].step(); }
    }

    // Fade out if necessary.
    if ((state != STATE_ACTIVE) &&
        (state != STATE_RESET) &&
        (state != STATE_CONFIG) &&
        (state != STATE_HIGHSCORE) &&
        (state != STATE_INACTIVE)) {

        // Fade out.
        if (fade.colour.alpha < FADE_TRANSPARENCY) {

            fade.colour.alpha += FADE_AMOUNT;
            if (fade.colour.alpha > FADE_TRANSPARENCY) { fade.colour.alpha = FADE_TRANSPARENCY; }
        }
        else {

            if (state == STATE_CONFIG_TRANS) { state = STATE_CONFIG; }
            else if (state == STATE_HIGHSCORE_TRANS) { state = STATE_HIGHSCORE; }
        }
    }

    // Fade in if necessary.
    if (state == STATE_RESET) {

        if (fade.colour.alpha > 0) {

            fade.colour.alpha -= FADE_AMOUNT;
            if (fade.colour.alpha < 0) { fade.colour.alpha = 0; }
        }
        else { state = STATE_ACTIVE; }
    }
}



void Menu::render (void) {

    // Render the background.
    J_Renderer::drawQuadFilled(background);

    if ((state != STATE_CONFIG) || (state != STATE_HIGHSCORE)) {

        // Render the buttons.
        for (int i = 0; i < 2; ++i) { button[i].render(); }

        // Render the title.
        Title::render();
    }

    // Render the fade out.
    if ((state != STATE_ACTIVE) && (state != STATE_INACTIVE)) { J_Renderer::drawQuadFilled(fade); }
}



void Menu::reset (void) {

    // Reset the foreground darkness fade.
    fade.quad = { 0, 0, 640, 480 };
    fade.colour = { 29, 25, 16, FADE_TRANSPARENCY, SDL_BLENDMODE_BLEND };

    // Reset the menu state.
    state = STATE_RESET;
}



void Menu::exit (void) { state = STATE_EXIT; }

void Menu::play (void) { state = STATE_PLAY; }

void Menu::config (void) { state = STATE_CONFIG_TRANS; }

void Menu::highscore (void) { state = STATE_HIGHSCORE_TRANS; }



void Menu::setInactive (void) { state = STATE_INACTIVE; }



bool Menu::hasFadedOut (void) { return (fade.colour.alpha >= FADE_TRANSPARENCY) ? true : false; }

int Menu::getState (void) { return state; }



void Menu::terminate (void) {

    // Terminate the title.
    Title::terminate();

    // Reset the background quad.
    background.quad = { 0, 0, 0, 0 };
    background.colour = { 0, 0, 0, 255, SDL_BLENDMODE_BLEND };

    // Destroy and deallocate the buttons.
    for (int i = 0; i < 2; ++i) { button[i].destroy(); }

    delete[] button;
    button = nullptr;

    // Reset the foreground fade quad.
    fade.quad = { 0, 0, 0, 0 };
    fade.colour = { 0, 0, 0, 255, SDL_BLENDMODE_BLEND };

    // Reset the state.
    state = -1;
}

/// <TITLE> ///////////////////////////////////////////////////////////////////

J_Image Menu::Title::image;
const int Menu::Title::LENGTH = 10;
J_Quad* Menu::Title::letter = nullptr;
int* Menu::Title::letterY = nullptr;
const int Menu::Title::LETTER_STARTING_Y = -480, Menu::Title::LETTER_ENDING_Y = 32;
const int Menu::Title::LETTER_STARTING_Y_MAX_OFFSET = 640;
float Menu::Title::letterVelY = 0.0;
const float Menu::Title::LETTER_VELOCITY_Y = 0.2;
const float Menu::Title::TERMINAL_VELOCITY = 21.5;
bool Menu::Title::landed = false;



void Menu::Title::initialise (void) {

    // Load and create the title's image.
    image = J_Renderer::createImage("Title");

    // Create and allocate the memory for the the title's letters.
    letter = new(std::nothrow) J_Quad[LENGTH];
    if (letter == nullptr) { J_Error::log("GAME_ERROR_MENU_TITLE_ALLOCATE"); }

    for (int i = 0, x = 0; i < LENGTH; ++i, x += (J_Renderer::getImageWidth(image) / LENGTH)) {

        letter[i].quad = { x, 0, (J_Renderer::getImageWidth(image) / LENGTH), J_Renderer::getImageHeight(image) };
    }

    // Create and allocate the memory for the letters' current y positions.
    letterY = new(std::nothrow) int[LENGTH];
    if (letterY == nullptr) { J_Error::log("GAME_ERROR_MENU_TITLE_POSITION_ALLOCATE"); }

    // Set the letters' starting y positions.
    for (int i = 0; i < LENGTH; ++i) {

        letterY[i] = LETTER_STARTING_Y;
        letterY[i] -= rand() % LETTER_STARTING_Y_MAX_OFFSET;
    }

    // Set the starting values.
    letterVelY = 0.0;
    landed = false;
}



void Menu::Title::step (void) {

    // Move the title's letters downwards.
    if (!landed) {

        landed = true;

        for (int i = 0; i < LENGTH; ++i) {

            if (letterY[i] < LETTER_ENDING_Y) {

                letterVelY += LETTER_VELOCITY_Y;
                if (letterVelY > TERMINAL_VELOCITY) { letterVelY = TERMINAL_VELOCITY; }

                letterY[i] += letterVelY;
                if (letterY[i] > (J_Renderer::getImageHeight(image) / 2)) { letterY[i] = (J_Renderer::getImageHeight(image) / 2); }

                landed = false;
            }
        }
    }
}


void Menu::Title::render (void) {

    // Render the title's letters.
    for (int i = 0, x = (640 / 2) - (J_Renderer::getImageWidth(image) / 2); i < LENGTH; ++i, x += (J_Renderer::getImageWidth(image) / LENGTH)) {

        J_Renderer::renderImage(image, x, letterY[i], &letter[i]);
    }
}



bool Menu::Title::hasLanded (void) { return landed; }



void Menu::Title::terminate (void) {

    // Destroy the title's image.
    J_Renderer::destroyImage(&image);

    // Delete and deallocate the memory for the title's letters.
    delete[] letter;
    letter = nullptr;

    // Delete and deallocate the memory for the title's letter positions.
    delete[] letterY;
    letterY = nullptr;

    // Reset the starting values.
    letterVelY = 0.0;
    landed = false;

}

/// </TITLE> //////////////////////////////////////////////////////////////////

//
//
//
//

/// </MENU> ///////////////////////////////////////////////////////////////////
