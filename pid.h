#include "defines.h"

lemlib::Drivetrain drivetrain(&leftDrivetrain, //left motorgroup
    &rightDrivetrain, //right motorgroup
    10.25, //track width
    lemlib::Omniwheel::NEW_275, //wheel size
    600, //drivetrain rpm 
    2 //horizontal drift (for now)
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(14, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              12, // derivative gain (kD)
                                              3, // 3 anti windup
                                              1, // 1 small error range, in inches
                                              100, // 100 small error range timeout, in milliseconds
                                              3, // 3 large error range, in inches
                                              500, // 500 large error range timeout, in milliseconds
                                              100 // 20 maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(4, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              26.5, // derivative gain (kD)
                                              3, // 3 anti windup
                                              1, // 1 small error range, in degrees
                                              100, // 100 small error range timeout, in milliseconds
                                              3, // 3 large error range, in degrees
                                              500, // 500 large error range timeout, in milliseconds
                                              0 // 0 maximum acceleration (slew)
);

lemlib::TrackingWheel vertical(&verticalOdom, //vertical tracking wheel sensor
    lemlib::Omniwheel::NEW_2, //wheel size
    -0.4 //offset
);

lemlib::TrackingWheel horizontal(&horizontalOdom, //horizontal tracking wheel sensor
    lemlib::Omniwheel::NEW_2, //wheel size
    -0.4 //offset
);

lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

//create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
    lateral_controller, // lateral PID settings
    angular_controller, // angular PID settings
    sensors// odometry sensors
);

//Testing move pid
void tuneMovePID() {
    // set position to x:0, y:0, heading:0
   chassis.setPose(0, 0, 0);
   // move 48" forwards
   chassis.moveToPoint(0, 48, 10000);
}

//Testing turn pid
void tuneTurnPID() {
   // set position to x:0, y:0, heading:0
   chassis.setPose(0, 0, 0);
   // turn to face heading 90 with a very long timeout
   chassis.turnToHeading(90, 1000000);
}