#pragma once

#include "Drivetrain.h"
#include "../include/api.h"

class MovementMgr {

    double x;
    double y;
    double rot;

    pros::Gps gps;

    Drivetrain drivetrain;
    // odomngr TODO finish this

    public:
        MovementMgr(pros::MotorGroup& FL, pros::MotorGroup& FR, pros::MotorGroup& BL, pros::MotorGroup& BR, pros::Gps& gps)
    : gps(gps), drivetrain(FL, FR, BL, BR) {

        }

        bool translate_to(double x, double y) {
            return drivetrain.translate_to(x, y);
        }

        bool translate_by(double x, double y) {
            return drivetrain.translate_by(x, y);
        }

        bool rotate_to(double angle) {
            return drivetrain.rotate_to(angle);
        }

        bool rotate_by(double angle) {
            return drivetrain.rotate_by(angle);
        }

        bool drive_to(double x, double y, int rot) {
            return drivetrain.drive_to(x, y, rot);
        }

        bool drive_by(double x, double y, int rot) {
            return drivetrain.drive_by(x, y, rot);
        }

        double get_x() {
            x = drivetrain.get_x();
            return x;
        }

        double get_y() {
            y = drivetrain.get_y();
            return y;
        }

        double get_rot() {
            rot = drivetrain.get_rot();
            return rot;
        }
};
