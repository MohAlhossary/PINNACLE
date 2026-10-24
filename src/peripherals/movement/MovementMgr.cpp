#include "libcreccompsci/peripherals/movement/MovementMgr.h"

MovementMgr::MovementMgr(pros::MotorGroup &FL, pros::MotorGroup &FR, pros::MotorGroup &BL, pros::MotorGroup &BR,
    pros::Gps &gps): gps(gps), drivetrain(FL, FR, BL, BR), drivetrain_mgr(drivetrain), odo_mgr(gps) {
    start_thread();
}

MovementMgr::~MovementMgr() {
    stop_thread();
}

void MovementMgr::set_manual_mode(bool manual) {
    drivetrain_mgr.set_manual_mode(manual);
}

void MovementMgr::drive_manual(double x, double y, double rot) {
    drivetrain_mgr.drive_manual(x, y, rot);
}

bool MovementMgr::translate_to(double x, double y) {
    return drivetrain_mgr.translate_to(x, y);
}

bool MovementMgr::translate_by(double x, double y) {
    return drivetrain_mgr.translate_by(x, y);
}

bool MovementMgr::rotate_to(int rot) {
    return drivetrain_mgr.rotate_to(rot);
}

bool MovementMgr::rotate_by(int rot) {
    return drivetrain_mgr.rotate_by(rot);
}

bool MovementMgr::drive_to(double x, double y, int rot) {
    return drivetrain_mgr.drive_to(x, y, rot);
}

bool MovementMgr::drive_by(double x, double y, int rot) {
    return drivetrain_mgr.drive_by(x, y, rot);
}

double MovementMgr::get_x() {
    return x;
}

double MovementMgr::get_y() {
    return y;
}

int MovementMgr::get_rot() {
    return rot;
}

void MovementMgr::current_x_changed(double new_x) {
    x = new_x;
}

void MovementMgr::current_y_changed(double new_y) {
    y = new_y;
}

void MovementMgr::current_rot_changed(int new_rot) {
    rot = new_rot;
}

void MovementMgr::current_pose_changed(double new_x, double new_y, int new_rot) {
    x = new_x;
    y = new_y;
    rot = new_rot;
}

void MovementMgr::start_thread() {
    odo_update_task_running = true;
    odo_update_task.emplace([this] {
        while (odo_update_task_running) {
            update_pose_from_odo();
            pros::delay(20);
        }
    });

}

void MovementMgr::stop_thread() {
    odo_update_task_running = false;
}

void MovementMgr::update_pose_from_odo() {
    std::tuple<double, double, int> pose = odo_mgr.get_pose();
    x = std::get<0>(pose);
    y = std::get<1>(pose);
    rot = std::get<2>(pose);

    drivetrain_mgr.set_current_pose(x, y, rot);
}
