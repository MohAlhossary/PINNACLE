#ifndef VEX_DRIVETRAIN_H
#define VEX_DRIVETRAIN_H

/**
 * Hardware-only interface for a drivetrain: turns a robot-relative power request into motor commands.
 * It knows nothing about targets, pose or tasks; DrivetrainMgr handles those.
 */
class Drivetrain {
public:
    virtual ~Drivetrain() = default;

    /**
     * Drive with robot-relative power, each in -1..1
     * @param y forward, + is forward
     * @param x strafe, + is right
     * @param rot turn, + is clockwise
     */
    virtual void set_power(double y, double x, double rot) = 0;

    void stop();
};


#endif //VEX_DRIVETRAIN_H
