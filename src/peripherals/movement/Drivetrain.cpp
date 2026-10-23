#include "libcreccompsci/peripherals/movement/Drivetrain.h"

Drivetrain::Drivetrain(pros::MotorGroup &FL, pros::MotorGroup &FR, pros::MotorGroup &BL,
                       pros::MotorGroup &BR) : FL(FL), FR(FR), BL(BL), BR(BR) {
    start_thread();
}

Drivetrain::~Drivetrain() {
    stop_thread();
}

bool Drivetrain::translate_to(double x, double y) {
    target_x.store(x);
    target_y.store(y);
    return true;
}

bool Drivetrain::translate_by(double x, double y) {
    target_x.store(target_x.load() + x);
    target_y.store(target_y.load() + y);
    return true;
}

bool Drivetrain::rotate_to(int rot) {
    target_rot.store(rot);
    return true;
}

bool Drivetrain::rotate_by(int rot) {
    int new_rot = (target_rot.load() + rot) % 360;
    target_rot.store(new_rot);
    return true;
}

bool Drivetrain::drive_to(double x, double y, int rot) {
    translate_to(x, y);
    rotate_to(rot);
    return true;
}

bool Drivetrain::drive_by(double x, double y, int rot) {
    translate_by(x, y);
    rotate_by(rot);
    return true;
}

double Drivetrain::get_x() {
    return current_x;
}

double Drivetrain::get_y() {
    return current_y;
}

double Drivetrain::get_rot() {
    return current_rot;
}

void Drivetrain::stop_thread() {
    move_thread_running = false;
}

void Drivetrain::start_thread() {
    move_thread_running = true;
    move_task.emplace([this] {
        while (move_thread_running) {
            move_to_target();
            pros::delay(20);
        }
    });
}

void Drivetrain::move_to_target() {
    double tx = target_x.load();
    double ty = target_y.load();
    int trot = target_rot.load();

    double delta_x = tx - current_x;
    double delta_y = ty - current_y;
    double delta_rot = trot - current_rot;

    double fl_power = delta_x + delta_y + delta_rot;
    double fr_power = delta_x - delta_y - delta_rot;
    double bl_power = delta_x - delta_y + delta_rot;
    double br_power = delta_x + delta_y - delta_rot;

    FL.move(fl_power);
    FR.move(fr_power);
    BL.move(bl_power);
    BR.move(br_power);
}
