int Highscore::highscore;



void Highscore::setScore (const int arg_highscore) {

    highscore = arg_highscore;
}

int Highscore::getScore (void) {

    return highscore;
}



bool Highscore::addScore (const int arg_score) {

    bool newBest = (arg_score > highscore);
    if (newBest) { highscore = arg_score; }
    return newBest;
}



void Highscore::reset (void) {

    highscore = 0;
}
