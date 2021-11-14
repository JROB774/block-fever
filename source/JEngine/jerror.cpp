#include "jerror.h"

/// <J_ERROR> /////////////////////////////////////////////////////////////////

const std::string J_Error::ERROR_FILE = "Resources\\Data\\Error.dat";
const std::string J_Error::ERROR_LOG = "Error.log";
int J_Error::total = 0;
std::unordered_map <std::string, std::string> J_Error::error;



void J_Error::initialise (void) {

    // If the error system is already initialised, end the process.
    if (!error.empty()) { return; }


    // Open the error data file and count how many lines are inside it.
    std::ifstream errorFile(ERROR_FILE, std::ifstream::in);

    if (errorFile.is_open()) {

        std::string dummy = "\0";
        while (std::getline(errorFile, dummy)) { ++total; }
    }
    else { initialiseError(); }


    // Store the data of each individual line as its own string, in an array.
    std::string* line = new(std::nothrow) std::string[total];
    if (line == nullptr) { initialiseError(); }

    errorFile.clear();
    errorFile.seekg(0, std::ifstream::beg);

    if (errorFile.is_open()) {

        for (int i = 0; i < total; ++i) { std::getline(errorFile, line[i]); }
        errorFile.close();
    }
    else { initialiseError(); }


    // Split each line into its key and content and store them both in seperate arrays.
    std::string* key = new(std::nothrow) std::string[total];
    std::string* content = new(std::nothrow) std::string[total];
    if ((key == nullptr) || (content == nullptr)) { initialiseError(); }

    for (int i = 0; i < total; ++i) {

        char* data = new(std::nothrow) char[line[i].length() + 1];
        if (data == nullptr) { initialiseError(); }

        strcpy(data, line[i].c_str());

        key[i] = strtok(data, "=");
        content[i] = strtok(nullptr, "=");

        delete[] data;
        data = nullptr;
    }


    // Deallocate the memory used to store the raw line data.
    delete[] line;
    line = nullptr;


    // Store the keys and the contents within the error data map, ready for use.
    for (int i = 0; i < total; ++i) { error.insert({ key[i], content[i] }); }


    // Deallocate the old key and content data arrays.
    delete[] key;
    key = nullptr;
    delete[] content;
    content = nullptr;
}



void J_Error::log (const std::string arg_key) {

    // If the error system has not been initialised then exit with a failure state.
    if (error.empty()) { logError(); }


    // Store the specified error key selected, if it does not exist set it to be an unknown error.
    std::string key = arg_key;
    if (error.count(key) == 0) { key = "J_ERROR_UNKNOWN"; }


    // Extract the error content, linked to the key, and split it into its two components. (output message, error type)
    char* data = new(std::nothrow) char[error.at(key).length() + 1];
    if (data == nullptr) { logError(); }
    strcpy(data, error.at(key).c_str());

    std::string output = strtok(data, ":");
    int type = atoi(strtok(nullptr, ":"));

    delete[] data;
    data = nullptr;


    // Open the error log (create it if it does not exist) and write the error data to it.
    std::ofstream errorLog(ERROR_LOG, std::ofstream::out | std::ofstream::app);

    if (errorLog.is_open()) {

        errorLog << output;

        switch (type) {

            case (J_ERROR_TYPE_SDL) : { errorLog << " (" << SDL_GetError() << ")"; break; }
            case (J_ERROR_TYPE_IMG) : { errorLog << " (" << IMG_GetError() << ")"; break; }
            case (J_ERROR_TYPE_MIX) : { errorLog << " (" << Mix_GetError() << ")"; break; }
        }

        errorLog << "\n";
        errorLog.close();
    }
    else { logError(); }


    // Display an error message box and terminate with a failure state.
    MessageBox(nullptr, "An error has occured!\nCheck the 'Error.log' for more details.", "J-Engine Error", MB_OK);
    exit(EXIT_FAILURE);
}



void J_Error::terminate (void) {

    // Reset all the error data.
    total = 0;
    if (!error.empty()) { error.clear(); }
}



inline void J_Error::initialiseError (void) {

    MessageBox(nullptr, "Could not initialise the J_Error sub-system!", "J-Engine Error", MB_OK);
    exit(EXIT_FAILURE);
}

inline void J_Error::logError (void) {

    MessageBox(nullptr, "Could not log an error to the error log!", "J-Engine Error", MB_OK);
    exit(EXIT_FAILURE);
}

/// </J_ERROR> ////////////////////////////////////////////////////////////////
