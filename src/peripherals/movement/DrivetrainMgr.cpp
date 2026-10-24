#include "libcreccompsci/peripherals/movement/DrivetrainMgr.h"

#include <cmath>
#include <numbers>

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
    target_rot.store(normalize_heading(rot));
    return true;
}

bool DrivetrainMgr::rotate_by(int rot) {
    target_rot.store(normalize_heading(target_rot.load() + rot));
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

int DrivetrainMgr::normalize_heading(int rot) {
    return ((rot % 360) + 360) % 360;
}

int DrivetrainMgr::wrap_heading_error(int error) {
    return ((error % 360) + 540) % 360 - 180;
}

void DrivetrainMgr::move_to_target_async() {
    //TODO replace the P gains with a PID controller
    int rot = current_rot.load();

    double delta_x = target_x.load() - current_x.load();
    double delta_y = target_y.load() - current_y.load();
    int delta_rot = wrap_heading_error(target_rot.load() - rot);

    if (std::hypot(delta_x, delta_y) < POSITION_TOLERANCE && std::abs(delta_rot) < HEADING_TOLERANCE) {
        drivetrain.stop();
        return;
    }

    // Field-frame error -> robot frame. Assumes heading 0 faces field +y and increases clockwise
    double heading = rot * std::numbers::pi / 180.0;
    double forward = delta_x * std::sin(heading) + delta_y * std::cos(heading);
    double strafe = delta_x * std::cos(heading) - delta_y * std::sin(heading);

    drivetrain.set_power(KP_LINEAR * forward, KP_LINEAR * strafe, KP_TURN * delta_rot);
}
