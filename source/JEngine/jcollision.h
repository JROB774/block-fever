#ifndef INCLUDE_J_COLLISION
#define INCLUDE_J_COLLISION

/// <J_COLLIDER> //////////////////////////////////////////////////////////////

struct J_Collider
{
    public:

    // The quad for the collider.
    J_Quad quad;
};

bool operator==(const J_Collider&, const J_Collider&);
bool operator!=(const J_Collider&, const J_Collider&);

/// </J_COLLIDER> /////////////////////////////////////////////////////////////

//
//
//
//

/// <J_COLLISION> /////////////////////////////////////////////////////////////

class J_Collision
{
    public:

        /// DESCRIPTION:
        // The constructor.
        //
        J_Collision(void) = delete;
        J_Collision(const J_Collision&) = delete;
        J_Collision(J_Collision&&) = delete;

        /// DESCRIPTION:
        // The assignment operator.
        //
        J_Collision& operator=(const J_Collision&) = delete;
        J_Collision& operator=(J_Collision&&) = delete;

        /// DESCRIPTION:
        // Handle a collision between two different collision points/boxes.
        //
        /// ARGUMENTS:
        // The two collision points/boxes.
        //
        /// RETURN VALUES:
        // True if there was a collision.
        // False if there was no collision.
        //
        static bool handleCollision(const J_Collider&, const J_Collider&);
        static bool handleCollision(const int, const int, const J_Collider&);
        static bool handleCollision(const int, const int, const int, const int);

        /// DESCRIPTION:
        // Render a collider.
        //
        /// ARGUMENTS:
        // The collider to render.
        //
        static void renderCollider(const J_Collider&);

        /// DESCRIPTON:
        // Handle all collision related events.
        //
        /// ARGUEMENTS:
        // The event handler.
        //
        static void handle(const SDL_Event&);

        /// DESCRIPTION:
        // The destructor.
        //
        ~J_Collision(void) = delete;

    private:

        // The flag stating whether collider shall be rendered or not.
        static bool renderColliders;
        // The flag stating whether to render colliders filled or outline.
        static bool renderCollidersFilled;
};

/// </J_COLLISION> ////////////////////////////////////////////////////////////

#endif // INCLUDE_J_COLLISION
