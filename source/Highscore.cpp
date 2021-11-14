#include "Highscore.h"

const std::string Highscore::HIGHSCORE_FILE = "Resources\\Data\\Highscores.dat";



bool Highscore::save (const int arg_score) {

    // Open the highscore file and store the data.
    std::fstream highscoreFile(HIGHSCORE_FILE, std::ios::in);
    std::string rawData = "\0";

    if (highscoreFile.is_open()) {

        std::getline(highscoreFile, rawData);
        highscoreFile.close();
    }
    else { J_Error::log("GAME_ERROR_HIGHSCORE_FILE_OPEN"); }

    int highscore[5];

    std::istringstream data(rawData);
    data >> highscore[0] >> highscore[1] >> highscore[2] >> highscore[3] >> highscore[4];


    // Checks to see if the new score is a valid highscore, if so the position is set.
    int position = -1;

    for (int i = 4; i >= 0; --i) {

        if (arg_score > highscore[i]) { position = i; continue; }
        else { break; }
    }


    // If the score is a highscore, insert it in the list and save.
    if (position > -1) {

        for (int i = 4; i >= position; --i) { highscore[i] = highscore[i - 1]; }
        highscore[position] = arg_score;

        std::ostringstream saveData;
        saveData << highscore[0] << " " << highscore[1] << " " << highscore[2] << " " << highscore[3] << " " << highscore[4];

        highscoreFile.open(HIGHSCORE_FILE, std::ios::out);

        if (highscoreFile.is_open()) {

            highscoreFile << saveData.str();
            highscoreFile.close();
        }
        else { J_Error::log("GAME_ERROR_HIGHSCORE_FILE_OPEN"); }
    }

    return (position == 0) ? true : false;
}



std::string Highscore::load (void) {

    // Open the highscore file and load the data in.
    std::ifstream highscoreFile(HIGHSCORE_FILE);
    std::string rawData = "\0";

    if (highscoreFile.is_open()) {

        std::getline(highscoreFile, rawData);
        highscoreFile.close();
    }
    else { J_Error::log("GAME_ERROR_HIGHSCORE_FILE_OPEN"); }

    return rawData;
}



void Highscore::reset (void) {

    // Open the highscore file to fill with empty data..
    std::ofstream highscoreFile(HIGHSCORE_FILE, std::ios::trunc);

    if (highscoreFile.is_open()) {

        highscoreFile << "0 0 0 0 0";
        highscoreFile.close();
    }
    else { J_Error::log("GAME_ERROR_HIGHSCORE_FILE_OPEN"); }
}
