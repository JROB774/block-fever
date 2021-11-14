#ifndef INCLUDE_HIGHSCORE
#define INCLUDE_HIGHSCORE

#include "jsystem.h"

class Highscore
{
    public:

        /// DESCRIPTION:
        // The constructor.
        //
        Highscore() = delete;
        Highscore(const Highscore&) = delete;
        Highscore(Highscore&&) = delete;

        /// DESCRIPTION:
        // The assignment operator.
        //
        Highscore& operator=(const Highscore&) = delete;
        Highscore& operator=(Highscore&&) = delete;

        /// DESCRIPTION:
        // Save the highscore to the file.
        //
        /// RETURN VALUES:
        // True if this is the new best score.
        // False if it is not.
        static bool save(const int);

        /// DESCRIPTION:
        // Load the highscores from the file.
        //
        static std::string load(void);

        /// DESCRIPTION:
        // Reset the saved highscores.
        //
        static void reset(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~Highscore() = delete;

    private:

        // The highscore save file.
        static const std::string HIGHSCORE_FILE;
};

#endif // INCLUDE_HIGHSCORE
