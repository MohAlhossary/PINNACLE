#include "libcreccompsci/brain/Cortex.h"

Cortex::Cortex(): midbrain(FL, FR, BL, BR, DR4B, claw_rot, claw, gps) {

}

void Cortex::tick(pros::Controller controller) {
    double x = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    double y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rot = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    midbrain.drive_by(x, y, rot);
}
