/// <J_COLLIDER> //////////////////////////////////////////////////////////////

bool operator== (const J_Collider& arg_lhs, const J_Collider& arg_rhs) { return arg_lhs.quad == arg_rhs.quad; }

bool operator!= (const J_Collider& arg_lhs, const J_Collider& arg_rhs) { return !operator==(arg_lhs, arg_rhs); }

/// </J_COLLIDER> /////////////////////////////////////////////////////////////

//
//
//
//

/// <J_COLLISION> /////////////////////////////////////////////////////////////

bool J_Collision::renderColliders = false;
bool J_Collision::renderCollidersFilled = false;



bool J_Collision::handleCollision (const J_Collider& arg_first, const J_Collider& arg_second) { return ((arg_first.quad.quad.x < (arg_second.quad.quad.x + arg_second.quad.quad.w)) && ((arg_first.quad.quad.x + arg_first.quad.quad.w) > arg_second.quad.quad.x) && (arg_first.quad.quad.y < (arg_second.quad.quad.y + arg_second.quad.quad.h)) && ((arg_first.quad.quad.y + arg_first.quad.quad.h) > arg_second.quad.quad.y)) ? true : false; }

bool J_Collision::handleCollision (const int arg_x, const int arg_y, const J_Collider& arg_collider) { return ((arg_x >= arg_collider.quad.quad.x) && (arg_x < (arg_collider.quad.quad.x + arg_collider.quad.quad.w)) && (arg_y >= arg_collider.quad.quad.y) && (arg_y < (arg_collider.quad.quad.y + arg_collider.quad.quad.h))) ? true : false; }

bool J_Collision::handleCollision (const int arg_first_x, const int arg_first_y, const int arg_second_x, const int arg_second_y) { return ((arg_first_x == arg_second_x) && (arg_first_y == arg_second_y)) ? true : false; }



void J_Collision::renderCollider (const J_Collider& arg_collider) {

    if (renderColliders) {

        if (renderCollidersFilled) { J_Renderer::drawQuadFilled(arg_collider.quad); }
        else { J_Renderer::drawQuadOutline(arg_collider.quad); }
    }
}



void J_Collision::handle (const SDL_Event& arg_event) {

    if (arg_event.type == SDL_KEYDOWN) {

        switch (arg_event.key.keysym.sym) {

            case (SDLK_1) : { renderColliders = !renderColliders; break; }

            case (SDLK_2) : { renderCollidersFilled = !renderCollidersFilled; break; }
        }
    }
}

/// </J_COLLISION> ////////////////////////////////////////////////////////////
