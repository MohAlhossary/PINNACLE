#include "libcreccompsci/peripherals/movement/OdoMgr.h"

OdoMgr::OdoMgr(pros::Gps &gps) : gps(gps) {
    gps.set_offset(5 / METERS_TO_INCHES,3.5 / METERS_TO_INCHES);
    start_thread();
}

OdoMgr::~OdoMgr() {
    stop_thread();
}

double OdoMgr::get_x() {
    return gps.get_position_x() * METERS_TO_INCHES;
}

double OdoMgr::get_y() {
    return gps.get_position_y() * METERS_TO_INCHES;
}


int OdoMgr::get_rot() {
    return static_cast<int>(gps.get_heading());
}

std::tuple<double, double, int> OdoMgr::get_pose() {
    //TODO Use an odometry deadwheel and an AI vision sensor in a monte-carlo simulation to improve accuracy
    return std::make_tuple(gps_x.load(), gps_y.load(), gps_rot.load());
}

void OdoMgr::update_pose_from_gps() {
    double raw_x = gps.get_position_x();
    double raw_y = gps.get_position_y();
    double raw_heading = gps.get_heading();

    // The GPS returns PROS_ERR_F when it is unplugged or can't see the field strip; keep the last good pose
    if (raw_x == PROS_ERR_F || raw_y == PROS_ERR_F || raw_heading == PROS_ERR_F) {
        return;
    }

    gps_x.store(raw_x * METERS_TO_INCHES);
    gps_y.store(raw_y * METERS_TO_INCHES);
    gps_rot.store(static_cast<int>(raw_heading));
}

void OdoMgr::start_thread() {
    gps_update_task_running = true;
    gps_update_task.emplace([this] {
        while (gps_update_task_running) {
            update_pose_from_gps();
            pros::delay(20);
        }
    });
}

void OdoMgr::stop_thread() {
    gps_update_task_running = false;
}
