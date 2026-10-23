#include "libcreccompsci/peripherals/scoring/ClawMgr.h"

ClawMgr::ClawMgr(pros::MotorGroup &DR4B, pros::MotorGroup &claw,
                 pros::MotorGroup &claw_rot) : DR4B(DR4B), claw_rot(claw_rot), claw(claw) {

}
