#ifndef CLAW_MGR_H
#define CLAW_MGR_H

#include "api.h"

class ClawMgr {
    pros::v5::MotorGroup &DR4B;
    pros::MotorGroup &claw_rot;
    pros::MotorGroup &claw;

public:
    ClawMgr(pros::MotorGroup &DR4B, pros::MotorGroup &claw, pros::MotorGroup &claw_rot);
};
#endif // CLAW_MGR_H
