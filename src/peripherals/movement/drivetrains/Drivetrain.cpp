#include "libcreccompsci/peripherals/movement/drivetrains/Drivetrain.h"

void Drivetrain::stop() {
    set_power(0.0, 0.0, 0.0);
}
