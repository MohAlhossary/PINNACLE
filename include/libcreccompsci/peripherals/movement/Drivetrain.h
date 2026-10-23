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

    pros::MotorGroup& FL;
    pros::MotorGroup& FR;
    pros::MotorGroup& BL;
    pros::MotorGroup& BR;

    std::optional<pros::Task> move_task;
    std::atomic<bool> move_thread_running{false};

    public:
        Drivetrain(pros::MotorGroup& FL, pros::MotorGroup& FR, pros::MotorGroup& BL, pros::MotorGroup& BR): FL(FL), FR(FR), BL(BL), BR(BR) {
            start_thread();
        }

        ~Drivetrain() {
            stop_thread();
        }

        bool translate_to(double x, double y) {
            target_x.store(x);
            target_y.store(y);
            return true;
        }

        bool translate_by(double x, double y) {
            target_x.store(target_x.load() + x);
            target_y.store(target_y.load() + y);
            return true;
        }

        bool rotate_to(int rot) {
            target_rot.store(rot);
            return true;
        }

        bool rotate_by(int rot) {
            int new_rot = (target_rot.load() + rot) % 360;
            target_rot.store(new_rot);
            return true;
        }

        bool drive_to(double x, double y, int rot) {
            translate_to(x, y);
            rotate_to(rot);
            return true;
        }

        bool drive_by(double x, double y, int rot) {
            translate_by(x, y);
            rotate_by(rot);
            return true;
        }

        double get_x() {
            return current_x;
        }

        double get_y() {
            return current_y;
        }

        double get_rot() {
            return current_rot;
        }

        private:
            void stop_thread() {
                move_thread_running = false;
            }

            void start_thread() {
                move_thread_running = true;
                move_task.emplace([this] {
                    while (move_thread_running) {
                        move_to_target();
                        pros::delay(20);
                    }
                });
            }

            void move_to_target() {

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
};
#endif