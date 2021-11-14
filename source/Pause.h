#ifndef INCLUDE_PAUSE
#define INCLUDE_PAUSE

/// <PAUSE> ///////////////////////////////////////////////////////////////////

class Pause
{
    public:

        enum PauseState
        {
            STATE_ACTIVE,
            STATE_MENU,
            STATE_EXIT
        };

        /// DESCRIPTION:
        // The constructor.
        //
        Pause(void) = delete;
        Pause(const Pause&) = delete;
        Pause(Pause&&) = delete;

        /// DESCRIPTION:
        // The assignment operator.
        //
        Pause& operator=(const Pause&) = delete;
        Pause& operator=(Pause&&) = delete;

        /// DESCRIPTION:
        // Initialise the pause screen.
        //
        static void initalise(void);

        /// DESCRIPTION:
        // Handle all pause events.
        //
        static void handle(void);

        /// DESCRIPTION:
        // Iterate through the pause step.
        //
        static void step(void);

        /// DESCRIPTION:
        // Render the pause screen.
        //
        static void render(void);

        /// DESCRIPTION:
        // For a button.
        //
        static void menu(void);
        static void exit(void);

        /// DESCRIPTION:
        // Reset the pause screen.
        //
        static void reset(void);

        /// DESCRIPTION:
        // Get the current state.
        //
        /// RETURN VALUES:
        // The current state.
        //
        static int getState(void);

        /// DESCRIPTION:
        // Terminate the pause screen.
        //
        static void terminate(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~Pause(void) = delete;

    private:

        // The title image.
        static J_Image title;
        // The quad that is used to render the darkness fade/background.
        static J_Quad darkness;
        // The black bars on the pause screen.
        static J_Quad* bar;
        // The pause screen buttons.
        static Button* button;
        // The current pause state.
        static int state;
};

/// </PAUSE> //////////////////////////////////////////////////////////////////

#endif // INCLUDE_PAUSE
