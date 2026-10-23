#ifndef MOVEMENTMGR_H
#define MOVEMENTMGR_H

#include "api.h"
#include "Drivetrain.h"

class MovementMgr {
    double x;
    double y;
    double rot;

    pros::Gps gps;

    Drivetrain drivetrain;
    // odomngr TODO finish this

public:
    MovementMgr(pros::MotorGroup &FL, pros::MotorGroup &FR, pros::MotorGroup &BL, pros::MotorGroup &BR, pros::Gps &gps);

    bool translate_to(double x, double y);

    bool translate_by(double x, double y);

    bool rotate_to(double angle);

    bool rotate_by(double angle);

    bool drive_to(double x, double y, int rot);

    bool drive_by(double x, double y, int rot);

    double get_x();

    double get_y();

    double get_rot();
};
#endif // MOVEMENTMGR_H
