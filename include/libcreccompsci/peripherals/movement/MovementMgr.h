#ifndef MOVEMENTMGR_H
#define MOVEMENTMGR_H

#include "api.h"
#include "OdoMgr.h"
#include "DrivetrainMgr.h"
#include "drivetrains/XDrive.h"

class MovementMgr {
    std::atomic<double> x{0.0};
    std::atomic<double> y{0.0};
    std::atomic<int> rot{0};

    pros::Gps gps;

    // drivetrain must be declared before drivetrain_mgr, which holds a reference to it
    XDrive drivetrain;
    DrivetrainMgr drivetrain_mgr;
    OdoMgr odo_mgr;

    std::optional<pros::Task> odo_update_task;
    std::atomic<bool> odo_update_task_running;

public:
    MovementMgr(pros::MotorGroup &FL, pros::MotorGroup &FR, pros::MotorGroup &BL, pros::MotorGroup &BR, pros::Gps &gps);

    ~MovementMgr();

    void set_manual_mode(bool manual);

    void drive_manual(double x, double y, double rot);

    bool translate_to(double x, double y);

    bool translate_by(double x, double y);

    bool rotate_to(int rot);

    bool rotate_by(int rot);

    bool drive_to(double x, double y, int rot);

    bool drive_by(double x, double y, int rot);

    double get_x();

    double get_y();

    int get_rot();

    friend class OdoMgr;

private:
    void current_x_changed(double new_x);

    void current_y_changed(double new_y);

    void current_rot_changed(int new_rot);

    void current_pose_changed(double new_x, double new_y, int new_rot);

    void update_pose_from_odo();

    void start_thread();

    void stop_thread();
};
#endif // MOVEMENTMGR_H
