#ifndef INCLUDE_BUTTON
#define INCLUDE_BUTTON

class Button
{
    // GameOver has access to private members.
    friend class GameOver;

    public:

        /// DESCRIPTION:
        // The different types of button.
        //
        enum ButtonType
        {
            TYPE_QUIT,
            TYPE_MENU,
            TYPE_RESTART,
            TYPE_TOTAL
        };

        /// DESCRIPTION:
        // The constructor.
        //
        Button(void) = default;
        Button(const Button&) = delete;
        Button(Button&&) = delete;

        /// DESCRIPTION:
        // The assignment operator.
        //
        Button& operator=(const Button&) = delete;
        Button& operator=(Button&&) = delete;

        /// DESCRIPTION:
        // Create a button.
        //
        /// ARGUMENTS:
        // The position coordinates for the button.
        // The button type.
        //
        void create(const int, const int, const int);

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
        ~Button(void);

    private:

        // The button dimensions.
        static const int WIDTH, HEIGHT;
        // The ending vertical positions.
        static const int ENDING_Y;
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
        // The position coordinates.
        int x, y;
        // The current vertical velocity.
        float velY;
        // The different button sprites.
        J_Quad* sprite;
        // The box collider.
        J_Collider collider;
        // The sound made when the button is clicked.
        J_Sound click;
        // The button type.
        int type;
        // The flag stating whether the button has landed or not.
        bool landed;
};

#endif // INCLUDE_BUTTON
