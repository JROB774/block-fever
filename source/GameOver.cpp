/// <GAME_OVER> ///////////////////////////////////////////////////////////////

J_Quad GameOver::darkness;
const Uint8 GameOver::DARKNESS_TRANSPARENCY = 128;
const Uint8 GameOver::DARKNESS_AMOUNT = 4;
J_Quad* GameOver::bar = nullptr;
J_Font GameOver::bigNumbers;
int GameOver::blocksSaved = 0, GameOver::currentBlocksSaved = 0;
int GameOver::blocksSavedCounter = 0;
J_Sound GameOver::scoreNoise;
Button* GameOver::button = nullptr;
int GameOver::buttonsCounter = 0;
J_Quad GameOver::fade;
const Uint8 GameOver::FADE_TRANSPARENCY = 255;
const Uint8 GameOver::FADE_AMOUNT = 5;
bool GameOver::bestScore = false;
J_Sound GameOver::best;
bool GameOver::bestHasPlayed = false;
int GameOver::bestCounter = 0;
int GameOver::state = -1;



void GameOver::initialise (void) {

    // Initialise the big block.
    BigBlock::initialise();

    // Initialise the title.
    Title::initialise();

    // Set the background darkness quad.
    darkness.quad = { 0, 0, 640, 480 };
    darkness.colour = { 29, 25, 16, 0, SDL_BLENDMODE_BLEND };

    // Create and allocate the memory for the bars.
    bar = new(std::nothrow) J_Quad[2];
    if (bar == nullptr) { J_Error::log("GAME_ERROR_GAME_OVER_BAR_ALLOCATE"); }

    // Set the positions, dimensions and colours of the bars.
    bar[0].quad = { 0, -80, 640, 80 };
    bar[0].colour = { 29, 25, 16, 255, SDL_BLENDMODE_BLEND };

    bar[1].quad = { 0, 480, 640, 80 };
    bar[1].colour = { 29, 25, 16, 255, SDL_BLENDMODE_BLEND };

    // Load and create the font.
    bigNumbers = J_Renderer::createFont("BigNumbers");

    // Set the number of blocks saved to default.
    blocksSaved = 0;
    currentBlocksSaved = 0;

    // Set the counter to wait for before the saved blocks are counted.
    blocksSavedCounter = 60;

    // Set the score sound.
    scoreNoise = J_Mixer::createSound("Score");

    // Allocate and create the three buttons.
    button = new(std::nothrow) Button[Button::TYPE_TOTAL];
    if (button == nullptr) { J_Error::log("GAME_ERROR_GAME_OVER_BUTTON_ALLOCATE"); }

    for (int i = 0, ix = (((640 / 2) + Button::getWidth()) - 10); i < Button::TYPE_TOTAL; ++i, ix -= (Button::getWidth() + 10)) {

        button[i].create(ix, 480 + 256, i);
    }

    // Set the counter to wait before the buttons move in.
    buttonsCounter = 60;

    // Set the foreground darkness fade.
    fade.quad = { 0, 0, 640, 480 };
    fade.colour = { 29, 25, 16, 0, SDL_BLENDMODE_BLEND };

    // Set the best score values.
    bestScore = false;
    best = J_Mixer::createSound("Best");
    bestHasPlayed = false;
    bestCounter = 10;

    // Set the game over state to running.
    state = STATE_RUNNING;
}



void GameOver::handle (void) {

    // Handle the buttons' events.
    if (J_System::getEvent().type == SDL_MOUSEBUTTONDOWN) {

        if (J_System::getEvent().button.button == SDL_BUTTON_LEFT) {

            button[Button::TYPE_RESTART].handle(&restart);
            button[Button::TYPE_MENU].handle(&menu);
            button[Button::TYPE_QUIT].handle(&exit);
        }
    }

    // If the user presses any key or mouse button skip parts of the game over screen animation.
    if ((J_System::getEvent().type == SDL_MOUSEBUTTONDOWN) || (J_System::getEvent().type == SDL_KEYDOWN)) {

        // Skip the big block, title and bars moving into the screen.
        if (!BigBlock::hasLanded() || !Title::hasLanded()) {

            BigBlock::y = BigBlock::ENDING_Y;
            for (int i = 0; i < Title::LENGTH; ++i) { Title::letterY[i] = Title::LETTER_ENDING_Y; }

            bar[0].quad.y = 0;
            bar[1].quad.y = (480 - bar[1].quad.h);

            return;
        }

        // Skip the saved blocks number counting upwards.
        if (currentBlocksSaved != blocksSaved) {

            blocksSavedCounter = 0;
            currentBlocksSaved = blocksSaved;
            BigBlock::convertCounter = 0;

            return;
        }

        bool buttonsLanded = false;
        for (int i = 0; i < Button::TYPE_TOTAL; ++i) { if (button[i].hasLanded()) { buttonsLanded = true; } }

        if (!buttonsLanded) {

            buttonsCounter = 0;

            for (int i = 0; i < Button::TYPE_TOTAL; ++i) {

                button[i].y = Button::ENDING_Y;
                button[i].collider.quad.quad.y = button[i].y;
            }

            return;
        }
    }
}



void GameOver::step (void) {

    // Fade the background darkness in.
    if (darkness.colour.alpha < DARKNESS_TRANSPARENCY) {

        darkness.colour.alpha += DARKNESS_AMOUNT;
    }

    // Move the bars in from the bottom and top of the screen.
    if (bar[0].quad.y < 0) { bar[0].quad.y += 4; }
    if (bar[1].quad.y > (480 - bar[1].quad.h)) { bar[1].quad.y -= 4; }

    // Handle the big block's step.
    BigBlock::step();

    // Handle the title's step.
    Title::step();

    // Countdown the blocks saved counter if everything has landed.
    if (BigBlock::hasLanded() && (Title::hasLanded())) {

        if (blocksSavedCounter <= 0) {

            // When the counter is done count up the blocks saved.
            if (currentBlocksSaved < blocksSaved) {

                J_Mixer::playSound(scoreNoise, 0);
                ++currentBlocksSaved;
            }
        }
        else { --blocksSavedCounter; }
    }

    // Handle the button's step events.
    if ((blocksSavedCounter == 0) && (currentBlocksSaved == blocksSaved)) {

        if (buttonsCounter == 0) {

            for (int i = 0; i < Button::TYPE_TOTAL; ++i) {

                button[i].step();
            }
        }
        else { --buttonsCounter; }
    }

    // Fade out if neccessary.
    if ((state == STATE_RESTART) || (state == STATE_MENU)) {

        if (fade.colour.alpha < FADE_TRANSPARENCY) {

            fade.colour.alpha += FADE_AMOUNT;
            if (fade.colour.alpha > FADE_TRANSPARENCY) { fade.colour.alpha = FADE_TRANSPARENCY; }
        }
    }

    // Play the sound if a new best score was obtained.
    // if (currentBlocksSaved == (blocksSaved - 1)) { J_Mixer::playSound(best, 0); }
}



void GameOver::render (void) {

    // Draw the background darkness.
    J_Renderer::drawQuadFilled(darkness);

    // Render the big block.
    BigBlock::render();

    // Render the bars.
    for (int i = 0; i < 2; ++i) { J_Renderer::drawQuadFilled(bar[i]); }

    // Render the buttons.
    for (int i = 0; i < Button::TYPE_TOTAL; ++i) { button[i].render(); }

    // Render the title.
    Title::render();

    // If the counter is done counting then render the blocks saved.
    if (blocksSavedCounter <= 0) {

        std::ostringstream data;
        data << currentBlocksSaved;

        J_Renderer::renderFont(bigNumbers, (640 / 2) - ((data.str().length() * J_Renderer::getFontCharWidth(bigNumbers)) / 2), (480 / 2) + (112 / 2), data.str());
    }

    // Render the best score text if this is the new best score.
    if (blocksSavedCounter <= 0) {

        if (currentBlocksSaved == blocksSaved) {

            if (bestScore) {

                if (bestCounter <= 0) {

                    std::string newBest = "NEW BEST";

                    J_Renderer::renderFont(bigNumbers, (640 / 2) - ((newBest.length() * J_Renderer::getFontCharWidth(bigNumbers)) / 2),
                                           (480 / 2) + ((112 / 2) + (J_Renderer::getFontCharHeight(bigNumbers))), newBest);

                    if (!bestHasPlayed) {

                        J_Mixer::playSound(best, 0);
                        bestHasPlayed = true;
                    }
                }
                else { --bestCounter; }
            }
        }
    }

    // Render the fade out.
    if ((state == STATE_RESTART) || (state == STATE_MENU)) { J_Renderer::drawQuadFilled(fade); }
}



void GameOver::reset (void) {

    terminate();
    initialise();
}



void GameOver::restart (void) { state = STATE_RESTART; }

void GameOver::menu (void) { state = STATE_MENU; }

void GameOver::exit (void) { state = STATE_EXIT; }



void GameOver::setBestScore (const bool arg_best_score) { bestScore = arg_best_score; }

void GameOver::setBlocksSaved (const int arg_blocks_saved) {

    blocksSaved = arg_blocks_saved;

    if (J_System::isDebug()) {

        std::ofstream file("Scores.log", std::ios::app);

        if (file.is_open()) {

            file << arg_blocks_saved << "\n";
            file.close();
        }
        else { printf("Couldn't open the 'Score.log' file!"); }
    }
}



bool GameOver::hasFadedOut (void) { return (fade.colour.alpha >= FADE_TRANSPARENCY) ? true : false; }

int GameOver::getState (void) { return state; }



void GameOver::terminate (void) {

    // Terminate the big block.
    BigBlock::terminate();

    // Terminate the title.
    Title::terminate();

    // Reset the background darkness quad.
    darkness.quad = { 0, 0, 0, 0 };
    darkness.colour = { 0, 0, 0, 255, SDL_BLENDMODE_BLEND };

    // Delete and deallocate the bars.
    delete[] bar;
    bar = nullptr;

    // Destroy the font.
    J_Renderer::destroyFont(&bigNumbers);

    // Reset the number of blocks saved.
    blocksSaved = 0;
    currentBlocksSaved = 0;

    // Reset the blocks saved counter.
    blocksSavedCounter = 0;

    // Destroy the score sound.
    J_Mixer::destroySound(&scoreNoise);

    // Destroy and deallocate the buttons.
    for (int i = 0; i < Button::TYPE_TOTAL; ++i) { button[i].destroy(); }
    delete[] button;
    button = nullptr;

    // Reset the buttons' counter.
    buttonsCounter = 0;

    // Reset the foreground fade quad.
    fade.quad = { 0, 0, 0, 0 };
    fade.colour = { 0, 0, 0, 255, SDL_BLENDMODE_BLEND };

    // Reset the best values.
    bestScore = false;
    J_Mixer::destroySound(&best);
    bestHasPlayed = false;
    bestCounter = 0;

    // Reset the game over state.
    state = -1;
}



/// <BIG_BLOCK> ///////////////////////////////////////////////////////////////

J_Image GameOver::BigBlock::image;
J_Animation GameOver::BigBlock::idle;
J_Animation GameOver::BigBlock::convert;
J_Animation GameOver::BigBlock::healthy, GameOver::BigBlock::sick, GameOver::BigBlock::corrupt;
int GameOver::BigBlock::y = 0;
const int GameOver::BigBlock::STARTING_Y = -1024, GameOver::BigBlock::ENDING_Y = (480 / 2) - (112 / 2);
float GameOver::BigBlock::velY = 0.0;
const float GameOver::BigBlock::VELOCITY_Y = 0.6;
const float GameOver::BigBlock::TERMINAL_VELOCITY = 21.5;
bool GameOver::BigBlock::landed = false;
int GameOver::BigBlock::convertCounter = 0;



void GameOver::BigBlock::initialise (void) {

    // Load and create the big block image.
    image = J_Renderer::createImage("BigBlock");

    // Load and create the animations.
    idle = J_Renderer::createAnimation("BigBlockIdle");
    convert = J_Renderer::createAnimation("BigBlockConvert");

    healthy = J_Renderer::createAnimation("BigBlockHealthy");
    sick = J_Renderer::createAnimation("BigBlockSick");
    corrupt = J_Renderer::createAnimation("BigBlockCorrupt");

    // Set the starting values.
    y = STARTING_Y;
    velY = 0.0;
    landed = false;
    convertCounter = 60;
}



void GameOver::BigBlock::step (void) {

    // Move the big block downwards.
    if (!landed) {

        if (y < ENDING_Y) {

            velY += VELOCITY_Y;
            if (velY > TERMINAL_VELOCITY) { velY = TERMINAL_VELOCITY; }

            y += velY;
            if (y > ENDING_Y) { y = ENDING_Y; }

            landed = false;
        }
        else { landed = true; }
    }
}



void GameOver::BigBlock::render (void) {

    // Render the big block.
    if (GameOver::currentBlocksSaved != GameOver::blocksSaved) {

        J_Renderer::renderImage(image, (640 / 2) - (112 / 2), y, J_Renderer::playAnimation(&idle));
    }
    else {

        if (landed) {

            if (convertCounter <= 0) {

                J_Renderer::renderImage(image, (640 / 2) - (112 / 2), y, J_Renderer::playAnimation(&convert));

                if (J_Renderer::isAnimationDone(convert)) {

                    if (GameOver::blocksSaved >= 120) { J_Renderer::renderImage(image, (640 / 2) - (112 / 2), y, J_Renderer::playAnimation(&healthy)); }
                    else if (GameOver::blocksSaved >= 55) { J_Renderer::renderImage(image, (640 / 2) - (112 / 2), y, J_Renderer::playAnimation(&sick)); }
                    else { J_Renderer::renderImage(image, (640 / 2) - (112 / 2), y, J_Renderer::playAnimation(&corrupt)); }
                }
            }
            else {

                J_Renderer::renderImage(image, (640 / 2) - (112 / 2), y, J_Renderer::playAnimation(&idle));
                --convertCounter;
            }
        }
    }
}



bool GameOver::BigBlock::hasLanded (void) { return landed; }



void GameOver::BigBlock::terminate (void) {

    // Destroy the big block image.
    J_Renderer::destroyImage(&image);

    // Destroy the animations.
    J_Renderer::destroyAnimation(&idle);
    J_Renderer::destroyAnimation(&convert);

    J_Renderer::destroyAnimation(&healthy);
    J_Renderer::destroyAnimation(&sick);
    J_Renderer::destroyAnimation(&corrupt);

    // Reset the values.
    y = 0;
    velY = 0.0;
    landed = false;
    convertCounter = 0;
}

/// </BIG_BLOCK> //////////////////////////////////////////////////////////////

//
//
//
//

/// <TITLE> ///////////////////////////////////////////////////////////////////

J_Image GameOver::Title::image;
const int GameOver::Title::LENGTH = 8;
J_Quad* GameOver::Title::letter = nullptr;
int* GameOver::Title::letterY = nullptr;
const int GameOver::Title::LETTER_STARTING_Y = -128, GameOver::Title::LETTER_ENDING_Y = 32;
const int GameOver::Title::LETTER_STARTING_Y_MAX_OFFSET = 640;
float GameOver::Title::letterVelY = 0.0;
const float GameOver::Title::LETTER_VELOCITY_Y = 0.2;
const float GameOver::Title::TERMINAL_VELOCITY = 21.5;
bool GameOver::Title::landed = false;



void GameOver::Title::initialise (void) {

    // Load and create the title's image.
    image = J_Renderer::createImage("GameOver");

    // Create and allocate the memory for the the title's letters.
    letter = new(std::nothrow) J_Quad[LENGTH];
    if (letter == nullptr) { J_Error::log("GAME_ERROR_GAME_OVER_TITLE_ALLOCATE"); }

    for (int i = 0, x = 0; i < LENGTH; ++i, x += (J_Renderer::getImageWidth(image) / LENGTH)) {

        letter[i].quad = { x, 0, (J_Renderer::getImageWidth(image) / LENGTH), J_Renderer::getImageHeight(image) };
    }

    // Create and allocate the memory for the letters' current y positions.
    letterY = new(std::nothrow) int[LENGTH];
    if (letterY == nullptr) { J_Error::log("GAME_ERROR_GAME_OVER_TITLE_POSITION_ALLOCATE"); }

    // Set the letters' starting y positions.
    for (int i = 0; i < LENGTH; ++i) {

        letterY[i] = LETTER_STARTING_Y;
        letterY[i] -= rand() % LETTER_STARTING_Y_MAX_OFFSET;
    }

    // Set the starting values.
    letterVelY = 0.0;
    landed = false;
}



void GameOver::Title::step (void) {

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



void GameOver::Title::render (void) {

    // Render the title's letters.
    for (int i = 0, x = (640 / 2) - (J_Renderer::getImageWidth(image) / 2); i < LENGTH; ++i, x += (J_Renderer::getImageWidth(image) / LENGTH)) {

        J_Renderer::renderImage(image, x, letterY[i], &letter[i]);
    }
}



bool GameOver::Title::hasLanded (void) { return landed; }



void GameOver::Title::terminate (void) {

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

/// </GAME_OVER> //////////////////////////////////////////////////////////////
