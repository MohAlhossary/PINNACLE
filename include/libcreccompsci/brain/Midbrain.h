#ifndef MIDBRAIN_H
#define MIDBRAIN_H

#include "api.h"
#include "libcreccompsci/peripherals/movement/MovementMgr.h"
#include "libcreccompsci/peripherals/scoring/ScoringMgr.h"

class Midbrain {
    MovementMgr movement_mgr;
    ScoringMgr scoring_mgr;

public:
    Midbrain(pros::MotorGroup &FL, pros::MotorGroup &FR, pros::MotorGroup &BL, pros::MotorGroup &BR,
             pros::MotorGroup &DR4B, pros::MotorGroup &claw_rot, pros::MotorGroup &claw,
             pros::Gps &gps);

    void set_manual_mode(bool manual);

    void drive_manual(double x, double y, double rot);

    bool drive_to(double x, double y, int rot);

    bool drive_by(double x, double y, int rot);

    bool drive_by(double x, double y, double rot);

    bool turn_to(int rot);

    bool turn_by(int rot);

    bool score();

    bool flip();

    bool elevate(int level);

    double get_x();

    double get_y();

    int get_elevation();
};
#endif // MIDBRAIN_H
