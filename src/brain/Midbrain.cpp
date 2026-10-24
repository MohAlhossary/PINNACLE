#include "libcreccompsci/brain/Midbrain.h"

Midbrain::Midbrain(pros::MotorGroup &FL, pros::MotorGroup &FR, pros::MotorGroup &BL, pros::MotorGroup &BR,
                   pros::MotorGroup &DR4B, pros::MotorGroup &claw_rot, pros::MotorGroup &claw,
                   pros::Gps &gps) : scoring_mgr(DR4B, claw_rot, claw), movement_mgr(FL, FR, BL, BR, gps) {
}

void Midbrain::set_manual_mode(bool manual) {
    movement_mgr.set_manual_mode(manual);
}

void Midbrain::drive_manual(double x, double y, double rot) {
    movement_mgr.drive_manual(x, y, rot);
}

bool Midbrain::drive_to(double x, double y, int rot) {
    return movement_mgr.drive_to(x, y, rot);
}

bool Midbrain::drive_by(double x, double y, int rot) {
    return movement_mgr.drive_by(x, y, rot);
}

bool Midbrain::drive_by(double x, double y, double rot) {
    return movement_mgr.drive_by(x, y, rot * 360);
}

bool Midbrain::turn_to(int rot) {
    return movement_mgr.rotate_to(rot);
}

bool Midbrain::turn_by(int rot) {
    return movement_mgr.rotate_by(rot);
}

bool Midbrain::score() {
    return scoring_mgr.score();
}

bool Midbrain::flip() {
    return scoring_mgr.flip();
}

bool Midbrain::elevate(int level) {
    return scoring_mgr.elevate(level);
}

double Midbrain::get_x() {
    return movement_mgr.get_x();
}

double Midbrain::get_y() {
    return movement_mgr.get_y();
}

int Midbrain::get_elevation() {
    return scoring_mgr.get_elevation();
}
