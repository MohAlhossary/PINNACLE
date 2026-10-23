#include "libcreccompsci/peripherals/movement/MovementMgr.h"

MovementMgr::MovementMgr(pros::MotorGroup &FL, pros::MotorGroup &FR, pros::MotorGroup &BL, pros::MotorGroup &BR,
    pros::Gps &gps): gps(gps), drivetrain(FL, FR, BL, BR) {

}

bool MovementMgr::translate_to(double x, double y) {
    return drivetrain.translate_to(x, y);
}

bool MovementMgr::translate_by(double x, double y) {
    return drivetrain.translate_by(x, y);
}

bool MovementMgr::rotate_to(double angle) {
    return drivetrain.rotate_to(angle);
}

bool MovementMgr::rotate_by(double angle) {
    return drivetrain.rotate_by(angle);
}

bool MovementMgr::drive_to(double x, double y, int rot) {
    return drivetrain.drive_to(x, y, rot);
}

bool MovementMgr::drive_by(double x, double y, int rot) {
    return drivetrain.drive_by(x, y, rot);
}

double MovementMgr::get_x() {
    x = drivetrain.get_x();
    return x;
}

double MovementMgr::get_y() {
    y = drivetrain.get_y();
    return y;
}

double MovementMgr::get_rot() {
    rot = drivetrain.get_rot();
    return rot;
}
