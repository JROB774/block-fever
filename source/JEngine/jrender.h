#ifndef INCLUDE_J_RENDER
#define INCLUDE_J_RENDER

/// <J_COLOUR> ////////////////////////////////////////////////////////////////

struct J_Colour
{
    public:

        // The RGBA data.
        Uint8 red, green, blue, alpha;
        // The blend mode data.
        SDL_BlendMode blendmode;
};

/// DESCRIPTION:
// The comparison operators.
//
/// ARGUMENTS:
// The objects to compare.
//
/// RETURN VALUES:
// Whether the condition was true or false.
//
bool operator==(const J_Colour&, const J_Colour&);
bool operator!=(const J_Colour&, const J_Colour&);

/// </J_COLOUR> ///////////////////////////////////////////////////////////////

//
//
//
//

/// <J_POINT> /////////////////////////////////////////////////////////////////

struct J_Point
{
    public:

        // The coordinates.
        SDL_Point point;
        // The colour data.
        J_Colour colour;
};

/// DESCRIPTION:
// The comparison operators.
//
/// ARGUMENTS:
// The objects to compare.
//
/// RETURN VALUES:
// Whether the condition was true or false.
//
bool operator==(const J_Point&, const J_Point&);
bool operator!=(const J_Point&, const J_Point&);

/// </J_POINT> ////////////////////////////////////////////////////////////////

//
//
//
//

/// <J_LINE> //////////////////////////////////////////////////////////////////

struct J_Line
{
    public:

        // The start point.
        SDL_Point start;
        // the end point.
        SDL_Point end;
        // The colour dats.
        J_Colour colour;
};

/// DESCRIPTION:
// The comparison operators.
//
/// ARGUMENTS:
// The objects to compare.
//
/// RETURN VALUES:
// Whether the condition was true or false.
//
bool operator==(const J_Line&, const J_Line&);
bool operator!=(const J_Line&, const J_Line&);

/// </J_LINE> /////////////////////////////////////////////////////////////////

//
//
//
//

/// <J_QUAD> //////////////////////////////////////////////////////////////////

struct J_Quad
{
    public:

        // The quad.
        SDL_Rect quad;
        // The colour data.
        J_Colour colour;
};

/// DESCRIPTION:
// The comparison operators.
//
/// ARGUMENTS:
// The objects to compare.
//
/// RETURN VALUES:
// Whether the condition was true or false.
//
bool operator==(const J_Quad&, const J_Quad&);
bool operator!=(const J_Quad&, const J_Quad&);

/// </J_QUAD> /////////////////////////////////////////////////////////////////

//
//
//
//

/// <J_IMAGE> /////////////////////////////////////////////////////////////////

struct J_Image
{
    // The renderer has access to private members.
    friend class J_Renderer;

    private:

        // The dimensions of the image.
        int width, height;
        // The image's colour data.
        J_Colour colour;
        // The raw SDL texture.
        SDL_Texture* texture;
};

/// </J_IMAGE> ////////////////////////////////////////////////////////////////

//
//
//
//

/// <J_ANIMATION> /////////////////////////////////////////////////////////////

struct J_Animation
{
    // The renderer has access to private members.
    friend class J_Renderer;

    private:

        // The total number of sprites in the animation.
        int spriteTotal;
        // The different sprite quads.
        std::vector <J_Quad> sprite;
        // The delay before the sprite is incremented/decremented.
        std::vector <int> delay;
        // The number of loops to play the animation (-1 is forever).
        int loops;
        // The current loop the animation is on.
        int currentLoop;
        // The flag stating whether the animation is done playing or not.
        bool done;
        // The direction to play the animation.
        int direction;
        // The current sprite to render.
        int currentSprite;
        // The counter for how long to delay each sprite.
        int delayCounter;
};

/// DESCRIPTION:
// The different directions the animation can play in.
//
enum J_AnimationPlayDirection
{
    J_ANIMATION_PLAY_BACKWARD,
    J_ANIMATION_PLAY_FORWARD
};

/// </J_ANIMATION> ////////////////////////////////////////////////////////////

//
//
//
//

/// <J_BACKGROUND> ////////////////////////////////////////////////////////////

struct J_Background
{
    // The renderer has access to private members.
    friend class J_Renderer;

    private:

        // The position coordinates.
        int x, y;
        // The speed to move the background.
        int speed;
        // The offset to render a moving backgound at.
        int offset;
        // The direction to move the background.
        int direction;
        // The background image.
        J_Image image;
};

/// DESCRIPTION:
// The different directions the background can move.
//
enum J_BackgroundMoveDirection
{
    J_BACKGROUND_MOVE_STATIONARY,
    J_BACKGROUND_MOVE_NORTH,
    J_BACKGROUND_MOVE_EAST,
    J_BACKGROUND_MOVE_SOUTH,
    J_BACKGROUND_MOVE_WEST
};

/// </J_BACKGROUND> ///////////////////////////////////////////////////////////

//
//
//
//

/// <J_FONT> //////////////////////////////////////////////////////////////////

struct J_Font
{
    // The renderer has access to private members.
    friend class J_Renderer;

    private:

        // The maximum number of characters.
        static const int CHARACTER_TOTAL;

        // The character dimensioons.
        int characterWidth, characterHeight;
        // The individual characters.
        J_Quad* character;
        // The font image.
        J_Image image;
};

/// </J_FONT> /////////////////////////////////////////////////////////////////

//
//
//
//

/// <J_RENDERER> //////////////////////////////////////////////////////////////

class J_Renderer
{
    public:

        /// DESCRIPTION:
        // The constructor.
        //
        J_Renderer(void) = delete;
        J_Renderer(const J_Renderer&) = delete;
        J_Renderer(J_Renderer&&) = delete;

        /// DESCRIPTION:
        // The assignment operator.
        //
        J_Renderer& operator=(const J_Renderer&) = delete;
        J_Renderer& operator=(J_Renderer&&) = delete;

        /// DESCRIPTION:
        // Initialise the renderer.
        // If the renderer is already initialised then calling this function
        // does nothing.
        //
        /// ARGUMENTS:
        // The window to create the renderer with.
        //
        static void initialise(SDL_Window*);

        /// DESCRIPTION:
        // Draw methods, draw a piece of geometry to the window.
        // Set the draw colour, render the gemoetry at its set position then
        // reset the draw colour back to default.
        //
        /// ARGUMENTS:
        // The piece of geometry to draw.
        //
        static void drawPoint(const J_Point&);
        static void drawLine(const J_Line&);
        static void drawQuadOutline(const J_Quad&);
        static void drawQuadFilled(const J_Quad&);

        /// DESCRIPTION:
        // Create an image from a PNG file.
        //
        /// ARGUMENTS:
        // The file to make the image with.
        //
        /// RETURN VALUES:
        // The newly created image.
        //
        static J_Image createImage(const std::string);

        /// DESCRIPTION:
        // Render an image to the screen at the specified position.
        // First Render an image at the specified position.
        // Second: Render an image, with extra render options, at the
        // specified position.
        //
        /// ARGUMENTS:
        // The image to render.
        // The coordinates to render the image at.
        // The camera's position coordinates (offset).
        // The angle to render the image at.
        // The center point of the rendered image.
        // The way to flip the rendered image.
        // The section of the image to render.
        //
        static void renderImage(const J_Image&, const int, const int, J_Quad*);
        static void renderImage(const J_Image&, const int, const int, const double, const J_Point*, const SDL_RendererFlip, J_Quad*);

        /// DESCRIPTION:
        // Set the image colour data.
        //
        /// ARGUMENTS:
        // The image to change the colour of.
        // The new colour data for the image.
        //
        static void setImageColour(J_Image*, const J_Colour);

        /// DESCRIPTION:
        // Get the image dimensions.
        //
        /// ARGUMENTS
        // The image to get the dimensions of.
        //
        /// RETURN VALUES:
        // The image dimensions.
        //
        static int getImageWidth(const J_Image&);
        static int getImageHeight(const J_Image&);

        /// DESCRIPTION:
        // Get the image colour data.
        //
        /// ARGUMENTS:
        // The image to get the colour of.
        //
        /// RETURN VALUES:
        // The image colour data.
        //
        static J_Colour getImageColour(const J_Image&);

        /// DESCRIPTION:
        // Destroy an image.
        //
        /// ARGUMENTS:
        // The image to destroy.
        //
        static void destroyImage(J_Image*);

        /// DESCRIPTION:
        // Create an animation from an ANIM file.
        //
        /// ARGUMENTS:
        // The file to make the animation with.
        //
        /// RETURN VALUES:
        // The newly created animation.
        //
        static J_Animation createAnimation(const std::string);

        /// DESCRIPTION:
        // Get the current frame of animation to render.
        //
        /// ARGUMENTS:
        // The animation to play.
        //
        /// RETURN VALUES:
        // The current frame quad.
        //
        static J_Quad* playAnimation(J_Animation*);

        /// DESCRIPTION:
        // If the animation has a finite number of loops, reset it so that it
        // can play through all of them again.
        //
        /// ARGUMENTS:
        // The animation to reset.
        //
        static void resetAnimation(J_Animation*);

        /// DESCRIPTION:
        // Set whether to play an animation forward or backward.
        //
        /// ARGUEMENTS:
        // The animation to change the direction of.
        // The direction to play the animation.
        //
        static void setAnimationDirection(J_Animation*, const int);

        /// DESCRIPTION:
        // Check to see whether the animation is done or not.
        // If the animation loops infinitely it will never be done.
        //
        /// ARGUMENTS:
        // The animation to check.
        //
        /// RETURN VAUES:
        // True if the animation is done.
        // False if the animation is still playing.
        //
        static bool isAnimationDone(const J_Animation&);

        /// DESCRIPTION:
        // Get the current direction the animtion is playing.
        //
        /// ARGUMENTS:
        // The animation to get the direction from.
        //
        /// RETURN VALUES:
        // The current direction.
        //
        static int getAnimationDirection(const J_Animation&);

        /// DESCRTIPTION:
        // Get the length of an animation in frames.
        //
        /// ARGUMENTS:
        // The animation to get the length of.
        //
        /// RETURN VALUES:
        // The length of the animation.
        //
        static int getAnimationLength(const J_Animation&);

        /// DESCRIPTION:
        // Destroy an animation.
        //
        /// ARGUMENTS:
        // The animation to destroy.
        //
        static void destroyAnimation(J_Animation*);

        /// DESCRIPTION:
        // Create a background from a BG file.
        //
        /// ARGUMENTS:
        // The file to make the background from.
        //
        /// RETURN VALUES:
        // The newly created background.
        //
        static J_Background createBackground(const std::string);

        /// DESCRIPTION:
        // Render a background.
        //
        /// ARGUMENTS:
        // The background to render.
        //
        static void renderBackground(J_Background*);

        /// DESCRIPTION:
        // Set the background's colour.
        //
        /// ARGUMENTS:
        // The background to change.
        // The new colour.
        //
        static void setBackgroundColour(J_Background*, const J_Colour&);

        /// DESCRIPTION:
        // Get the speed the background moves at.
        //
        /// ARGUMENTS:
        // The background to get the speed from.
        //
        /// RETURN VALUES:
        // The beckground's movement speed.
        //
        static int getBackgroundSpeed(const J_Background&);

        /// DESCRIPTION:
        // Get the direction the background moves.
        //
        /// ARGUMENTS:
        // The background to get the directioon of.
        //
        /// RETURN VALUES:
        // The background's movement direction.
        //
        static int getBackgroundDirection(const J_Background&);

        /// DESCRIPTION:
        // Get the background's oolour.
        //
        /// ARGUMENTS:
        // The background to get the colour of.
        //
        /// RETURN VALUES:
        // The background's colour.
        //
        static J_Colour getBackgroundColour(const J_Background&);

        /// DESCRPTION:
        // Destroy a background.
        //
        /// ARGUMENTS:
        // The background to destroy.
        //
        static void destroyBackground(J_Background*);

        /// DESCRIPTION:
        // Create a font from a FONT file.
        //
        /// ARGUMENTS:
        // The file to make the font from.
        //
        /// RETURN VALUES:
        // The newly created font.
        //
        static J_Font createFont(const std::string);

        /// DESCRIPTION:
        // Render the specified text in the specified font.
        //
        /// ARGUMENTS:
        // The font to render with.
        // The position to render at.
        // The text to render.
        //
        static void renderFont(const J_Font&, const int, const int, const std::string);

        /// DESCRIPTION:
        // Set the colour to render at font at.
        //
        /// ARGUMENTS:
        // The font to change the colour of.
        // The new colour to render the font.
        //
        static void setFontColour(J_Font*, const J_Colour&);

        /// DESCRIPTION:
        // Get the font's character dimensions.
        //
        /// RETURN VALUES:
        // The character's dimensions.
        //
        static int getFontCharWidth(const J_Font&);
        static int getFontCharHeight(const J_Font&);

        /// DESCRIPTION:
        // Get the colour of a font.
        //
        /// ARGUMENTS:
        // The font to get the colour of.
        //
        /// RETURN VALUES:
        // The colour of the font.
        //
        static J_Colour getFontColour(const J_Font&);

        /// DESCRIPTION:
        // Destroy a font.
        //
        /// ARGUMENTS:
        // The font to destroy.
        //
        static void destroyFont(J_Font*);

        /// DESCRIPTION:
        // Clear the renderer.
        // Reset the draw colour to default and fill the window with it.
        //
        static void clear(void);

        /// DESCRIPTION:
        // Update the renderer.
        // Render everything to the window.
        //
        static void update(void);

        /// DESCRIPTION:
        // Set the renderer viewport.
        //
        /// ARGUMENTS:
        // The viwport quad.
        //
        static void setViewport(const J_Quad);

        /// DESCRIPTION:
        // Set the scale to render everything at.
        //
        /// ARGUMENTS:
        // The new renderer scale.
        //
        static void setScale(const float, const float);

        /// DESCRIPTION:
        // Set the colour, alpha and blend mode for the the renderer.
        //
        /// ARGUMENTS:
        // The new colour data for the renderer.
        //
        static void setColour(const J_Colour&);

        /// DESCRIPTION:
        // Get the viewport values and store them in the pointer passed.
        //
        /// ARGUMENTS:
        // The pointer to store the viewpot values.
        //
        static void getViewport(J_Quad*);

        /// DESCRIPTION:
        // Get the x and y renderer scale values and store them in the two
        // pointers passed.
        //
        /// ARGUMENTS:
        // The pointer to store the x scale in.
        // The pointer to store the y scale in.
        //
        static void getScale(float*, float*);

        /// DESCRIPTION:
        // Get the renderer's default draw colour.
        //
        /// RETURN VALUES:
        // (DEFAULT_COLOUR) = The constant default colour for the renderer.
        //
        static J_Colour getDefaultColour(void);

        /// DESCRIPTION:
        // Terminate the renderer.
        //
        static void terminate(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~J_Renderer(void) = delete;

    private:

        // The renderer's default colour data.
        static const J_Colour DEFAULT_COLOUR;
        // The renderer.
        static SDL_Renderer* renderer;
};

/// </J_RENDERER> /////////////////////////////////////////////////////////////

#endif // INCLUDE_J_RENDER
