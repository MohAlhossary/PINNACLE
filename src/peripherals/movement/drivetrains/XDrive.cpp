#include "libcreccompsci/peripherals/movement/drivetrains/XDrive.h"
#include <algorithm>
#include <cmath>

XDrive::XDrive(pros::MotorGroup &FL, pros::MotorGroup &FR, pros::MotorGroup &BL, pros::MotorGroup &BR) :
    FL(FL), FR(FR), BL(BL), BR(BR) {

}

void XDrive::set_power(double forward, double strafe, double rot) {
    double fl_power = forward + strafe + rot;
    double fr_power = -(forward - strafe - rot);
    double bl_power = forward - strafe + rot;
    double br_power = -(forward + strafe - rot);

    double max_power = std::max({1.0, std::fabs(fl_power), std::fabs(fr_power), std::fabs(bl_power), std::fabs(br_power)});

    FL.move(static_cast<std::int32_t>(127 * fl_power / max_power));
    FR.move(static_cast<std::int32_t>(127 * fr_power / max_power));
    BL.move(static_cast<std::int32_t>(127 * bl_power / max_power));
    BR.move(static_cast<std::int32_t>(127 * br_power / max_power));
}
