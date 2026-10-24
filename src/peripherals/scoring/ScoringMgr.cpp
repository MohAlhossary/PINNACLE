#include "libcreccompsci/peripherals/scoring/ScoringMgr.h"


ScoringMgr::ScoringMgr(pros::MotorGroup &DR4B, pros::MotorGroup &claw_rot, pros::MotorGroup &claw) : DR4B(DR4B), claw_rot(claw_rot),
    claw(claw) {

}

bool ScoringMgr::score() {
    //TODO implement
    return true;
}

bool ScoringMgr::flip() {
    //TODO implement
    return true;
}

bool ScoringMgr::elevate(int level) {
    //TODO implement
    return true;
}

int ScoringMgr::get_elevation() {
    //TODO implement
    return 0;
}

double ScoringMgr::motor_to_lift_deg(double motor_deg) {
    return motor_deg / DR4B_GEAR_RATIO;
}

double ScoringMgr::lift_to_motor_deg(double lift_deg) {
    return lift_deg * DR4B_GEAR_RATIO;
}
