#include "jrender.h"

/// <J_COLOUR> ////////////////////////////////////////////////////////////////

bool operator== (const J_Colour& arg_lhs, const J_Colour& arg_rhs) { return ((arg_lhs.red == arg_rhs.red) && (arg_lhs.green == arg_rhs.green) && (arg_lhs.blue == arg_rhs.blue) && (arg_lhs.alpha == arg_rhs.alpha) && (arg_lhs.blendmode == arg_rhs.blendmode)) ? true : false; }

bool operator!= (const J_Colour& arg_lhs, const J_Colour& arg_rhs) { return !operator==(arg_lhs, arg_rhs); }

/// </J_COLOUR> ///////////////////////////////////////////////////////////////

//
//
//
//

/// <J_POINT> /////////////////////////////////////////////////////////////////

bool operator== (const J_Point& arg_lhs, const J_Point& arg_rhs) { return ((arg_lhs.point.x == arg_rhs.point.x) && (arg_lhs.point.y == arg_rhs.point.y)) ? true : false; }

bool operator!= (const J_Point& arg_lhs, const J_Point& arg_rhs) { return !operator==(arg_lhs, arg_rhs); }

/// </J_POINT> ////////////////////////////////////////////////////////////////

//
//
//
//

/// <J_LINE> //////////////////////////////////////////////////////////////////

bool operator== (const J_Line& arg_lhs, const J_Line& arg_rhs) { return ((arg_lhs.start.x == arg_rhs.start.x) && (arg_lhs.start.y == arg_rhs.start.y) && (arg_lhs.end.x == arg_rhs.end.x) && (arg_lhs.end.y == arg_rhs.end.y)) ? true : false; }

bool operator!= (const J_Line& arg_lhs, const J_Line& arg_rhs) { return !operator==(arg_lhs, arg_rhs); }

/// </J_LINE> /////////////////////////////////////////////////////////////////

//
//
//
//

/// <J_QUAD> //////////////////////////////////////////////////////////////////

bool operator== (const J_Quad& arg_lhs, const J_Quad& arg_rhs) { return (SDL_RectEquals(&arg_lhs.quad, &arg_rhs.quad) == SDL_TRUE) ? true : false; }

bool operator!= (const J_Quad& arg_lhs, const J_Quad& arg_rhs) { return !operator==(arg_lhs, arg_rhs); }

/// </J_QUAD> /////////////////////////////////////////////////////////////////

//
//
//
//

/// <J_FONT> //////////////////////////////////////////////////////////////////

const int J_Font::CHARACTER_TOTAL = 128;

/// </J_FONT> /////////////////////////////////////////////////////////////////

//
//
//
//

/// <J_RENDERER> //////////////////////////////////////////////////////////////

const J_Colour J_Renderer::DEFAULT_COLOUR = { 0, 0, 0, 255, SDL_BLENDMODE_BLEND };
SDL_Renderer* J_Renderer::renderer = nullptr;



void J_Renderer::initialise (SDL_Window* arg_window) {

    // If the renderer is already initialised, end the process.
    if (renderer != nullptr) { return; }

    // Create the renderer itself and set its draw colour to default.
    renderer = SDL_CreateRenderer(arg_window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) { J_Error::log("J_ERROR_RENDERER_CREATE"); }

    setColour(DEFAULT_COLOUR);
}



void J_Renderer::drawPoint (const J_Point& arg_point) {

    // Set the renderer's draw colour to that of the point to be drawn and draw it.
    setColour(arg_point.colour);
    if (SDL_RenderDrawPoint(renderer, arg_point.point.x, arg_point.point.y) != 0) { J_Error::log("J_ERROR_RENDERER_DRAW_POINT"); }

    // Reset the renderer's draw colour to its default.
    setColour(DEFAULT_COLOUR);
}

void J_Renderer::drawLine (const J_Line& arg_line) {

    // Set the renderer's draw colour to that of the line to be drawn and draw it.
    setColour(arg_line.colour);
    if (SDL_RenderDrawLine(renderer, arg_line.start.x, arg_line.start.y, arg_line.end.x, arg_line.end.y) != 0) { J_Error::log("J_ERROR_RENDERER_DRAW_LINE"); }

    // Reset the renderer's draw colour to its default.
    setColour(DEFAULT_COLOUR);
}

void J_Renderer::drawQuadOutline (const J_Quad& arg_quad) {

    // Set the renderer's draw colour to that of the quad to be drawn and draw it.
    setColour(arg_quad.colour);
    if (SDL_RenderDrawRect(renderer, &arg_quad.quad) != 0) { J_Error::log("J_ERROR_RENDERER_DRAW_QUAD_OUTLINE"); }

    // Reset the renderer's draw colour to its default.
    setColour(DEFAULT_COLOUR);
}

void J_Renderer::drawQuadFilled (const J_Quad& arg_quad) {

    // Set the renderer's draw colour to that of the quad to be drawn and draw it.
    setColour(arg_quad.colour);
    if (SDL_RenderFillRect(renderer, &arg_quad.quad) != 0) { J_Error::log("J_ERROR_RENDERER_DRAW_QUAD_FILLED"); }

    // Reset the renderer's draw colour to its default.
    setColour(DEFAULT_COLOUR);
}



J_Image J_Renderer::createImage (const std::string arg_file) {

    // Load the PNG file into a surface.
    std::string directory = "Resources\\Images\\" + arg_file + ".png";
    SDL_Surface* surface = IMG_Load(directory.c_str());
    if (surface == nullptr) { J_Error::log("J_ERROR_RENDERER_IMAGE_SURFACE_LOAD"); }

    // Create the texture from a surface.
    J_Image image;
    image.texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (image.texture == nullptr) { J_Error::log("J_ERROR_RENDERER_IMAGE_TEXTURE_CREATE"); }

    // Set the image's dimensions.
    image.width = surface->w, image.height = surface->h;

    // Free the temporary surface
    SDL_FreeSurface(surface);
    surface = nullptr;

    // Return the image.
    return image;
}



void J_Renderer::renderImage (const J_Image& arg_image, const int arg_x, const int arg_y, J_Quad* arg_source) {

    // Setup the source and destination quads.
    J_Quad destination;

    destination.quad = { arg_x, arg_y, arg_image.width, arg_image.height };
    if (arg_source != nullptr) { destination.quad.w = arg_source->quad.w, destination.quad.h = arg_source->quad.h; }

    // Render the image to the screen.
    if (SDL_RenderCopy(renderer, arg_image.texture, &arg_source->quad, &destination.quad) != 0) { J_Error::log("J_ERROR_RENDERER_IMAGE_RENDER"); }
}

void J_Renderer::renderImage (const J_Image& arg_image, const int arg_x, const int arg_y, const double arg_angle, const J_Point* arg_center, const SDL_RendererFlip arg_flip, J_Quad* arg_source) {

    // Setup the source and destination quads.
    J_Quad destination;

    destination.quad = { arg_x, arg_y, arg_image.width, arg_image.height };
    if (arg_source != nullptr) { destination.quad.w = arg_source->quad.w, destination.quad.h = arg_source->quad.h; }

    // Render the image to the screen with extra render options.
    if (SDL_RenderCopyEx(renderer, arg_image.texture, &arg_source->quad, &destination.quad, arg_angle, &arg_center->point, arg_flip) != 0) { J_Error::log("J_ERROR_RENDERER_IMAGE_RENDER_EXTRA"); }
}



void J_Renderer::setImageColour (J_Image* arg_image, const J_Colour arg_colour) {

    // Set all of the image's colour data.
    if (SDL_SetTextureColorMod(arg_image->texture, arg_colour.red, arg_colour.green, arg_colour.blue) != 0) { J_Error::log("J_ERROR_RENDERER_SET_IMAGE_COLOUR"); }
    if (SDL_SetTextureAlphaMod(arg_image->texture, arg_colour.alpha) != 0) { J_Error::log("J_ERROR_RENDERER_SET_IMAGE_ALPHA"); }
    if (SDL_SetTextureBlendMode(arg_image->texture, arg_colour.blendmode) != 0) { J_Error::log("J_ERROR_RENDERER_SET_IMAGE_BLENDMODE"); }
}



int J_Renderer::getImageWidth (const J_Image& arg_image) { return arg_image.width; }

int J_Renderer::getImageHeight (const J_Image& arg_image) { return arg_image.height; }

J_Colour J_Renderer::getImageColour (const J_Image& arg_image) { return arg_image.colour; }



void J_Renderer::destroyImage (J_Image* arg_image) {

    // Destroy the image and reset its values.
    SDL_DestroyTexture(arg_image->texture);
    arg_image->texture = nullptr;
    arg_image->width = 0, arg_image->height = 0;
    arg_image->colour = { 0, 0, 0, 255, SDL_BLENDMODE_BLEND };
    arg_image = nullptr;
}



J_Animation J_Renderer::createAnimation (const std::string arg_file) {

    // Read the animation file and store all the data.
    std::string directory = "Resources\\Animations\\" + arg_file + ".anim";
    std::ifstream animationFile(directory, std::ifstream::in);
    std::string rawData = "\0";

    if (animationFile.is_open()) {

        std::getline(animationFile, rawData);
        animationFile.close();
    }
    else { J_Error::log("J_ERROR_RENDERER_ANIMATION_LOAD"); }

    std::istringstream data;
    data.str(rawData);

    int spriteTotal = 0;
    J_Quad sprite;
    std::string rawDelay = "\0";
    int loops = 0;
    int direction = J_ANIMATION_PLAY_FORWARD;

    data >> spriteTotal >> loops >> direction >> sprite.quad.x >> sprite.quad.y >> sprite.quad.w >> sprite.quad.h >> rawDelay;


    // Take the raw data, convert it and then store it in a temporary animation.
    J_Animation animation;

    animation.spriteTotal = spriteTotal;
    animation.loops = loops;
    animation.currentLoop = animation.loops;
    animation.done = false;
    animation.direction = direction;

    for (int i = 0, ix = sprite.quad.x; i < spriteTotal; ++i, ix += sprite.quad.w) {

        J_Quad tempSprite;
        tempSprite.quad = { ix, sprite.quad.y, sprite.quad.w, sprite.quad.h };
        animation.sprite.push_back(tempSprite);
    }

    char* delay = new(std::nothrow) char[rawDelay.length() + 1];
    if (delay == nullptr) { J_Error::log("J_ERROR_RENDERER_ANIMATION_CREATE"); }
    strcpy(delay, rawDelay.c_str());
    animation.delay.push_back(atoi(strtok(delay, ":")));
    for (int i = 0; i < (spriteTotal - 1); ++i) { animation.delay.push_back(atoi(strtok(nullptr, ":"))); }

    if (direction == J_ANIMATION_PLAY_FORWARD) {

        animation.currentSprite = 0;
        animation.delayCounter = animation.delay.front();
    }
    else {

        animation.currentSprite = spriteTotal - 1;
        animation.delayCounter = animation.delay.back();
    }


    // Delete and clean up.
    delete[] delay;
    delay = nullptr;


    // Return the animation.
    return animation;
}



J_Quad* J_Renderer::playAnimation (J_Animation* arg_animation) {

    // Figure out the current sprite to render and return it.
    if (arg_animation->loops <= -1) {

        if (arg_animation->delayCounter <= 0) {

            if (arg_animation->direction == J_ANIMATION_PLAY_FORWARD) { ++arg_animation->currentSprite; }
            else { --arg_animation->currentSprite; }

            if (arg_animation->currentSprite >= arg_animation->spriteTotal) { arg_animation->currentSprite = 0; }
            else if (arg_animation->currentSprite < 0) { arg_animation->currentSprite = arg_animation->spriteTotal - 1; }

            arg_animation->delayCounter = arg_animation->delay.at(arg_animation->currentSprite);
        }
        else { --arg_animation->delayCounter; }
    }
    else {

        if (arg_animation->currentLoop > -1) {

            if (arg_animation->delayCounter <= 0) {

                if (arg_animation->direction == J_ANIMATION_PLAY_FORWARD) { ++arg_animation->currentSprite; }
                else { --arg_animation->currentSprite; }

                if (arg_animation->currentSprite >= arg_animation->spriteTotal) {

                    --arg_animation->currentLoop;

                    if (arg_animation->currentLoop > -1) { arg_animation->currentSprite = 0; }
                    else {

                        arg_animation->currentSprite = arg_animation->spriteTotal - 1;
                        arg_animation->done = true;
                    }
                }
                else if (arg_animation->currentSprite < 0) {

                    arg_animation->currentSprite = arg_animation->spriteTotal - 1;
                    --arg_animation->currentLoop;

                    if (arg_animation->currentLoop > -1) { arg_animation->currentSprite = arg_animation->spriteTotal -1; }
                    else {

                        arg_animation->currentSprite = 0;
                        arg_animation->done = true;
                    }
                }

                arg_animation->delayCounter = arg_animation->delay.at(arg_animation->currentSprite);
            }
            else { --arg_animation->delayCounter; }
        }
    }

    return &arg_animation->sprite.at(arg_animation->currentSprite);
}



void J_Renderer::resetAnimation (J_Animation* arg_animation) {

    // Reset the animation if it has a finite number of loops.
    if (arg_animation->loops > -1) {

        if (arg_animation->direction == J_ANIMATION_PLAY_FORWARD) { arg_animation->currentSprite = 0; }
        else { arg_animation->currentSprite = arg_animation->spriteTotal - 1; }

        arg_animation->delayCounter = arg_animation->delay.at(arg_animation->currentSprite);

        arg_animation->currentLoop = arg_animation->loops;
        arg_animation->done = false;
    }
}



void J_Renderer::setAnimationDirection (J_Animation* arg_animation, const int arg_direction) {  if (!arg_animation->done) {arg_animation->direction = arg_direction;} }



bool J_Renderer::isAnimationDone (const J_Animation& arg_animation) { return arg_animation.done; }

int J_Renderer::getAnimationDirection (const J_Animation& arg_animation) { return arg_animation.direction; }

int J_Renderer::getAnimationLength (const J_Animation& arg_animation) {

    int length = 0;
    for (int i = 0; i < arg_animation.spriteTotal; ++i) { length += arg_animation.delay.at(i); }

    return length;
}



void J_Renderer::destroyAnimation (J_Animation* arg_animation) {

    // Reset all the animation's data.
    arg_animation->spriteTotal = 0;
    arg_animation->sprite.clear();
    arg_animation->delay.clear();
    arg_animation->loops = 0;
    arg_animation->currentLoop = 0;
    arg_animation->done = false;
    arg_animation->direction = J_ANIMATION_PLAY_FORWARD;
    arg_animation->currentSprite = 0;
    arg_animation->delayCounter = 0;
}



J_Background J_Renderer::createBackground (const std::string arg_file) {

    // Read the background file and store all the data.
    std::string directory = "Resources\\Backgrounds\\" + arg_file + ".bg";
    std::ifstream backgroundFile(directory, std::ifstream::in);
    std::string rawData = "\0";

    if (backgroundFile.is_open()) {

        std::getline(backgroundFile, rawData);
        backgroundFile.close();
    }
    else { J_Error::log("J_ERROR_RENDERER_BACKGROUND_LOAD"); }

    std::istringstream data;
    data.str(rawData);

    int x = 0, y = 0;
    int speed = 0;
    int direction = J_BACKGROUND_MOVE_STATIONARY;
    std::string imageFile = "\0";

    data >> x >> y >> speed >> direction >> imageFile;


    // Take the raw data and store it in a temporary background.
    J_Background background;

    background.x = x, background.y = y;
    background.speed = speed;
    background.offset = 0;
    background.direction = direction;
    background.image = createImage(imageFile);


    // Return the background.
    return background;
}



void J_Renderer::renderBackground (J_Background* arg_background) {

    // Find out which direction the backgroud is moving and render it accordingly.
    switch (arg_background->direction) {

        case (J_BACKGROUND_MOVE_NORTH) : {

            arg_background->offset -= arg_background->speed;
            if (arg_background->offset <= -getImageHeight(arg_background->image)) { arg_background->offset += getImageHeight(arg_background->image); }

            renderImage(arg_background->image, arg_background->x, arg_background->y + arg_background->offset, nullptr);
            renderImage(arg_background->image, arg_background->x, arg_background->y + (arg_background->offset + getImageHeight(arg_background->image)), nullptr);

            break;
        }

        case (J_BACKGROUND_MOVE_EAST) : {

            arg_background->offset += arg_background->speed;
            if (arg_background->offset >= getImageWidth(arg_background->image)) { arg_background->offset -= getImageWidth(arg_background->image); }

            renderImage(arg_background->image, arg_background->x + arg_background->offset, arg_background->y, nullptr);
            renderImage(arg_background->image, arg_background->x + (arg_background->offset - getImageWidth(arg_background->image)), arg_background->y, nullptr);

            break;
        }

        case (J_BACKGROUND_MOVE_SOUTH) : {

            arg_background->offset += arg_background->speed;
            if (arg_background->offset >= getImageHeight(arg_background->image)) { arg_background->offset -= getImageHeight(arg_background->image); }

            renderImage(arg_background->image, arg_background->x, arg_background->y + arg_background->offset, nullptr);
            renderImage(arg_background->image, arg_background->x, arg_background->y + (arg_background->offset - getImageHeight(arg_background->image)), nullptr);

            break;
        }

        case (J_BACKGROUND_MOVE_WEST) : {

            arg_background->offset -= arg_background->speed;
            if (arg_background->offset <= -getImageWidth(arg_background->image)) { arg_background->offset += getImageWidth(arg_background->image); }

            renderImage(arg_background->image, arg_background->x + arg_background->offset, arg_background->y, nullptr);
            renderImage(arg_background->image, arg_background->x + (arg_background->offset + getImageWidth(arg_background->image)), arg_background->y, nullptr);

            break;
        }

        default : { renderImage(arg_background->image, arg_background->x, arg_background->y, nullptr); break; }
    }
}



void J_Renderer::setBackgroundColour (J_Background* arg_background, const J_Colour& arg_colour) { setImageColour(&arg_background->image, arg_colour); }



int J_Renderer::getBackgroundSpeed (const J_Background& arg_background) { return (arg_background.direction != J_BACKGROUND_MOVE_STATIONARY) ? arg_background.speed : 0; }

int J_Renderer::getBackgroundDirection (const J_Background& arg_background) { return arg_background.direction; }

J_Colour J_Renderer::getBackgroundColour (const J_Background& arg_background) { return getImageColour(arg_background.image); }



void J_Renderer::destroyBackground (J_Background* arg_background) {

    // Reset all the background's data.
    arg_background->x = 0, arg_background->y = 0;
    arg_background->speed = 0;
    arg_background->offset = 0;
    arg_background->direction = J_BACKGROUND_MOVE_STATIONARY;
    destroyImage(&arg_background->image);
}



J_Font J_Renderer::createFont (const std::string arg_file)  {

    // Read the font file and store all the data.
    std::string directory = "Resources\\Fonts\\" + arg_file + ".font";
    std::ifstream fontFile(directory, std::ifstream::in);
    std::string rawData = "\0";

    if (fontFile.is_open()) {

        std::getline(fontFile, rawData);
        fontFile.close();
    }
    else { J_Error::log("J_ERROR_RENDERER_FONT_LOAD"); }

    std::istringstream data;
    data.str(rawData);

    int characterWidth = 0, characterHeight = 0;
    std::string imageFile = "\0";

    data >> characterWidth >> characterHeight >> imageFile;


    // Take the raw data and store it in a temporary font.
    J_Font font;

    font.characterWidth = characterWidth, font.characterHeight = characterHeight;
    font.image = createImage(imageFile);
    font.character = nullptr;


    // Cut up the indivudal character quads.
    font.character = new(std::nothrow) J_Quad[J_Font::CHARACTER_TOTAL];
    if (font.character == nullptr) { J_Error::log("J_ERROR_RENDERER_FONT_CREATE"); }

    for (int i = 0, ix = 0, iy = 0; i < J_Font::CHARACTER_TOTAL; ++i, ix += font.characterWidth) {

        font.character[i].quad = { ix, iy, font.characterWidth, font.characterHeight };
        if (ix >= getImageWidth(font.image)) { ix = 0, iy += font.characterHeight; }
    }


    // Return the font.
    return font;
}



void J_Renderer::renderFont (const J_Font& arg_font, const int arg_x, const int arg_y, const std::string arg_text) {

    // Render the specified text to the screen.
    if (arg_font.character != nullptr) {

        int characterValue = 0;

        for (unsigned int i = 0, ix = arg_x, iy = arg_y; i < arg_text.length(); ++i) {

            switch (arg_text.at(i)) {

                case ('\n') : { ix = arg_x, iy += arg_font.characterHeight; break; }

                case ('\t') : { ix += (arg_font.characterWidth * 4); break; }

                default : {

                    characterValue = static_cast <unsigned char> (arg_text.at(i));
                    renderImage(arg_font.image, ix, iy, &arg_font.character[characterValue]);

                    ix += arg_font.characterWidth;

                    break;
                }
            }
        }
    }
}



void J_Renderer::setFontColour (J_Font* arg_font, const J_Colour& arg_colour) { setImageColour(&arg_font->image, arg_colour); }



int J_Renderer::getFontCharWidth (const J_Font& arg_font) { return arg_font.characterWidth; }

int J_Renderer::getFontCharHeight (const J_Font& arg_font) { return arg_font.characterHeight; }

J_Colour J_Renderer::getFontColour (const J_Font& arg_font) { return getImageColour(arg_font.image); }



void J_Renderer::destroyFont (J_Font* arg_font) {

    // Reset all the font's values.
    arg_font->characterWidth = 0, arg_font->characterHeight = 0;
    delete[] arg_font->character;
    arg_font->character = nullptr;
    destroyImage(&arg_font->image);
}



void J_Renderer::clear (void) {

    // Reset the renderer's draw colour, in case it's been changed, and fills the screen with it.
    setColour(DEFAULT_COLOUR);
    if (SDL_RenderClear(renderer) != 0) { J_Error::log("J_ERROR_RENDERER_CLEAR"); }
}

void J_Renderer::update (void) {

    // Update the renderer to render everything to the screen.
    SDL_RenderPresent(renderer);
}



void J_Renderer::setViewport (const J_Quad arg_viewport) {

    // Set the viewport to the quad passed.
    if (SDL_RenderSetViewport(renderer, &arg_viewport.quad) != 0) { J_Error::log("J_ERROR_RENDERER_SET_VIEWPORT"); }
}

void J_Renderer::setScale (const float arg_scale_x, const float arg_scale_y) {

    // Set the scale to the values passed, if they are valid.
    if ((arg_scale_x < 0.0) || (arg_scale_y < 0.0)) { J_Error::log("J_ERROR_RENDERER_SCALE_RANGE"); }
    if (SDL_RenderSetScale(renderer, arg_scale_x, arg_scale_y) != 0) { J_Error::log("J_ERROR_RENDERER_SET_SCALE"); }
}

void J_Renderer::setColour (const J_Colour& arg_colour) {

    // Set the renderer's new draw colour using the colour data passed.
    if (SDL_SetRenderDrawColor(renderer, arg_colour.red, arg_colour.green, arg_colour.blue, arg_colour.alpha) != 0) { J_Error::log("J_ERROR_RENDERER_SET_COLOUR"); }
    if (SDL_SetRenderDrawBlendMode(renderer, arg_colour.blendmode) != 0) { J_Error::log("J_ERROR_RENDERER_SET_BLENDMODE"); }
}



void J_Renderer::getViewport (J_Quad* arg_quad) { SDL_RenderGetViewport(renderer, &arg_quad->quad); }

void J_Renderer::getScale (float* arg_scale_x, float* arg_scale_y) { SDL_RenderGetScale(renderer, arg_scale_x, arg_scale_y); }

J_Colour J_Renderer::getDefaultColour (void) { return DEFAULT_COLOUR; }



void J_Renderer::terminate (void) {

    // Destroy the renderer.
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
}

/// </J_RENDERER> /////////////////////////////////////////////////////////////
