/// <STAGE> ///////////////////////////////////////////////////////////////////

const int Stage::BLOCK_ARRAY_WIDTH = 15, Stage::BLOCK_ARRAY_HEIGHT = 15;
Block* Stage::block;
const int Stage::STARTING_CORRUPTION = 4;
const int Stage::STARTING_SICKNESS = 25;
J_Image Stage::sidebar;
J_Font Stage::bigNumbers;
int Stage::convertToSickCounter = 0;
const int Stage::MIN_CONVERT_TO_SICK_TIME = 65, Stage::MAX_CONVERT_TO_SICK_TIME = 150;
int Stage::convertToCorruptCounter = 0;
const int Stage::MIN_CONVERT_TO_CORRUPT_TIME = 115, Stage::MAX_CONVERT_TO_CORRUPT_TIME = 240;
int Stage::money = 0;
const int Stage::SICK_BLOCK_MONEY = 15;
const int Stage::IMMUNE_BLOCK_COST = 25;
int Stage::healthyTotal = 0, Stage::sickTotal = 0, Stage::corruptTotal = 0, Stage::immuneTotal = 0;
J_Quad Stage::fade;
const Uint8 Stage::FADE_TRANSPARENCY = 255;
const Uint8 Stage::FADE_AMOUNT = 5;
int Stage::burstCounter = 0;
int Stage::stageTime = 0;
int Stage::state = -1;



void Stage::initialise (void) {

    // Allocate memory for all the blocks in the board.
    block = new(std::nothrow) Block[BLOCK_ARRAY_WIDTH * BLOCK_ARRAY_HEIGHT];
    if (block == nullptr) { J_Error::log("GAME_ERROR_STAGE_BLOCK_ALLOCATE"); }

    // Create each individual block.
    for (int y = 0; y < BLOCK_ARRAY_HEIGHT; ++y)
    {
        for (int x = 0; x < BLOCK_ARRAY_WIDTH; ++x)
        {
            block[y
            * BLOCK_ARRAY_HEIGHT + x].create((x * Block::getWidth()), (y * Block::getHeight()));
        }
    }

    // Load and create the stage media.
    sidebar = J_Renderer::createImage("Sidebar");
    bigNumbers = J_Renderer::createFont("BigNumbers");

    // Initialise the pause screen.
    Pause::initalise();
}



void Stage::generate (void) {

    // Set all the blocks to healthy blocks, just in case.
    for (int y = 0; y < BLOCK_ARRAY_HEIGHT; ++y) {

        for (int x = 0; x < BLOCK_ARRAY_WIDTH; ++x) {

            block[y * BLOCK_ARRAY_HEIGHT + x].setState(Block::STATE_HEALTHY);
        }
    }

    // Create an array to store all the taken corruption positions.
    int takenPosition[STARTING_CORRUPTION][2];

    for (int iy = 0; iy < STARTING_CORRUPTION; ++iy)
    {
        for (int ix = 0; ix < 2; ++ix)
        {
            takenPosition[iy][ix] = -1;
        }
    }

    // Randomly generate the starting corrupt and sick blocks.
    for (int i = 0; i < STARTING_CORRUPTION; ++i) {

        // Spawn a corrupt block randomly.
        int x = 0, y = 0;
        int sicknessSubtract = 0;

        while (true) {

            bool positionTaken = false;
            x = rand() % BLOCK_ARRAY_WIDTH, y = rand() % BLOCK_ARRAY_HEIGHT;

            for (int iy = 0; iy < STARTING_CORRUPTION; ++iy) {

                if ((x == takenPosition[iy][0]) && (y == takenPosition[iy][1])) {

                    positionTaken = true;
                }
            }

            if (!positionTaken) {

                block[y * BLOCK_ARRAY_HEIGHT + x].setState(Block::STATE_CORRUPT);
                takenPosition[i][0] = x, takenPosition[i][1] = y;

                break;
            }
        }

        // Spawn some sickness around the corrupt block.
        for (int yy = (y - 1); yy < (y + 2); ++yy) {

            for (int xx = (x - 1); xx < (x + 2); ++xx) {

                // 1/10 chance to not spawn a block.
                if ((rand() % 100 + 1) > 10) {

                    if (((yy * BLOCK_ARRAY_HEIGHT + xx) >= 0) && ((yy * BLOCK_ARRAY_HEIGHT + xx) < (BLOCK_ARRAY_WIDTH * BLOCK_ARRAY_HEIGHT))) {

                        if (xx == ((x - 1) + 2)) {

                            if (((yy * BLOCK_ARRAY_HEIGHT + xx) % BLOCK_ARRAY_WIDTH) != 0) {

                                if (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() != Block::STATE_CORRUPT) {

                                    block[yy * BLOCK_ARRAY_HEIGHT + xx].setState(Block::STATE_SICK);
                                    ++sicknessSubtract;
                                }
                            }
                        }
                        else if (xx == (x - 1)) {

                            if ((((yy * BLOCK_ARRAY_HEIGHT + xx) + 1) % BLOCK_ARRAY_WIDTH) != 0) {

                                if (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() != Block::STATE_CORRUPT) {

                                    block[yy * BLOCK_ARRAY_HEIGHT + xx].setState(Block::STATE_SICK);
                                    ++sicknessSubtract;
                                }
                            }
                        }
                        else {

                            if (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() != Block::STATE_CORRUPT) {

                                block[yy * BLOCK_ARRAY_HEIGHT + xx].setState(Block::STATE_SICK);
                                ++sicknessSubtract;
                            }
                        }
                    }
                }
            }
        }

        // Spawn a trail of sickness starting from a corruption block.
        int sicknessTrail = STARTING_SICKNESS - sicknessSubtract;
        int xxx = x, yyy = y;
        int prevDirection = -1, direction = -1;

        while (sicknessTrail > 0) {

            // Select a direction to move.
            prevDirection = direction;
            while (direction == prevDirection) { direction = rand() % 4; }

            // Check to see if the sickness can be placed then place it.
            switch (direction) {

                case (0) : {

                    if ((((yyy - 1) * BLOCK_ARRAY_HEIGHT + xxx) >= 0) && (((yyy - 1) * BLOCK_ARRAY_HEIGHT + xxx) < (BLOCK_ARRAY_WIDTH * BLOCK_ARRAY_HEIGHT))) {

                        if (block[(yyy - 1) * BLOCK_ARRAY_HEIGHT + xxx].getState() != Block::STATE_CORRUPT) {

                            if (block[(yyy - 1) * BLOCK_ARRAY_HEIGHT + xxx].getState() == Block::STATE_HEALTHY) { --sicknessTrail; }
                            --yyy;
                            block[yyy * BLOCK_ARRAY_HEIGHT + xxx].setState(Block::STATE_SICK);
                        }
                    }

                    break;
                }

                case (1) : {

                    if (((yyy * BLOCK_ARRAY_HEIGHT + (xxx + 1)) >= 0) && ((yyy * BLOCK_ARRAY_HEIGHT + (xxx + 1)) < (BLOCK_ARRAY_WIDTH * BLOCK_ARRAY_HEIGHT))) {

                        if ((((yyy * BLOCK_ARRAY_HEIGHT + xxx) + 1) % BLOCK_ARRAY_WIDTH) != 0) {

                            if (block[yyy * BLOCK_ARRAY_HEIGHT + (xxx + 1)].getState() != Block::STATE_CORRUPT) {

                                if (block[yyy * BLOCK_ARRAY_HEIGHT + (xxx + 1)].getState() == Block::STATE_HEALTHY) { --sicknessTrail; }
                                ++xxx;
                                block[yyy * BLOCK_ARRAY_HEIGHT + xxx].setState(Block::STATE_SICK);
                            }
                        }
                    }

                    break;
                }

                case (2) : {

                    if ((((yyy + 1) * BLOCK_ARRAY_HEIGHT + xxx) >= 0) && (((yyy + 1) * BLOCK_ARRAY_HEIGHT + xxx) < (BLOCK_ARRAY_WIDTH * BLOCK_ARRAY_HEIGHT))) {

                        if (block[(yyy + 1) * BLOCK_ARRAY_HEIGHT + xxx].getState() != Block::STATE_CORRUPT) {

                            if (block[(yyy + 1) * BLOCK_ARRAY_HEIGHT + xxx].getState() == Block::STATE_HEALTHY) { --sicknessTrail; }
                            ++yyy;
                            block[yyy * BLOCK_ARRAY_HEIGHT + xxx].setState(Block::STATE_SICK);
                        }
                    }

                    break;
                }

                case (3) : {

                    if (((yyy * BLOCK_ARRAY_HEIGHT + (xxx - 1)) >= 0) && ((yyy * BLOCK_ARRAY_HEIGHT + (xxx - 1)) < (BLOCK_ARRAY_WIDTH * BLOCK_ARRAY_HEIGHT))) {

                        if (((yyy * BLOCK_ARRAY_HEIGHT + xxx) % BLOCK_ARRAY_WIDTH) != 0) {

                            if (block[yyy * BLOCK_ARRAY_HEIGHT + (xxx - 1)].getState() != Block::STATE_CORRUPT) {

                                if (block[yyy * BLOCK_ARRAY_HEIGHT + (xxx - 1)].getState() == Block::STATE_HEALTHY) { --sicknessTrail; }
                                --xxx;
                                block[yyy * BLOCK_ARRAY_HEIGHT + xxx].setState(Block::STATE_SICK);
                            }
                        }
                    }

                    break;
                }
            }
        }
    }

    // Set the starting time for the conversion counters.
    convertToSickCounter = MIN_CONVERT_TO_SICK_TIME;
    convertToCorruptCounter = MAX_CONVERT_TO_CORRUPT_TIME;

    // Set the starting amount of money.
    money = 0;

    // Set the foreground darkness fade.
    fade.quad = { 0, 0, 640, 480 };
    fade.colour = { 29, 25, 16, FADE_TRANSPARENCY, SDL_BLENDMODE_BLEND };

    // Set the burst counter.
    burstCounter = 0;

    // Set the stage time.
    stageTime = 0;

    // Set the stage's state to generate.
    state = STATE_GENERATE;
}



void Stage::handle (void) {

    if (state == STATE_PLAYING) {

        // Convert a healthy block to immune, or a sick block to healthy if they are clicked on.
        if (J_System::getEvent().type == SDL_MOUSEBUTTONDOWN) {

            if (J_System::getEvent().button.button == SDL_BUTTON_LEFT) {

                for (int y = 0; y < BLOCK_ARRAY_HEIGHT; ++y) {

                    for (int x = 0; x < BLOCK_ARRAY_WIDTH; ++x) {

                        if (block[y * BLOCK_ARRAY_HEIGHT + x].getState() == Block::STATE_SICK) {

                            bool shouldConvert = false;

                            // The sick block can only be made healthy if there is a healthy block surrounding it.
                            for (int yy = (y - 1); yy < (y + 2); ++yy) {

                                for (int xx = (x - 1); xx < (x + 2); ++xx) {

                                    if (((yy * BLOCK_ARRAY_HEIGHT + xx) >= 0) && ((yy * BLOCK_ARRAY_HEIGHT + xx) < (BLOCK_ARRAY_WIDTH * BLOCK_ARRAY_HEIGHT))) {

                                        if (xx == ((x - 1) + 2)) {

                                            if (((yy * BLOCK_ARRAY_HEIGHT + xx) % BLOCK_ARRAY_WIDTH) != 0) {

                                                if ((block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_HEALTHY) ||
                                                    (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_HEALTHY_CONVERT)) {

                                                    shouldConvert = true;
                                                }
                                            }
                                        }
                                        else if (xx == (x - 1)) {

                                            if ((((yy * BLOCK_ARRAY_HEIGHT + xx) + 1) % BLOCK_ARRAY_WIDTH) != 0) {

                                                if ((block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_HEALTHY) ||
                                                    (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_HEALTHY_CONVERT)) {

                                                    shouldConvert = true;
                                                }
                                            }
                                        }
                                        else {

                                            if ((block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_HEALTHY) ||
                                                (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_HEALTHY_CONVERT)) {

                                                shouldConvert = true;
                                            }
                                        }
                                    }
                                }
                            }

                            if (shouldConvert) {

                                if (J_Collision::handleCollision(Cursor::getX(), Cursor::getY(), block[y * BLOCK_ARRAY_HEIGHT + x].getCollider())) {

                                    block[y * BLOCK_ARRAY_HEIGHT + x].setState(Block::STATE_HEALTHY_CONVERT);
                                    money += SICK_BLOCK_MONEY;
                                }
                            }
                        }
                    }
                }
            }
            else if (J_System::getEvent().button.button == SDL_BUTTON_RIGHT) {

                for (int y = 0; y < BLOCK_ARRAY_HEIGHT; ++y) {

                    for (int x = 0; x < BLOCK_ARRAY_WIDTH; ++x) {

                        if (block[y * BLOCK_ARRAY_HEIGHT + x].getState() == Block::STATE_HEALTHY) {

                            // The healthy block can only be made immune if the player has enough money.
                            if (money >= IMMUNE_BLOCK_COST) {

                                if (J_Collision::handleCollision(Cursor::getX(), Cursor::getY(), block[y * BLOCK_ARRAY_HEIGHT + x].getCollider())) {

                                    block[y * BLOCK_ARRAY_HEIGHT + x].setState(Block::STATE_IMMUNE_CONVERT);
                                    money -= IMMUNE_BLOCK_COST;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else if (state == STATE_PAUSED) { Pause::handle(); }

    // Pause or unpsause the game if the 'P' key is pressed.
    if (J_System::getEvent().type == SDL_KEYDOWN) {

        if (J_System::getEvent().key.keysym.sym == SDLK_p) {

            if (state == STATE_PLAYING) { state = STATE_PAUSED; }
            else if (state == STATE_PAUSED) { state = STATE_PLAYING; }
        }
    }

    // Debug Commands
    if (J_System::isDebug()) {

        if (state == STATE_PLAYING) {

            if (J_System::getEvent().type == SDL_KEYDOWN) {

                switch(J_System::getEvent().key.keysym.sym) {

                    case (SDLK_x) : {

                        GameOver::setBestScore(Highscore::addScore(healthyTotal));
                        GameOver::setBlocksSaved(healthyTotal);
                        state = STATE_INACTIVE;
                        break;
                    }

                    case (SDLK_c) : {

                        generate();
                        break;
                    }

                    case (SDLK_v) : {

                        money = 10000;
                        break;
                    }
                }
            }
        }
    }
}



void Stage::step (void) {

    if (state == STATE_PLAYING) {

        // When the sick conversion counter is done counting.
        if (convertToSickCounter == 0) {

            // Iterate through all the blocks until a healthy one is found.
            for (int y = 0; y < BLOCK_ARRAY_HEIGHT; ++y) {

                for (int x = 0; x < BLOCK_ARRAY_WIDTH; ++x) {

                    if (block[y * BLOCK_ARRAY_HEIGHT + x].getState() == Block::STATE_HEALTHY) {

                        // Check to see how many sick/corrupt blocks are surrounding the healthy block.
                        int sickConversionChance = 0;

                        for (int yy = (y - 1); yy < (y + 2); ++yy) {

                            for (int xx = (x - 1); xx < (x + 2); ++xx) {

                                if (((yy * BLOCK_ARRAY_HEIGHT + xx) >= 0) && ((yy * BLOCK_ARRAY_HEIGHT + xx) < (BLOCK_ARRAY_WIDTH * BLOCK_ARRAY_HEIGHT))) {

                                    // The more sick/corrupt blocks surrounding the healthy one the higher the chance of conversion.
                                    if (xx == ((x - 1) + 2)) {

                                        if (((yy * BLOCK_ARRAY_HEIGHT + xx) % BLOCK_ARRAY_WIDTH) != 0) {

                                            switch (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState()) {

                                                case(Block::STATE_HEALTHY) : { sickConversionChance -= 3; break; }

                                                case(Block::STATE_SICK) : { sickConversionChance += 10; break; }

                                                case(Block::STATE_CORRUPT) : { sickConversionChance += 35; break; }
                                            }
                                        }
                                    }
                                    else if (xx == (x - 1)) {

                                        if ((((yy * BLOCK_ARRAY_HEIGHT + xx) + 1) % BLOCK_ARRAY_WIDTH) != 0) {

                                            switch (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState()) {

                                                case(Block::STATE_HEALTHY) : { sickConversionChance -= 3; break; }

                                                case(Block::STATE_SICK) : { sickConversionChance += 10; break; }

                                                case(Block::STATE_CORRUPT) : { sickConversionChance += 35; break; }
                                            }
                                        }
                                    }
                                    else {

                                        switch (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState()) {

                                            case(Block::STATE_HEALTHY) : { sickConversionChance -= 3; break; }

                                            case(Block::STATE_SICK) : { sickConversionChance += 10; break; }

                                            case(Block::STATE_CORRUPT) : { sickConversionChance += 35; break; }
                                        }
                                    }
                                }
                            }
                        }

                        // Convert the block from healthy to sick.
                        if ((rand() % 110 + 1) <= sickConversionChance) {

                            block[y * BLOCK_ARRAY_HEIGHT + x].setState(Block::STATE_SICK_CONVERT);
                        }
                    }
                }
            }

            // Reset the conversion counter.
            if (sickTotal <= 7) {

                if (burstCounter <= 0) {

                    if ((rand() % 200) <= 25) {

                        burstCounter = rand() % 12 + 5;
                    }
                }
            }
            else {

                if (burstCounter > 0) {

                    convertToSickCounter = 5;
                    --burstCounter;
                }
                else {

                    convertToSickCounter = (int)((rand() % MAX_CONVERT_TO_SICK_TIME + MIN_CONVERT_TO_SICK_TIME) - ((0.35f * (sickTotal + corruptTotal)) + (0.0003f * stageTime)));
                    if (convertToSickCounter < 0 ) { convertToSickCounter = 0; }
                }
            }
        }
        else { --convertToSickCounter; }

        // When the corrupt conversion counter is done counting.
        if (convertToCorruptCounter == 0) {

            // Iterate through all the blocks until a sick one is found.
            for (int y = 0; y < BLOCK_ARRAY_HEIGHT; ++y) {

                for (int x = 0; x < BLOCK_ARRAY_WIDTH; ++x) {

                    if (block[y * BLOCK_ARRAY_HEIGHT + x].getState() == Block::STATE_SICK) {

                        // Check to see how many corrupt blocks are surrounding the sick block.
                        int corruptConversionChance = 0;

                        for (int yy = (y - 1); yy < (y + 2); ++yy) {

                            for (int xx = (x - 1); xx < (x + 2); ++xx) {

                                if (((yy * BLOCK_ARRAY_HEIGHT + xx) >= 0) && ((yy * BLOCK_ARRAY_HEIGHT + xx) < (BLOCK_ARRAY_WIDTH * BLOCK_ARRAY_HEIGHT))) {

                                    // The more corrupt blocks surrounding the sick one the higher the chance of conversion.
                                    if (xx == ((x - 1) + 2)) {

                                        if (((yy * BLOCK_ARRAY_HEIGHT + xx) % BLOCK_ARRAY_WIDTH) != 0) {

                                            switch (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState()) {

                                                case(Block::STATE_HEALTHY) : { corruptConversionChance -= 10; break; }

                                                case(Block::STATE_CORRUPT) : { corruptConversionChance += 12; break; }
                                            }
                                        }
                                    }
                                    else if (xx == (x - 1)) {

                                        if ((((yy * BLOCK_ARRAY_HEIGHT + xx) + 1) % BLOCK_ARRAY_WIDTH) != 0) {

                                            switch (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState()) {

                                                case(Block::STATE_HEALTHY) : { corruptConversionChance -= 10; break; }

                                                case(Block::STATE_CORRUPT) : { corruptConversionChance += 12; break; }
                                            }
                                        }
                                    }
                                    else {

                                        switch (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState()) {

                                            case(Block::STATE_HEALTHY) : { corruptConversionChance -= 10; break; }

                                            case(Block::STATE_CORRUPT) : { corruptConversionChance += 12; break; }
                                        }
                                    }
                                }
                            }
                        }

                        // Convert the block from sick to corrupt.
                        if ((rand() % 195 + 1) <= corruptConversionChance) {

                            block[y * BLOCK_ARRAY_HEIGHT + x].setState(Block::STATE_CORRUPT_CONVERT);
                        }
                    }
                }
            }

            // Reset the conversion counter.
            convertToCorruptCounter = (int)((rand() % MAX_CONVERT_TO_CORRUPT_TIME + MIN_CONVERT_TO_CORRUPT_TIME) - ((0.15f * (sickTotal + corruptTotal)) + (0.0003f * stageTime)));
            if (convertToCorruptCounter < 0 ) { convertToCorruptCounter = 0; }
        }
        else { --convertToCorruptCounter; }

        // Go through all the block's step events.
        for (int y = 0; y < BLOCK_ARRAY_HEIGHT; ++y) {

            for (int x = 0; x < BLOCK_ARRAY_WIDTH; ++x) {

                block[y * BLOCK_ARRAY_HEIGHT + x].step();
            }
        }

        // Set it so that the healthy/sick block being moused over will be highlighted.
        for (int y = 0; y < BLOCK_ARRAY_HEIGHT; ++y) {

            for (int x = 0; x < BLOCK_ARRAY_WIDTH; ++x) {

                if (block[y * BLOCK_ARRAY_HEIGHT + x].getState() == Block::STATE_SICK) {

                    bool shouldHighlight = false;

                    for (int yy = (y - 1); yy < (y + 2); ++yy) {

                        for (int xx = (x - 1); xx < (x + 2); ++xx) {

                            if (((yy * BLOCK_ARRAY_HEIGHT + xx) >= 0) && ((yy * BLOCK_ARRAY_HEIGHT + xx) < (BLOCK_ARRAY_WIDTH * BLOCK_ARRAY_HEIGHT))) {

                                if (xx == ((x - 1) + 2)) {

                                    if (((yy * BLOCK_ARRAY_HEIGHT + xx) % BLOCK_ARRAY_WIDTH) != 0) {

                                        if ((block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_HEALTHY) ||
                                            (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_HEALTHY_CONVERT)) {

                                            shouldHighlight = true;
                                        }
                                    }
                                }
                                else if (xx == (x - 1)) {

                                    if ((((yy * BLOCK_ARRAY_HEIGHT + xx) + 1) % BLOCK_ARRAY_WIDTH) != 0) {

                                        if ((block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_HEALTHY) ||
                                            (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_HEALTHY_CONVERT)) {


                                            shouldHighlight = true;
                                        }
                                    }
                                }
                                else {

                                    if ((block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_HEALTHY) ||
                                        (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_HEALTHY_CONVERT)) {

                                        shouldHighlight = true;
                                    }
                                }
                            }
                        }
                    }

                    if (shouldHighlight) {

                        if (J_Collision::handleCollision(Cursor::getX(), Cursor::getY(), block[y * BLOCK_ARRAY_HEIGHT + x].getCollider())) {

                            block[y * BLOCK_ARRAY_HEIGHT + x].setRenderMask();
                        }
                    }
                }
                else if (block[y * BLOCK_ARRAY_HEIGHT + x].getState() == Block::STATE_HEALTHY) {

                    if (money >= IMMUNE_BLOCK_COST) {

                        if (J_Collision::handleCollision(Cursor::getX(), Cursor::getY(), block[y * BLOCK_ARRAY_HEIGHT + x].getCollider())) {

                            block[y * BLOCK_ARRAY_HEIGHT + x].setRenderMask();
                        }
                    }
                }
            }
        }

        // Get the total number of each block currently in the stage.
        healthyTotal = 0, sickTotal = 0, corruptTotal = 0, immuneTotal = 0;

        for (int y = 0; y < BLOCK_ARRAY_HEIGHT; ++y) {

            for (int x = 0; x < BLOCK_ARRAY_WIDTH; ++x) {

                switch (block[y * BLOCK_ARRAY_HEIGHT + x].getState()) {

                    case (Block::STATE_HEALTHY) : { ++healthyTotal; break; }

                    case (Block::STATE_SICK) : { ++sickTotal; break; }

                    case (Block::STATE_CORRUPT) : { ++corruptTotal; break; }

                    case (Block::STATE_IMMUNE) : { ++immuneTotal; break; }
                }
            }
        }

        // Check to see if the whole board is sick/corrupt, if so end the game.
        int healthy = 0;

        for (int y = 0; y < BLOCK_ARRAY_HEIGHT; ++y) {

            for (int x = 0; x < BLOCK_ARRAY_WIDTH; ++x) {

                if ((block[y * BLOCK_ARRAY_HEIGHT + x].getState() == Block::STATE_HEALTHY) ||
                    (block[y * BLOCK_ARRAY_HEIGHT + x].getState() == Block::STATE_HEALTHY_CONVERT) ||
                    (block[y * BLOCK_ARRAY_HEIGHT + x].getState() == Block::STATE_SICK_CONVERT) ||
                    (block[y * BLOCK_ARRAY_HEIGHT + x].getState() == Block::STATE_CORRUPT_CONVERT) ||
                    (block[y * BLOCK_ARRAY_HEIGHT + x].getState() == Block::STATE_IMMUNE_CONVERT)) {

                    ++healthy;
                }
            }
        }

        if (healthy <= 0) {

            GameOver::setBestScore(Highscore::addScore(healthyTotal));
            GameOver::setBlocksSaved(healthyTotal);
            state = STATE_INACTIVE;
        }
        else {

            // Check to see if the sickness or corruption can't spread anymore, if so end the game.
            int originalHealthy = healthy;

            for (int y = 0; y < BLOCK_ARRAY_HEIGHT; ++y) {

                for (int x = 0; x < BLOCK_ARRAY_WIDTH; ++x) {

                    if ((block[y * BLOCK_ARRAY_HEIGHT + x].getState() == Block::STATE_HEALTHY) ||
                        (block[y * BLOCK_ARRAY_HEIGHT + x].getState() == Block::STATE_HEALTHY_CONVERT) ||
                        (block[y * BLOCK_ARRAY_HEIGHT + x].getState() == Block::STATE_IMMUNE_CONVERT)) {

                        for (int yy = (y - 1); yy < (y + 2); ++yy) {

                            for (int xx = (x - 1); xx < (x + 2); ++xx) {

                                if (((yy * BLOCK_ARRAY_HEIGHT + xx) >= 0) && ((yy * BLOCK_ARRAY_HEIGHT + xx) < (BLOCK_ARRAY_WIDTH * BLOCK_ARRAY_HEIGHT))) {

                                    if (xx == ((x - 1) + 2)) {

                                        if (((yy * BLOCK_ARRAY_HEIGHT + xx) % BLOCK_ARRAY_WIDTH) != 0) {

                                            if ((block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_SICK) ||
                                                (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_CORRUPT) ||
                                                (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_SICK_CONVERT) ||
                                                (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_CORRUPT_CONVERT)) {

                                                --healthy;
                                            }
                                        }
                                    }
                                    else if (xx == (x - 1)) {

                                        if ((((yy * BLOCK_ARRAY_HEIGHT + xx) + 1) % BLOCK_ARRAY_WIDTH) != 0) {

                                            if ((block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_SICK) ||
                                                (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_CORRUPT) ||
                                                (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_SICK_CONVERT) ||
                                                (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_CORRUPT_CONVERT)) {

                                                --healthy;
                                            }
                                        }
                                    }
                                    else {

                                        if ((block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_SICK) ||
                                            (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_CORRUPT) ||
                                            (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_SICK_CONVERT) ||
                                            (block[yy * BLOCK_ARRAY_HEIGHT + xx].getState() == Block::STATE_CORRUPT_CONVERT)) {

                                            --healthy;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (healthy == originalHealthy) {

                GameOver::setBestScore(Highscore::addScore(healthyTotal));
                GameOver::setBlocksSaved(healthyTotal);
                state = STATE_INACTIVE;
            }
        }
    }
    else if (state == STATE_PAUSED) {

        Pause::step();

        switch (Pause::getState()) {

            case (Pause::STATE_MENU) : { state = STATE_MENU; break; }

            case (Pause::STATE_EXIT) : { state = STATE_EXIT; break; }
        }
    }
    else if (state == STATE_MENU) {

        // Fade out.
        if (fade.colour.alpha < FADE_TRANSPARENCY) {

            fade.colour.alpha += FADE_AMOUNT;
            if (fade.colour.alpha > FADE_TRANSPARENCY) { fade.colour.alpha = FADE_TRANSPARENCY; }
        }
    }
    else if (state == STATE_GENERATE) {

        // Fade in.
        if (fade.colour.alpha > 0) {

            fade.colour.alpha -= FADE_AMOUNT;
            if (fade.colour.alpha < 0) { fade.colour.alpha = 0; }
        }
        else { state = STATE_PLAYING; }
    }

    // Iterate the stage time counter.
    ++stageTime;
}



void Stage::render (void) {

    // Render all the blocks.
    for (int y = 0; y < BLOCK_ARRAY_HEIGHT; ++y) {

        for (int x = 0; x < BLOCK_ARRAY_WIDTH; ++x) {

            block[y * BLOCK_ARRAY_HEIGHT + x].render();
        }
    }

    // Render the sidebar.
    J_Renderer::renderImage(sidebar, BLOCK_ARRAY_WIDTH * Block::getWidth(), 0, nullptr);

    // Render the data stored inside the sidebar.
    std::ostringstream data;
    J_Colour fontColour;

    data << money;
    if (money < IMMUNE_BLOCK_COST) { fontColour = { 232, 60, 60, 255, SDL_BLENDMODE_BLEND }; }
    else { fontColour = { 255, 255, 255, 255, SDL_BLENDMODE_BLEND }; }
    J_Renderer::setFontColour(&bigNumbers, fontColour);
    J_Renderer::renderFont(bigNumbers, ((BLOCK_ARRAY_WIDTH * Block::getWidth()) + 84) - (((int)data.str().length() * J_Renderer::getFontCharWidth(bigNumbers)) / 2), 44, data.str());
    data.str("\0");

    data << healthyTotal;
    fontColour = { 107, 170, 175, 255, SDL_BLENDMODE_BLEND };
    J_Renderer::setFontColour(&bigNumbers, fontColour);
    J_Renderer::renderFont(bigNumbers, ((BLOCK_ARRAY_WIDTH * Block::getWidth()) + 84) - (((int)data.str().length() * J_Renderer::getFontCharWidth(bigNumbers)) / 2), 124, data.str());
    data.str("\0");

    data << sickTotal;
    fontColour = { 107, 175, 107, 255, SDL_BLENDMODE_BLEND };
    J_Renderer::setFontColour(&bigNumbers, fontColour);
    J_Renderer::renderFont(bigNumbers, ((BLOCK_ARRAY_WIDTH * Block::getWidth()) + 84) - (((int)data.str().length() * J_Renderer::getFontCharWidth(bigNumbers)) / 2), 188, data.str());
    data.str("\0");

    data << corruptTotal;
    fontColour = { 83, 204, 69, 255, SDL_BLENDMODE_BLEND };
    J_Renderer::setFontColour(&bigNumbers, fontColour);
    J_Renderer::renderFont(bigNumbers, ((BLOCK_ARRAY_WIDTH * Block::getWidth()) + 84) - (((int)data.str().length() * J_Renderer::getFontCharWidth(bigNumbers)) / 2), 252, data.str());
    data.str("\0");

    data << immuneTotal;
    fontColour = { 150, 134, 133, 255, SDL_BLENDMODE_BLEND };
    J_Renderer::setFontColour(&bigNumbers, fontColour);
    J_Renderer::renderFont(bigNumbers, ((BLOCK_ARRAY_WIDTH * Block::getWidth()) + 84) - (((int)data.str().length() * J_Renderer::getFontCharWidth(bigNumbers)) / 2), 316, data.str());
    data.str("\0");

    // Render the pause screen.
    if ((state == STATE_PAUSED) || (state == STATE_MENU)) { Pause::render(); }

    // Render the fade out or in.
    J_Renderer::drawQuadFilled(fade);
}



bool Stage::hasFadedOut (void) { return (fade.colour.alpha >= FADE_TRANSPARENCY) ? true : false; }

int Stage::getState (void) { return state; }



void Stage::terminate (void) {

    // Destroy each individual block.
    for (int i = 0; i < (BLOCK_ARRAY_WIDTH * BLOCK_ARRAY_HEIGHT); ++i) { block[i].destroy(); }

    // Deallocate the memory for all the blocks in the board.
    delete[] block;
    block = nullptr;

    // Destroy the stage media.
    J_Renderer::destroyImage(&sidebar);
    J_Renderer::destroyFont(&bigNumbers);

    // Reset the conversion counters.
    convertToSickCounter = 0;
    convertToCorruptCounter = 0;

    // Reset the player's money.
    money = 0;

    // Reset the sidebar data values.
    healthyTotal = 0, sickTotal = 0, corruptTotal = 0, immuneTotal = 0;

    // Reset the foreground darkness fade.
    fade.quad = { 0, 0, 640, 480 };
    fade.colour = { 29, 25, 16, 0, SDL_BLENDMODE_BLEND };

    // Reset the burst counter.
    burstCounter = 0;

    // Reset the stage time.
    stageTime = 0;

    // Terminate the pause screen.
    Pause::terminate();

    // Reset the state.
    state = -1;
}

/// </STAGE> //////////////////////////////////////////////////////////////////
