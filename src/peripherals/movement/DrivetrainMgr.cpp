#include "libcreccompsci/peripherals/movement/DrivetrainMgr.h"

DrivetrainMgr::DrivetrainMgr(Drivetrain &drivetrain) : drivetrain(drivetrain) {
    start_thread();
}

DrivetrainMgr::~DrivetrainMgr() {
    stop_thread();
}

void DrivetrainMgr::set_manual_mode(bool manual) {
    manual_mode = manual;
    drivetrain.stop();
}

void DrivetrainMgr::drive_manual(double x, double y, double rot) {
    if (manual_mode) {
        drivetrain.set_power(y, x, rot);
    }
}

bool DrivetrainMgr::translate_to(double x, double y) {
    target_x.store(x);
    target_y.store(y);
    return true;
}

bool DrivetrainMgr::translate_by(double x, double y) {
    target_x.store(target_x.load() + x);
    target_y.store(target_y.load() + y);
    return true;
}

bool DrivetrainMgr::rotate_to(int rot) {
    target_rot.store(rot);
    return true;
}

bool DrivetrainMgr::rotate_by(int rot) {
    int new_rot = (target_rot.load() + rot) % 360;
    target_rot.store(new_rot);
    return true;
}

bool DrivetrainMgr::drive_to(double x, double y, int rot) {
    translate_to(x, y);
    rotate_to(rot);
    return true;
}

bool DrivetrainMgr::drive_by(double x, double y, int rot) {
    translate_by(x, y);
    rotate_by(rot);
    return true;
}

void DrivetrainMgr::set_current_pose(double x, double y, int rot) {
    current_x.store(x);
    current_y.store(y);
    current_rot.store(rot);
}

void DrivetrainMgr::start_thread() {
    move_task_running = true;
    move_task.emplace([this] {
        while (move_task_running) {
            if (!manual_mode) {
                move_to_target_async();
            }
            pros::delay(20);
        }
    });
}

void DrivetrainMgr::stop_thread() {
    move_task_running = false;
}

void DrivetrainMgr::move_to_target_async() {
    //TODO rotate the field-frame error into the robot frame, wrap the heading error, and use a PID controller

    double delta_x = target_x.load() - current_x.load();
    double delta_y = target_y.load() - current_y.load();
    int delta_rot = target_rot.load() - current_rot.load();

    drivetrain.set_power(delta_y, delta_x, delta_rot);
}
