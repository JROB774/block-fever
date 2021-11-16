/// <SAVE> ////////////////////////////////////////////////////////////////////

const std::string Save::SAVE_FILE = "save.dat";

const bool Save::DEFAULT_FULLSCREEN = false;
const int Save::DEFAULT_WINDOW_WIDTH = 0;
const int Save::DEFAULT_WINDOW_HEIGHT = 0;
const int Save::DEFAULT_HIGHSCORE = 0;

bool Save::fullscreen;
int Save::highscore;

void Save::step () {

    // Checks if any of the valus the save system cares about have changed this frame, and if they have it saves them out.
    bool changed = false;

    bool currFullscreen = J_Window::getFullscreen();
    if (fullscreen != currFullscreen) {

        fullscreen = currFullscreen;
        changed = true;
    }

    int currHighscore = Highscore::getScore();
    if (highscore != currHighscore) {

        highscore = currHighscore;
        changed = true;
    }

    if (changed) { save(); }
}

void Save::load () {

    int windowWidth = DEFAULT_WINDOW_WIDTH;
    int windowHeight = DEFAULT_WINDOW_HEIGHT;

    fullscreen = DEFAULT_FULLSCREEN;
    highscore = DEFAULT_HIGHSCORE;

    std::fstream file(FILESYS_NAME(SAVE_FILE), std::ios::in);

    // If there's no save file we just use the default values.
    if(file.is_open()) {

        file >> fullscreen
             >> windowWidth
             >> windowHeight
             >> highscore;
        file.close();
    }

    // We never start in fullscreen on web as it causes some problems!
    #ifdef PLATFORM_WEB
    fullscreen = false;
    #endif

    J_Window::setWidth(windowWidth); // Needs to be before fullscreen to set correctly!
    J_Window::setHeight(windowHeight); // Needs to be before fullscreen to set correctly!
    J_Window::setFullscreen(fullscreen);

    Highscore::setScore(highscore);

    FILESYS_SYNC();
}

void Save::save () {

    int windowWidth = J_Window::getWidth();
    int windowHeight = J_Window::getHeight();

    std::fstream file(FILESYS_NAME(SAVE_FILE), std::ios::out);

    if(file.is_open()) {

        file << fullscreen << " "
             << windowWidth << " "
             << windowHeight << " "
             << highscore;
        file.close();
    }
    else { J_Error::log("GAME_ERROR_SAVE"); }

    FILESYS_SYNC();
}

/// </SAVE> ///////////////////////////////////////////////////////////////////
