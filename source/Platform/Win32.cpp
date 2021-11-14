int main (int argc, char* argv[]) {

    while (true) {

        J_System::initialise();
        Game::initialise();
        J_System::getFpsTimer()->start();

        while (J_System::getState() == J_SYSTEM_STATE_ACTIVE) {

            J_System::getCapTimer()->start();

            while (J_System::pollEvent() != 0) {

                J_System::handle();
                Game::handle();
            }

            J_System::stepBegin();
            Game::step();
            Game::render();
            J_System::stepEnd();
        }

        Game::terminate();
        J_System::terminate();

        if (J_System::getState() == J_SYSTEM_STATE_RESETTING) { continue; }
        else { break; }
    }

    if (J_System::isDebug()) { std::cin.get(); }
    return 0;
}
