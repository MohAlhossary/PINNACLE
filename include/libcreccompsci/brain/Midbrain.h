#ifndef MIDBRAIN_H
#define MIDBRAIN_H

#include "api.h"
#include "libcreccompsci/peripherals/movement/MovementMgr.h"
#include "libcreccompsci/peripherals/scoring/ScoringMgr.h"

class Midbrain {

    MovementMgr movement_mgr;
    ScoringMgr scoring_mgr;

public:
    Midbrain(pros::MotorGroup& FL, pros::MotorGroup& FR, pros::MotorGroup& BL, pros::MotorGroup& BR,
        pros::MotorGroup& DR4B, pros::MotorGroup& claw_rot, pros::MotorGroup& claw, pros::Gps gps): scoring_mgr(DR4B, claw_rot, claw), movement_mgr(FL, FR, BL, BR, gps) {
    }

    bool drive_to(double x, double y, int rot) {
        return movement_mgr.drive_to(x, y, rot);
    }

    bool drive_by(double x, double y, int rot) {
        return movement_mgr.drive_by(x, y, rot);
    }

    bool turn_to(double angle) {
        return movement_mgr.rotate_to(angle);
    }

    bool turn_by(double angle) {
        return movement_mgr.rotate_by(angle);
    }

    bool score() {
        return scoring_mgr.score();
    }

    bool flip() {
        return scoring_mgr.flip();
    }

    bool elevate(int level) {
        return scoring_mgr.elevate(level);
    }

    double get_x() {
        return movement_mgr.get_x();
    }

    double get_y() {
        return movement_mgr.get_y();
    }

    int get_elevation() {
        return scoring_mgr.get_elevation();
    }
};
#endif // MIDBRAIN_H
