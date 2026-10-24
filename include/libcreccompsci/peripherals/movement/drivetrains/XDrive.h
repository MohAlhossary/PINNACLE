#ifndef XDRIVE_H
#define XDRIVE_H

#include "api.h"
#include "Drivetrain.h"

/**
 * Four-wheel X-drive. Every motor must spin its wheel "forward" for positive power
 */
class XDrive : public Drivetrain {
    pros::MotorGroup &FL;
    pros::MotorGroup &FR;
    pros::MotorGroup &BL;
    pros::MotorGroup &BR;

public:
    XDrive(pros::MotorGroup &FL, pros::MotorGroup &FR, pros::MotorGroup &BL, pros::MotorGroup &BR);

    void set_power(double forward, double strafe, double rot) override;
};

#endif //XDRIVE_H
