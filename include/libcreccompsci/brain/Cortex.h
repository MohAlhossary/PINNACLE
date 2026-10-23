#ifndef CORTEX_H
#define CORTEX_H

#include "Midbrain.h"

class Cortex {
    pros::MotorGroup FL = pros::MotorGroup({9}, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
    pros::MotorGroup FR = pros::MotorGroup({19}, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
    pros::MotorGroup BL = pros::MotorGroup({10}, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
    pros::MotorGroup BR = pros::MotorGroup({11}, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

    pros::MotorGroup DR4B = pros::MotorGroup({12, 2}, pros::v5::MotorGears::red, pros::v5::MotorUnits::degrees);
    pros::MotorGroup claw = pros::MotorGroup({13}, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
    pros::MotorGroup claw_rot = pros::MotorGroup({8}, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
    pros::Gps gps{1};

    Midbrain midbrain;

public:
    Cortex();

    void tick(pros::Controller controller);
};
#endif // CORTEX_H
