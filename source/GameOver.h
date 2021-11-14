#ifndef INCLUDE_GAME_OVER
#define INCLUDE_GAME_OVER

#include "Button.h"
#include "Highscore.h"

/// <GAME_OVER> ///////////////////////////////////////////////////////////////

class GameOver
{

    public:

        /// DESCRIPTION:
        // The different states of the game over.
        //
        enum GameOverState
        {
            STATE_RUNNING,
            STATE_RESTART,
            STATE_MENU,
            STATE_EXIT,
            STATE_INACTIVE
        };

        /// DESCRIPTION:
        // The constructor.
        //
        GameOver(void) = delete;
        GameOver(const GameOver&) = delete;
        GameOver(GameOver&&) = delete;

        /// DESCRIPTION:
        // The assignment operator.
        //
        GameOver& operator=(const GameOver&) = delete;
        GameOver& operator=(GameOver&&) = delete;

        /// DESCRIPTION:
        // Initialise the game over screen.
        //
        static void initialise(void);

        /// DESCRIPTION:
        // Handle all game over screen events.
        //
        static void handle(void);

        /// DESCRIPTION:
        // Iterate through the game over screen.
        //
        static void step(void);

        /// DESCRIPTION:
        // Render everything in the game over screen.
        //
        static void render(void);

        /// DESCRIPTION:
        // Reset the game over to it's initial starting state.
        //
        static void reset(void);

        /// DESCRIPTION:
        // Restart the game.
        // A process to be assigned to a button.
        //
        static void restart(void);

        /// DESCRIPTION:
        // Go to the menu.
        // A process to be assigned to a button.
        //
        static void menu(void);

        /// DESCRIPTION:
        // Exit the game.
        // A process to be assigned to a button.
        //
        static void exit(void);

        /// DESCRIPTION:
        // Set whether it is the new best score or not.
        //
        static void setBestScore(const bool);

        /// DESCRIPTION:
        // Set the blocks saved in the stage.
        //
        /// RETURN VALUES:
        // The number of blocks saved.
        //
        static void setBlocksSaved(const int);

        /// DESCRIPTION:
        // Get whether the game over screen has faded out or not.
        //
        /// RETUNR VALUES:
        // True if the game over screen has faded out.
        // False if the game over screen has not faded out.
        //
        static bool hasFadedOut(void);

        /// DESCRIPTION:
        // Get the game over screen's current state.
        //
        /// RETURN VALUES:
        // The current game over state.
        //
        static int getState(void);

        /// DESCRIPTION:
        // Terminate the game over screen.
        //
        static void terminate(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~GameOver(void) = delete;

    private:

        // The quad that is used to render the darkness fade/background.
        static J_Quad darkness;
        // The level of transparency on the background darkness.
        static const Uint8 DARKNESS_TRANSPARENCY;
        // The amount to fade in the darkness by per frame.
        static const Uint8 DARKNESS_AMOUNT;
        // The black bars on the game over screen.
        static J_Quad* bar;
        // The big numbers font.
        static J_Font bigNumbers;
        // The number of healthy blocks saved.
        static int blocksSaved, currentBlocksSaved;
        // The counter to wait for before the saved blocks are counted.
        static int blocksSavedCounter;
        // The sound played each time the score counts up.
        static J_Sound scoreNoise;
        // The game over buttons.
        static Button* button;
        // The counter to wait before the buttons are moved in.
        static int buttonsCounter;
        // The fade out after restarting or going to the menu.
        static J_Quad fade;
        // The level of transparency on the fade out.
        static const Uint8 FADE_TRANSPARENCY;
        // The amount to fade out per frame.
        static const Uint8 FADE_AMOUNT;
        // The flag stating whether it's the new best score or not.
        static bool bestScore;
        // The sound to play when a new best score is achieved.
        static J_Sound best;
        // The flag that makes sure the sound is played once.
        static bool bestHasPlayed;
        // The counter.
        static int bestCounter;
        // The current state of the game over screen.
        static int state;

        /// <BIG_BLOCK> ///////////////////////////////////////////////////////

        class BigBlock
        {
            // Game Over has access to private members.
            friend class GameOver;

            public:

                /// DESCRIPTION:
                // The constructor.
                //
                BigBlock(void) = delete;
                BigBlock(const BigBlock&) = delete;
                BigBlock(BigBlock&&) = delete;

                /// DESCRIPTION:
                // The assignment operator.
                //
                BigBlock& operator=(const BigBlock&) = delete;
                BigBlock& operator=(BigBlock&&) = delete;

                /// DESCRIPTION:
                // Initialise the big block.
                //
                static void initialise(void);

                /// DESCRIPTION:
                // Iterate through the big block's step.
                //
                static void step(void);

                /// DESCRIPTION:
                // Render the big block.
                //
                static void render(void);

                /// DESCRIPTION:
                // Get whether the big block has landed or not.
                //
                /// RETURN VALUES:
                // True if the big block has landed.
                // False if the big block has not landed.
                //
                static bool hasLanded(void);

                /// DESCRIPTION:
                // Terminate the big block.
                //
                static void terminate(void);

                /// DESCRIPTION:
                // The destructor.
                //
                ~BigBlock(void) = delete;

            private:

                // The image.
                static J_Image image;
                // The idle animation.
                static J_Animation idle;
                // The conversion animation.
                static J_Animation convert;
                // The different type animations.
                static J_Animation healthy, sick, corrupt;
                // The current vertical position.
                static int y;
                // The starting and ending vertical positions.
                static const int STARTING_Y, ENDING_Y;
                // The current vertical velocity.
                static float velY;
                // The vertical velocity.
                static const float VELOCITY_Y;
                // The terminal velocity.
                static const float TERMINAL_VELOCITY;
                // The flag stating whether the big block has landed or not.
                static bool landed;
                // The counter to count down when to convert.
                static int convertCounter;

        };

        /// </BIG_BLOCK> //////////////////////////////////////////////////////

        //
        //
        //
        //

        /// <TITLE> ///////////////////////////////////////////////////////////

        class Title
        {
            // Game Over has access to private members.
            friend class GameOver;

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

                // The game over title image.
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

/// </GAME_OVER> //////////////////////////////////////////////////////////////

#endif // INCLUDE_GAME_OVER
