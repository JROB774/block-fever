#ifndef INCLUDE_HIGHSCORE
#define INCLUDE_HIGHSCORE

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
        // Set the highscore value.
        //
        static void setScore(const int);

        // DESCRIPTION:
        // Get the highscore value.
        //
        static int getScore(void);

        /// DESCRIPTION:
        // Save the highscore to the file.
        //
        /// RETURN VALUES:
        // True if this is the new best score, false if not.
        //
        static bool addScore(const int);

        /// DESCRIPTION:
        // Reset the saved highscore.
        //
        static void reset(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~Highscore() = delete;

    private:

        static int highscore;
};

#endif // INCLUDE_HIGHSCORE
