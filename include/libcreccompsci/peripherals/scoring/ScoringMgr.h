#ifndef SCORINGMGR_H
#define SCORINGMGR_H

#include "api.h"

class ScoringMgr {

    pros::MotorGroup& DR4B;
    pros::MotorGroup& claw_rot;
    pros::MotorGroup& claw;

public:
    ScoringMgr(pros::MotorGroup& DR4B, pros::MotorGroup& claw_rot, pros::MotorGroup& claw): DR4B(DR4B), claw_rot(claw_rot), claw(claw) {}

    bool score() {
        //TODO implement
        return true;
    }

    bool flip() {
        //TODO implement
        return true;
    }

    bool elevate(int level) {
        //TODO implement
        return true;
    }

    int get_elevation() {
        //TODO implement
        return 0;
    }
};
#endif // SCORINGMGR_H
