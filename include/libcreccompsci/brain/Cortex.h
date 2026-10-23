#ifndef CORTEX_H
#define CORTEX_H

#include "Midbrain.h"

class Cortex {
    // 1. Declare hardware peripherals first so they are initialized before dependent managers
    pros::MotorGroup FL = pros::MotorGroup({9}, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
    pros::MotorGroup FR = pros::MotorGroup({19}, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
    pros::MotorGroup BL = pros::MotorGroup({10}, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
    pros::MotorGroup BR = pros::MotorGroup({11}, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

    pros::MotorGroup DR4B = pros::MotorGroup({12, 2}, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
    pros::MotorGroup claw = pros::MotorGroup({13}, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
    pros::MotorGroup claw_rot = pros::MotorGroup({8}, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
    pros::Gps gps{1};

    // 2. Declare managers that depend on initialized peripherals
    Midbrain midbrain;

public:
    Cortex() : midbrain(FL, FR, BL, BR, DR4B, claw_rot, claw, gps) {}

    void tick(pros::Controller controller) {

        double x = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        double y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rot = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        midbrain.drive_by(x, y, rot);

    }
};
#endif // CORTEX_H
