#ifndef SCORINGMGR_H
#define SCORINGMGR_H

#include "api.h"

class ScoringMgr {
    /**
     * External 7:1 reduction between the DR4B motors and the lift's driven gear.
     */
    static constexpr double DR4B_GEAR_RATIO = 7.0;

    pros::MotorGroup &DR4B;
    pros::MotorGroup &claw_rot;
    pros::MotorGroup &claw;

public:
    ScoringMgr(pros::MotorGroup &DR4B, pros::MotorGroup &claw_rot, pros::MotorGroup &claw);

    bool score();

    bool flip();

    bool elevate(int level);

    int get_elevation();

private:
    static double motor_to_lift_deg(double motor_deg);

    static double lift_to_motor_deg(double lift_deg);
};
#endif // SCORINGMGR_H
