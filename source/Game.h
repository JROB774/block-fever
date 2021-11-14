#ifndef INCLUDE_GAME
#define INCLUDE_GAME

/// <GAME> ////////////////////////////////////////////////////////////////////

class Game
{
    public:

        /// DESCRIPTION:
        // The constructor.
        //
        Game(void) = delete;
        Game(const Game&) = delete;
        Game(Game&&) = delete;

        /// DESCRIPTION:
        // The assignment operator.
        //
        Game& operator=(const Game&) = delete;
        Game& operator=(Game&&) = delete;

        /// DESCRIPTION:
        // Initialise the game and all the system's sub-systems.
        //
        static void initialise(void);

        /// DESCRIPTION:
        // Handle all the game events.
        //
        static void handle(void);

        /// DESCRIPTION:
        // The step to be played every frame of the game.
        //
        static void step(void);

        /// DESCRIPTION:
        // Render everything in the game.
        //
        static void render(void);

        /// DESCRIPTION:
        // Terminate the game and all the system's sub-systems.
        //
        static void terminate(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~Game(void) = delete;
};

/// </GAME> ///////////////////////////////////////////////////////////////////

#endif // INCLUDE_GAME
