int main (int argc, char* argv[]) {

    while (true) {

        J_System::initialise();
        Game::initialise();

        Uint64 performanceFrequency = SDL_GetPerformanceFrequency();
        Uint64 lastCounter = SDL_GetPerformanceCounter();
        Uint64 endCounter = 0;
        Uint64 elapsedCounter = 0;

        float deltaTime = 1.0f / (float)J_System::getFps();

        while (J_System::getState() == J_SYSTEM_STATE_ACTIVE) {

            while (J_System::pollEvent() != 0) {

                SDL_Event event = J_System::getEvent();
                if(event.type == SDL_KEYDOWN) {

                    switch(event.key.keysym.sym) {

                        case (SDLK_RETURN) : { if (!(SDL_GetModState()&KMOD_ALT)) { break; } }
                        case (SDLK_F11) : {

                            J_Window::toggleFullscreen();
                            break;
                        }
                    }
                }

                J_System::handle();
                Game::handle();
            }

            J_System::stepBegin();
            Game::step();
            Game::render();

            endCounter = SDL_GetPerformanceCounter();
            elapsedCounter = endCounter - lastCounter;

            float elapsed = ((float)elapsedCounter / (float)performanceFrequency);
            while (elapsed < deltaTime) {

                float timeLeft = deltaTime - elapsed;
                Uint32 sleep = (Uint32)(1000.0f * timeLeft);
                if (sleep > 0) { SDL_Delay(sleep); }

                elapsedCounter = SDL_GetPerformanceCounter() - lastCounter;
                elapsed = ((float)elapsedCounter / (float)performanceFrequency);
            }

            lastCounter = SDL_GetPerformanceCounter();

            J_System::stepEnd();
        }

        Game::terminate();
        J_System::terminate();

        if (J_System::getState() == J_SYSTEM_STATE_RESETTING) { continue; }
        else { break; }
    }

    return 0;
}
