/// <BLOCK> ///////////////////////////////////////////////////////////////////

const int Block::WIDTH = 32, Block::HEIGHT = 32;



void Block::create (const int arg_x, const int arg_y) {

    // Create the block at the set position.
    x = arg_x, y = arg_y;

    image = J_Renderer::createImage("Block");

    mask = J_Renderer::createImage("Block_Mask");
    J_Colour maskColour = { 255, 255, 255, 63, SDL_BLENDMODE_BLEND };
    J_Renderer::setImageColour(&mask, maskColour);

    renderMask = false;

    healthy = J_Renderer::createAnimation("BlockHealthy");
    sick = J_Renderer::createAnimation("BlockSick");
    corrupt = J_Renderer::createAnimation("BlockCorrupt");
    immune = J_Renderer::createAnimation("BlockImmune");

    healthyConvert = J_Renderer::createAnimation("BlockHealthyConvert");
    sickConvert = J_Renderer::createAnimation("BlockSickConvert");
    corruptConvert = J_Renderer::createAnimation("BlockCorruptConvert");
    immuneConvert = J_Renderer::createAnimation("BlockImmuneConvert");

    sickSpecial = J_Renderer::createAnimation("BlockSickSpecial");

    healthyNoise = J_Mixer::createSound("Healthy");
    sickNoise = J_Mixer::createSound("Sick");
    corruptNoise = J_Mixer::createSound("Corrupt");
    immuneNoise = J_Mixer::createSound("Immune");

    collider.quad.quad = { x, y, WIDTH, HEIGHT };

    corruptCounter = 0;
    cooldownCounter = 0;

    state = STATE_HEALTHY;
}



void Block::step (void) {

    // If the block is converting see if it is done and set its new state.
    switch (state) {

        case (STATE_HEALTHY) : { if (cooldownCounter > 0) { --cooldownCounter; } break; }

        case (STATE_HEALTHY_CONVERT) : {

            corruptCounter = 0;
            cooldownCounter = 30;

            if (J_Renderer::isAnimationDone(healthyConvert)) {

                state = STATE_HEALTHY;
                J_Renderer::resetAnimation(&healthyConvert);
            }

            break;
        }

        case (STATE_SICK_CONVERT) : {

            if (J_Renderer::isAnimationDone(sickConvert)) {

                state = STATE_SICK;
                J_Renderer::resetAnimation(&sickConvert);
            }

            break;
        }

        case (STATE_SICK) : {

            if (corruptCounter <= 0) { if ((rand() % 39000) <= 2) { corruptCounter = (60 * 9.5); } }
            else {

                --corruptCounter;
                if (corruptCounter == 0) { setState(STATE_CORRUPT_CONVERT); }
            }

            break;
        }

        case (STATE_CORRUPT_CONVERT) : {

            corruptCounter = 0;

            if (J_Renderer::isAnimationDone(corruptConvert)) {

                state = STATE_CORRUPT;
                J_Renderer::resetAnimation(&corruptConvert);
            }

            break;
        }

        case (STATE_IMMUNE_CONVERT) : {

            if (J_Renderer::isAnimationDone(immuneConvert)) {

                state = STATE_IMMUNE;
                J_Renderer::resetAnimation(&immuneConvert);
            }

            break;
        }
    }
}



void Block::render (void) {

    // Render the block based on it's current state, and it's collider.
    switch (state) {

        case (STATE_HEALTHY) : {

            J_Renderer::renderImage(image, x, y, J_Renderer::playAnimation(&healthy));

            collider.quad.colour = { 0, 0, 255, 255, SDL_BLENDMODE_BLEND };
            J_Collision::renderCollider(collider);

            break;
        }

        case (STATE_HEALTHY_CONVERT) : { J_Renderer::renderImage(image, x, y, J_Renderer::playAnimation(&healthyConvert)); break; }

        case (STATE_SICK_CONVERT) : { J_Renderer::renderImage(image, x, y, J_Renderer::playAnimation(&sickConvert)); break; }

        case (STATE_SICK) : {

            if (corruptCounter == 0) { J_Renderer::renderImage(image, x, y, J_Renderer::playAnimation(&sick)); }
            else { J_Renderer::renderImage(image, x, y, J_Renderer::playAnimation(&sickSpecial)); }

            collider.quad.colour = { 0, 255, 127, 255, SDL_BLENDMODE_BLEND };
            J_Collision::renderCollider(collider);

            break;
        }

        case (STATE_CORRUPT_CONVERT) : { J_Renderer::renderImage(image, x, y, J_Renderer::playAnimation(&corruptConvert)); break; }

        case (STATE_CORRUPT) : {

            J_Renderer::renderImage(image, x, y, J_Renderer::playAnimation(&corrupt));

            collider.quad.colour = { 0, 255, 0, 255, SDL_BLENDMODE_BLEND };
            J_Collision::renderCollider(collider);

            break;
        }

        case (STATE_IMMUNE_CONVERT) :{ J_Renderer::renderImage(image, x, y, J_Renderer::playAnimation(&immuneConvert)); break; }

        case (STATE_IMMUNE) : {

            J_Renderer::renderImage(image, x, y, J_Renderer::playAnimation(&immune));

            collider.quad.colour = { 64, 64, 64, 255, SDL_BLENDMODE_BLEND };
            J_Collision::renderCollider(collider);

            break;
        }
    }

    // If the mask needs to be rendered, render it.
    if (renderMask) {

        J_Renderer::renderImage(mask, x, y, nullptr);
        renderMask = false;
    }
}



void Block::setRenderMask (void) { renderMask = true; }

void Block::setState (const int arg_state) {

    // Set the new state, if it's out of range set the state to healthy.
    state = arg_state;
    if ((state < STATE_HEALTHY) || (state > STATE_IMMUNE)) { state = STATE_HEALTHY; }

    // Make sure the block cools down before being converted sick again.
    if ((state == STATE_SICK_CONVERT) && (cooldownCounter > 0)) { state = STATE_HEALTHY; }

    // If it is a conversion then play the appropriate sound.
    switch (state) {

        case (STATE_HEALTHY_CONVERT) : { J_Mixer::playSound(healthyNoise, 0); break; }

        case (STATE_SICK_CONVERT) : { J_Mixer::playSound(sickNoise, 0); break; }

        case (STATE_CORRUPT_CONVERT) : { J_Mixer::playSound(corruptNoise, 0); break; }

        case (STATE_IMMUNE_CONVERT) : { J_Mixer::playSound(immuneNoise, 0); break; }
    }
}



int Block::getWidth (void) { return WIDTH; }

int Block::getHeight (void) { return HEIGHT; }

J_Collider Block::getCollider (void) const { return collider; }

int Block::getState (void) const { return state; }



void Block::destroy (void) {

    // Destroy the block.
    x = 0, y = 0;

    J_Renderer::destroyImage(&image);

    J_Renderer::destroyImage(&mask);
    renderMask = false;

    J_Renderer::destroyAnimation(&healthy);
    J_Renderer::destroyAnimation(&sick);
    J_Renderer::destroyAnimation(&corrupt);
    J_Renderer::destroyAnimation(&immune);

    J_Renderer::destroyAnimation(&healthyConvert);
    J_Renderer::destroyAnimation(&sickConvert);
    J_Renderer::destroyAnimation(&corruptConvert);
    J_Renderer::destroyAnimation(&immuneConvert);

    J_Mixer::destroySound(&healthyNoise);
    J_Mixer::destroySound(&sickNoise);
    J_Mixer::destroySound(&corruptNoise);
    J_Mixer::destroySound(&immuneNoise);

    collider.quad.quad = { 0, 0, 0, 0 };

    corruptCounter = 0;
    cooldownCounter = 0;

    state = STATE_HEALTHY;
}

Block::~Block (void) { destroy(); }

/// </BLOCK> //////////////////////////////////////////////////////////////////
