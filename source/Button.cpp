#include "Button.h"

const int Button::WIDTH = 40, Button::HEIGHT = 40;
const int Button::ENDING_Y = 480 - (86 + 15);
const float Button::VELOCITY_Y = 0.6;
const float Button::TERMINAL_VELOCITY = 21.5;



void Button::create (const int arg_x, const int arg_y, const int arg_type) {

    // Load and create the buton image.
    image = J_Renderer::createImage("Buttons");

    // Load and create the button mask.
    mask = J_Renderer::createImage("Button_Mask");
    J_Colour maskColour = { 255, 255, 255, 63, SDL_BLENDMODE_BLEND };
    J_Renderer::setImageColour(&mask, maskColour);

    // Set the button position and velocity.
    x = arg_x, y = arg_y;
    velY = 0.0;

    // Create and allocate the button sprites.
    sprite = new(std::nothrow) J_Quad[TYPE_TOTAL];
    if (sprite == nullptr) { J_Error::log("GAME_ERROR_BUTTON_ALLOCATE"); }

    for (int i = 0, iy = 0; i < TYPE_TOTAL; ++i, iy += HEIGHT) {

        sprite[i].quad = { 0, iy, WIDTH, HEIGHT };
    }

    // Set the collider.
    collider.quad.quad = { x, y, WIDTH, HEIGHT };
    collider.quad.colour = { 128, 128, 128, 255, SDL_BLENDMODE_BLEND };

    // Load and create the click sound.
    click = J_Mixer::createSound("Button");

    // Set the button type.
    type = arg_type;

    if (type < TYPE_QUIT) { type = TYPE_QUIT; }
    else if (type > TYPE_RESTART) { type = TYPE_RESTART; }

    // Set the landed flag.
    landed = false;
}



void Button::handle (void (*arg_process) (void)) {

    // If the button was clicked on then call the button's process.
    if (landed) {

        if (J_Collision::handleCollision(Cursor::getX(), Cursor::getY(), collider)) {

            J_Mixer::playSound(click, 0);
            (*arg_process)();
        }
    }
}



void Button::step (void) {

    // Move the button downwards.
    if (!landed) {

        if (y > ENDING_Y) {

            velY += VELOCITY_Y;
            if (velY > TERMINAL_VELOCITY) { velY = TERMINAL_VELOCITY; }

            y -= velY;
            if (y < ENDING_Y) { y = ENDING_Y; }
            collider.quad.quad.y = y;

            landed = false;
        }
        else { landed = true; }
    }
    else {

        // If the mouse is over the button, highlight it.
        if (J_Collision::handleCollision(Cursor::getX(), Cursor::getY(), collider)) { renderMask = true; }
        else { renderMask = false; }
    }
}



void Button::render (void) {

    // Render the button.
    J_Renderer::renderImage(image, x, y, &sprite[type]);

    // Render the mask.
    if (renderMask) {

        J_Renderer::renderImage(mask, x, y, nullptr);
    }

    // Render the collider.
    J_Collision::renderCollider(collider);
}



int Button::getWidth (void) { return WIDTH; }

int Button::getHeight (void) { return HEIGHT; }

bool Button::hasLanded (void) const { return landed; }



void Button::destroy (void) {

    // Destroy the button image and mask.
    J_Renderer::destroyImage(&image);
    J_Renderer::destroyImage(&mask);

    // Reset the button position and velocity.
    x = 0, y = 0;
    velY = 0.0;

    // Delete and deallocate the button sprites.
    delete[] sprite;
    sprite = nullptr;

    // Destroy the collider.
    collider.quad.quad = { 0, 0, 0, 0 };
    collider.quad.colour = { 0, 0, 0, 255, SDL_BLENDMODE_BLEND };

    // Destroy the button click sound.
    J_Mixer::destroySound(&click);

    // Reset the button type.
    type = TYPE_QUIT;

    // Reset the landed flag.
    landed = false;
}

Button::~Button (void) { destroy(); }
