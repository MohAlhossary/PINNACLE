#ifndef ODO_MGR_H
#define ODO_MGR_H

#include "api.h"
#include <atomic>
#include <optional>
#include <tuple>


class OdoMgr {
    pros::Gps &gps;

    /**
     * Last good GPS pose, in inches and degrees. Written by gps_update_task, read by MovementMgr's task
     */
    std::atomic<double> gps_x{0.0};
    std::atomic<double> gps_y{0.0};
    std::atomic<int> gps_rot{0};

    //TODO Use an odometry deadwheel and an AI vision sensor in a monte-carlo simulation to improve accuracy

    std::optional<pros::Task> gps_update_task;
    std::atomic<bool> gps_update_task_running{false};

    static constexpr double METERS_TO_INCHES = 39.3701;

public:
    explicit OdoMgr(pros::Gps &gps);

    ~OdoMgr();

    double get_x();
    double get_y();
    int get_rot();
    std::tuple<double, double, int> get_pose();

    void update_pose_from_gps();

private:
    void start_thread();

    void stop_thread();
};
#endif // ODO_MGR_H
