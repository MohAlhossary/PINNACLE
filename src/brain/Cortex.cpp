#include "libcreccompsci/brain/Cortex.h"

#include <complex>

Cortex::Cortex(): midbrain(FL, FR, BL, BR, DR4B, claw_rot, claw, gps) {
    midbrain.set_manual_mode(true);
}

void Cortex::tick(pros::Controller controller) {
    double x = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) / 127.0;
    double y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0;
    double rot = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0;

    if (std::abs(x) < DEADZONE) {
        x = 0;
    }
    if (std::abs(y) < DEADZONE) {
        y = 0;
    }
    if (std::abs(rot) < DEADZONE) {
        rot = 0;
    }

    midbrain.drive_by(x,y, rot);
    // midbrain.drive_manual(x, y, rot);
}
