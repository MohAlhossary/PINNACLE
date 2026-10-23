#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <optional>
#include <atomic>
#include <cmath>
#include "api.h"


class Drivetrain {
    /**
     * Real Drivetrain Coordinates; Blue side is +x, and red side is -x, in inches
     */
    double current_x = 0.0;
    double current_y = 0.0;
    /**
     * Real Drivetrain Heading, in degrees
     */
    int current_rot;

    /**
     * Target Drivetrain Coordinates; Blue side is +x, and red side is -x, in inches
     */
    std::atomic<double> target_x{0.0};
    std::atomic<double> target_y{0.0};
    /**
     * Target Drivetrain Heading, in degrees (Made atomic for thread safety)
     */
    std::atomic<int> target_rot{0};

    pros::MotorGroup &FL;
    pros::MotorGroup &FR;
    pros::MotorGroup &BL;
    pros::MotorGroup &BR;

    std::optional<pros::Task> move_task;
    std::atomic<bool> move_thread_running{false};

public:
    Drivetrain(pros::MotorGroup &FL, pros::MotorGroup &FR, pros::MotorGroup &BL, pros::MotorGroup &BR);

    ~Drivetrain();

    bool translate_to(double x, double y);

    bool translate_by(double x, double y);

    bool rotate_to(int rot);

    bool rotate_by(int rot);

    bool drive_to(double x, double y, int rot);

    bool drive_by(double x, double y, int rot);

    double get_x();

    double get_y();

    double get_rot();

private:
    void stop_thread();

    void start_thread();

    void move_to_target();
};
#endif
