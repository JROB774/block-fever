#ifndef INCLUDE_MENU
#define INCLUDE_MENU

/// <BUTTON> //////////////////////////////////////////////////////////////////

class BigButton
{
    // All menus have access to private members.
    friend class MenuHighscore;
    friend class Menu;

    public:

        /// DESCRIPTION:
        // The different types of button.
        //
        enum BigButtonType
        {
            TYPE_EXIT,
            TYPE_PLAY,
            TYPE_CONFIG,
            TYPE_HIGHSCORE,
            TYPE_TOTAL
        };

        /// DESCRIPTION:
        // The constructor.
        //
        BigButton(void) = default;
        BigButton(const BigButton&) = delete;
        BigButton(BigButton&&) = delete;

        /// DESCRIPTION:
        // The assignment operator.
        //
        BigButton& operator=(const BigButton&) = delete;
        BigButton& operator=(BigButton&&) = delete;

        /// DESCRIPTION:
        // Create a button.
        //
        /// ARGUMENTS:
        // The position coordinates for the button.
        //
        void create(const int, const int);

        /// DESCRIPTION:
        // Handle user input on the button.
        // If the button is clicked call the function assigned to the button.
        //
        /// ARGUMENTS:
        // The button's function.
        //
        void handle(void (*)(void));

        /// DESCRIPTION:
        // Iterate through the button's step.
        //
        void step(void);

        /// DESCRIPTION:
        // Render the button.
        //
        void render(void);

        /// DESCRIPTION:
        // Get the dimensions of the button.
        //
        /// RETURN VALUES
        // The button's dimensions.
        //
        static int getWidth(void);
        static int getHeight(void);

        /// DESCRIPTION:
        // Get whether the button has landed or not.
        //
        bool hasLanded(void) const;

        /// DESCRIPTION:
        // Destroy a button.
        //
        void destroy(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~BigButton(void);

    private:

        // The button dimensions.
        static const int WIDTH, HEIGHT;
        // The starting and ending vertical positions.
        static const int STARTING_Y, ENDING_Y;
        // The vertical velocity.
        static const float VELOCITY_Y;
        // The terminal velocity.
        static const float TERMINAL_VELOCITY;

        // The button image.
        J_Image image;
        // The button mask.
        J_Image mask;
        // The flag stating whetehr to render the mask or not.
        bool renderMask;
        // The flag stating whether to render the text or not.
        bool renderText;
        // The position coordinates.
        int x, y;
        // The current vertical velocity.
        float velY;
        // The different button sprites.
        J_Quad* sprite;
        // The box collider.
        J_Collider collider;
        // The different click sounds.
        J_Sound clickExit, clickPlay, clickConfig, clickHighscore;
        // The button type.
        int type;
        // The flag stating whether the button has landed or not.
        bool landed;
        // The button font.
        J_Font font;
};

/// </BUTTON> /////////////////////////////////////////////////////////////////

//
//
//
//

/// <MENU> ////////////////////////////////////////////////////////////////////

class Menu
{
    public:

        /// DESCRIPTION:
        // The different states the menu can be in.
        //
        enum MenuState
        {
            STATE_ACTIVE,
            STATE_EXIT,
            STATE_PLAY,
            STATE_CONFIG_TRANS,
            STATE_CONFIG,
            STATE_HIGHSCORE_TRANS,
            STATE_HIGHSCORE,
            STATE_RESET,
            STATE_INACTIVE
        };

        /// DESCRIPTION:
        // The constructor.
        //
        Menu(void) = delete;
        Menu(const Menu&) = delete;
        Menu(Menu&&) = delete;

        /// DESCRIPTION:
        // The assignment operator.
        //
        Menu& operator=(const Menu&) = delete;
        Menu& operator=(Menu&&) = delete;

        /// DESCRIPTION:
        // Initialise the main menu.
        //
        static void initialise(void);

        /// DESCRIPTION:
        // Handle all menu related events.
        //
        static void handle(void);

        /// DESCRIPTION:
        // Step through everything in the menu.
        //
        static void step(void);

        /// DESCRIPTION:
        // Render the menu.
        //
        static void render(void);

        /// DESCRIPTION:
        // Reset the menu.
        //
        static void reset(void);

        /// DESCRIPTION:
        // Exit the game.
        // A process to be assigned to a button.
        //
        static void exit(void);

        /// DESCRIPTION:
        // Play the game.
        // A process to be assigned to a button.
        //
        static void play(void);

        /// DESCRIPTION:
        // Go to the config screen.
        // A process to be assigned to a button.
        //
        static void config(void);

        /// DESCRIPTION:
        // Go to the highscore screen.
        // A process to be assigned to a button.
        //
        static void highscore(void);

        /// DESCRIPTION:
        // Set the menu to inactive.
        //
        static void setInactive(void);

        /// DESCRIPTION:
        // Get whether the main menu screen has faded out or not.
        //
        /// RETUNR VALUES:
        // True if the main menu screen has faded out.
        // False if the main menu screen has not faded out.
        //
        static bool hasFadedOut(void);

        /// DESCRIPTION:
        // Get the menu's current state.
        //
        /// RETUNR VALUES:
        // The menu's current state.
        //
        static int getState(void);

        /// DESCRIPTION:
        // Terminate the main menu.
        //
        static void terminate(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~Menu(void) = delete;

    private:

        // The background quad.
        static J_Quad background;
        // The menu buttons.
        static BigButton* button;
        // The fade out after selecting a button
        static J_Quad fade;
        // The level of transparency on the fade out.
        static const Uint8 FADE_TRANSPARENCY;
        // The amount to fade out per frame.
        static const Uint8 FADE_AMOUNT;
        // The current state.
        static int state;

        /// <TITLE> ///////////////////////////////////////////////////////////

        class Title
        {
            // Menu has access to private members.
            friend class Menu;

            public:

                /// DESCRIPTION:
                // The constructor.
                //
                Title(void) = delete;
                Title(const Title&) = delete;
                Title(Title&&) = delete;

                /// DESCRIPTION:
                // The assignment operator.
                //
                Title& operator=(const Title&) = delete;
                Title& operator=(Title&&) = delete;

                /// DESCRIPTION:
                // Initialise the title.
                //
                static void initialise(void);

                /// DESCRIPTION:
                // Iterate through the title's step.
                //
                static void step(void);

                /// DESCRIPTION:
                // Render the title to the game over screen.
                //
                static void render(void);

                /// DESCRIPTION:
                // Make the title land straight away.
                //
                static void land(void);

                /// DESCRIPTION:
                // Get whether the title has landed or not.
                //
                /// RETURN VALUES:
                // True if the title has landed.
                // False if the title has not landed.
                //
                static bool hasLanded(void);

                /// DESCRIPTION:
                // Terminate the title.
                //
                static void terminate(void);

                /// DESCRIPTION:
                // The destructor.
                //
                ~Title(void);

            private:

                // The menu title image.
                static J_Image image;
                // The length of the title.
                static const int LENGTH;
                // The individual letters of the title.
                static J_Quad* letter;
                // The letters' current vertical position.
                static int* letterY;
                // The letters' starting and ending vertical positions.
                static const int LETTER_STARTING_Y, LETTER_ENDING_Y;
                // The maximum offset for a letter's starting y position.
                static const int LETTER_STARTING_Y_MAX_OFFSET;
                // The current vertical velocity of all the letters.
                static float letterVelY;
                // The vertical velocity of the letters.
                static const float LETTER_VELOCITY_Y;
                // The terminal velocity of the letters.
                static const float TERMINAL_VELOCITY;
                // The flag stating whether the title has landed or not.
                static bool landed;
        };

        /// </TITLE> //////////////////////////////////////////////////////////
};

/// </MENU> ///////////////////////////////////////////////////////////////////

#endif // INCLUDE_MENU
