#include "Game.h"

/// <GAME> ////////////////////////////////////////////////////////////////////

void Game::initialise (void) {

    // Set a random seed based on the current time.
    srand(static_cast <unsigned int> (time(nullptr)));

    // Initialise everything for the game.
    Cursor::initialise();
    Menu::initialise();
    Stage::initialise();
    GameOver::initialise();
}



void Game::handle (void) {

    // Handle all game events.
    Cursor::handle();

    if (Menu::getState() == Menu::STATE_ACTIVE) { Menu::handle(); }
    else {

        if (Stage::getState() != Stage::STATE_INACTIVE) { Stage::handle(); }
        else {

            if (GameOver::getState() == GameOver::STATE_RUNNING) { GameOver::handle(); }
        }
    }
}



void Game::step (void) {

    // Step through everything in the game.
    if (Menu::getState() != Menu::STATE_INACTIVE) {

        Menu::step();

        // Based on the button pressed on the main menu screen, do an action.
        switch (Menu::getState()) {

            case (Menu::STATE_EXIT) : { J_System::exit(); break; }

            case (Menu::STATE_PLAY) : {

                if (Menu::hasFadedOut()) {

                    Menu::setInactive();
                    Stage::generate();
                    Pause::reset();
                }

                break;
            }
        }
    }
    else {

        if (Stage::getState() != Stage::STATE_INACTIVE) {

            Stage::step();

            switch (Stage::getState()) {

                case (Stage::STATE_MENU) : { if (Stage::hasFadedOut()) { Menu::reset(); } break; }

                case (Stage::STATE_EXIT) : { J_System::exit(); break; }
            }
        }
        else {

            if (GameOver::getState() != GameOver::STATE_INACTIVE) {

                GameOver::step();

                // Based on the button pressed on the game over screen, do an action.
                switch (GameOver::getState()) {

                    case(GameOver::STATE_RESTART) : {

                        if (GameOver::hasFadedOut()) {

                            GameOver::reset();
                            Stage::generate();
                            Pause::reset();
                        }

                        break;
                    }

                    case(GameOver::STATE_MENU) : {

                        if (GameOver::hasFadedOut()) {

                            GameOver::reset();
                            Menu::reset();
                        }

                        break;
                    }

                    case(GameOver::STATE_EXIT) : { J_System::exit(); break; }
                }
            }
        }
    }
}



void Game::render (void) {

    // Render everything in the game.
    if (Menu::getState() != Menu::STATE_INACTIVE) { Menu::render(); }
    else {

        Stage::render();

        if (Stage::getState() == Stage::STATE_INACTIVE) {

            if (GameOver::getState() != GameOver::STATE_INACTIVE) { GameOver::render(); }
        }
    }

    Cursor::render();
}



void Game::terminate (void) {

    // Terminate everything in the game.
    GameOver::terminate();
    Stage::terminate();
    Menu::terminate();
    Cursor::terminate();
}

/// </GAME> ///////////////////////////////////////////////////////////////////
