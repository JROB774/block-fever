#ifndef INCLUDE_STAGE
#define INCLUDE_STAGE

#include "Block.h"
#include "GameOver.h"
#include "Pause.h"

/// <STAGE> ///////////////////////////////////////////////////////////////////

class Stage
{
    public:

        /// DESCRIPTION:
        // The different states the stage can be in.
        //
        enum State
        {
            STATE_PLAYING,
            STATE_PAUSED,
            STATE_MENU,
            STATE_EXIT,
            STATE_GENERATE,
            STATE_INACTIVE
        };

        /// DESCRIPTION:
        // The constructor.
        //
        Stage(void) = delete;
        Stage(const Stage&) = delete;
        Stage(Stage&&) = delete;

        /// DESCRIPTION:
        // The assignement operator.
        //
        Stage& operator=(const Stage&) = delete;
        Stage& operator=(Stage&&) = delete;

        /// DESCRIPTION:
        // Initialise the stage and all it's components.
        //
        static void initialise(void);

        /// DESCRIPTION:
        // Generate the stage's map.
        //
        static void generate(void);

        /// DESCRIPTION:
        // Handle all the stage events.
        //
        static void handle(void);

        /// DESCRIPTION:
        // Step through everything in the stage.
        //
        static void step(void);

        /// DESCRIPTION:
        // Render everythhing in the stage.
        //
        static void render(void);

        /// DESCRIPTION:
        // Get whether the screen has faded out or not.
        //
        /// RETURN VALUES:
        // True if it has faded.
        // Fale if it hasn't faded.
        //
        static bool hasFadedOut(void);

        /// DESCRIPTION:
        // Get the stage's current state.
        //
        /// RETURN VALUES:
        // The current state.
        //
        static int getState(void);

        /// DESCRIPTION:
        // Terminate the stage.
        //
        static void terminate(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~Stage(void) = delete;

    private:

        // The dimensiosn of the game board.
        static const int BLOCK_ARRAY_WIDTH, BLOCK_ARRAY_HEIGHT;
        // The blocks in the board.
        static Block* block;
        // The starting number of corrupt blocks.
        static const int STARTING_CORRUPTION;
        // The starting sickness per corrupt block.
        static const int STARTING_SICKNESS;
        // The sidebar image.
        static J_Image sidebar;
        // The big numbers font, for the sidebar.
        static J_Font bigNumbers;
        // The counter to convert a healthy block to a sick block.
        static int convertToSickCounter;
        // The range of time to set the convert to sick counter to count down from.
        static const int MIN_CONVERT_TO_SICK_TIME, MAX_CONVERT_TO_SICK_TIME;
        // The counter to convert a sick block to a corrupt block.
        static int convertToCorruptCounter;
        // The range of time to set the conver to corrupt counter to cound down from.
        static const int MIN_CONVERT_TO_CORRUPT_TIME, MAX_CONVERT_TO_CORRUPT_TIME;
        // The current amount of money the player has.
        static int money;
        // The amount of money given by a sick block.
        static const int SICK_BLOCK_MONEY;
        // The cost to make an immune block.
        static const int IMMUNE_BLOCK_COST;
        // The total number of each block type.
        static int healthyTotal, sickTotal, corruptTotal, immuneTotal;
        // The fade out after going back to the menu.
        static J_Quad fade;
        // The level of transparency on the fade out.
        static const Uint8 FADE_TRANSPARENCY;
        // The amount to fade out per frame.
        static const Uint8 FADE_AMOUNT;
        // The counter stating how long the burst of sickness should be.
        static int burstCounter;
        // The counter storing the number of frames the stage has been active for.
        static int stageTime;
        // The stage's current state.
        static int state;
};

/// </STAGE> //////////////////////////////////////////////////////////////////

#endif // INCLUDE_STAGE
