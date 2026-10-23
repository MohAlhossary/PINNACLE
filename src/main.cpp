#include "main.h"
#include "libcreccompsci/brain/Cortex.h"

Cortex cortex = Cortex();

pros::Controller controller = pros::Controller(pros::E_CONTROLLER_MASTER);

void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
    while (true) {
        cortex.tick(controller);
    }
}