#ifndef INCLUDE_CURSOR
#define INCLUDE_CURSOR

#include "jsystem.h"

/// <CURSOR> //////////////////////////////////////////////////////////////////

class Cursor
{
    public:

        /// DESCRIPTION:
        // The constructor.
        //
        Cursor(void) = delete;
        Cursor(const Cursor&) = delete;
        Cursor(Cursor&&) = delete;

        /// DESCRIPTION:
        // The assignment operator.
        //
        Cursor& operator=(const Cursor&) = delete;
        Cursor& operator=(Cursor&&) = delete;

        /// DESCRIPTION:
        // Initialise the cursor.
        //
        static void initialise(void);

        /// DESCRIPTION:
        // Handle mouse movements for the cursor.
        //
        static void handle(void);

        /// DESCRIPTION:
        // Render the cursor at the mouse position.
        //
        static void render(void);

        /// DESCRIPTION:
        // Get the cursor's current position.
        //
        /// RETURN VALUES:
        // The cursor's current position.
        //
        static int getX(void);
        static int getY(void);

        /// DESCRIPTION:
        // Terminate the cursor.
        //
        static void terminate(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~Cursor(void) = delete;

    private:

        // The position coordinates.
        static int x, y;
        // The cursor image.
        static J_Image image;
};

/// </CURSOR> /////////////////////////////////////////////////////////////////

#endif // INCLUDE_CURSOR
