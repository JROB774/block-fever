void main_loop () {

    static Uint64 performanceFrequency = SDL_GetPerformanceFrequency();
    static Uint64 lastCounter = SDL_GetPerformanceCounter();
    static Uint64 endCounter = 0;
    static Uint64 elapsedCounter = 0;

    static float updateTimer = 0.0f;

    float updateRate = 1.0f / (float)J_System::getFps();

    while (J_System::pollEvent() != 0) {

        J_System::handle();
        Game::handle();
    }

    bool updated = false;
    while(updateTimer >= updateRate) {

        J_System::stepBegin();
        Game::step();
        Game::render();
        updateTimer -= updateRate;
        updated = true;
    }

    endCounter = SDL_GetPerformanceCounter();
    elapsedCounter = endCounter - lastCounter;
    lastCounter = SDL_GetPerformanceCounter();

    updateTimer += (float)elapsedCounter / (float)performanceFrequency;

    if(updated) {

        J_System::stepEnd();
    }
}

void main_start_cpp () {

    J_System::initialise();
    Game::initialise();

    J_Window::show();

    emscripten_set_main_loop(main_loop, -1, 1);
}

extern "C" {

    void main_start () {

        main_start_cpp();
    }

    int main (int argc, char* argv[]) {

        EM_ASM(
            FS.mkdir("/BLOCK");
            FS.mount(IDBFS, {}, "/BLOCK");
            FS.syncfs(true, function(err) {

                assert(!err);
                ccall("main_start");
            });
        );

        return 0;
    }
}
