//
// Created by moham on 10/24/2026.
//

#ifndef VEX_DRIVETRAINMGR_H
#define VEX_DRIVETRAINMGR_H

#include "api.h"
#include <atomic>
#include <optional>
#include "drivetrains/Drivetrain.h"


/**
 * Decides what the drivetrain should do.
 * In manual mode the driver's stick goes straight to the drivetrain; otherwise a background task
 * drives toward the target pose using the current pose fed in from odometry.
 */
class DrivetrainMgr {
    Drivetrain &drivetrain;

    std::atomic<bool> manual_mode{true};

    /**
     * Real Drivetrain Coordinates; Blue side is +x, and red side is -x, in inches
     */
    std::atomic<double> current_x{0.0};
    std::atomic<double> current_y{0.0};
    /**
     * Real Drivetrain Heading, in degrees
     */
    std::atomic<int> current_rot{0};

    /**
     * Target Drivetrain Coordinates; Blue side is +x, and red side is -x, in inches
     */
    std::atomic<double> target_x{0.0};
    std::atomic<double> target_y{0.0};
    /**
     * Target Drivetrain Heading, in degrees
     */
    std::atomic<int> target_rot{0};

    std::optional<pros::Task> move_task;
    std::atomic<bool> move_task_running{false};

public:
    explicit DrivetrainMgr(Drivetrain &drivetrain);

    ~DrivetrainMgr();

    void set_manual_mode(bool manual);

    /**
     * Driver control: robot-relative power, each in -1..1. Ignored outside manual mode.
     */
    void drive_manual(double x, double y, double rot);

    bool translate_to(double x, double y);

    bool translate_by(double x, double y);

    bool rotate_to(int rot);

    bool rotate_by(int rot);

    bool drive_to(double x, double y, int rot);

    bool drive_by(double x, double y, int rot);

    void set_current_pose(double x, double y, int rot);

private:
    void start_thread();

    void stop_thread();

    void move_to_target_async();
};


#endif //VEX_DRIVETRAINMGR_H
