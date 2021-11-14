#ifndef INCLUDE_BLOCK
#define INCLUDE_BLOCK

#include "jsystem.h"

/// <BLOCK> ///////////////////////////////////////////////////////////////////

class Block
{
    public:

        /// DESCRIPTION:
        // The different states a block can be in.
        //
        enum State
        {
            STATE_HEALTHY,
            STATE_HEALTHY_CONVERT,
            STATE_SICK_CONVERT,
            STATE_SICK,
            STATE_CORRUPT_CONVERT,
            STATE_CORRUPT,
            STATE_IMMUNE_CONVERT,
            STATE_IMMUNE
        };

        /// DESCRIPTION:
        // The constructor.
        //
        Block(void) = default;
        Block(const Block&) = delete;
        Block(Block&&) = delete;

        /// DESCRIPTION:
        // The assignment operator.
        //
        Block& operator=(const Block&) = delete;
        Block& operator=(Block&&) = delete;

        /// DESCRIPTION:
        // Create the block.
        //
        /// ARGUMENTS:
        // The position coordinates.
        //
        void create(const int, const int);

        /// DESCRIPTION:
        // Step through the block.
        //
        void step(void);

        /// DESCRIPTION:
        // Render the block to the screen.
        //
        void render(void);

        /// DESCRIPTION:
        // Set the flag to render the mask to true.
        //
        void setRenderMask(void);

        /// DESCRIPTION:
        // Set the state of a block to the state passed.
        // If the state passed is not valid then the state shall be set to
        // healthy.
        //
        /// ARGUMENTS:
        // The new state of the block.
        //
        void setState(const int);

        /// DESCRIPTION:
        // Get the block dimensions.
        //
        /// RETURN VALUES:
        // The block dimensions.
        //
        static int getWidth(void);
        static int getHeight(void);

        /// DESCRIPTION:
        // Get the block's collider.
        //
        /// RETURN VALUES:
        // The collider.
        //
        J_Collider getCollider(void) const;

        /// DESCRIPTION:
        // Get the block's current state.
        //
        /// RETURN VALUES:
        // The current state.
        //
        int getState(void) const;

        /// DESCRIPTION:
        // Destory the block.
        //
        void destroy(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~Block(void);

    private:

        // The block dimensions.
        static const int WIDTH, HEIGHT;

        // The position coordinates.
        int x, y;
        // The block image.
        J_Image image;
        // The block mask
        J_Image mask;
        // The flag stating whether to render the mask.
        bool renderMask;
        // The differnet idle animations.
        J_Animation healthy, sick, corrupt, immune;
        // The different conversion animations.
        J_Animation healthyConvert, sickConvert, corruptConvert, immuneConvert;
        // The animation for a sick block about to turn corrupt.
        J_Animation sickSpecial;
        // The different block sound effects.
        J_Sound healthyNoise, sickNoise, corruptNoise, immuneNoise;
        // The collision box for the block.
        J_Collider collider;
        // The counter stating when a sick block should turn corrupt.
        int corruptCounter;
        // The cooldown counter.
        int cooldownCounter;
        // The current state of the block.
        int state;
};

#endif // INCLUDE_BLOCK

/// </BLOCK> //////////////////////////////////////////////////////////////////
