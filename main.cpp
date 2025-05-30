#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

// initialize function. Runs on program startup
void initialize() {
    pros::lcd::initialize(); // initialize brain screen

    chassis.calibrate(); // calibrate sensors

    Task ladyBrown(ladyBrownControl);

    // Task color_sort_task(colorSortTask, "ColorSortTask");
    
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
			// // print measurements from the adi encoder
			// pros::lcd::print(0, "ADI Encoder: %i", adi_encoder.get_value());
			// // print measurements from the rotation sensor
			// pros::delay(10); // delay to save resources. DO NOT REMOVE

            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            pros::lcd::print(3, "Rotation Sensor: %i", ladybrownRotation.get_position()/100);
            pros::lcd::print(4, "Color Sensor: %.2f", opticalSensor.get_hue());

            // delay to save resources
            pros::delay(20);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    //rightSideAuto();
    //leftSideAuto();
    //tuneMovePID();
    //tuneTurnPID();
    redRightSide();
    //blueRightSide();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

float linearSpeed = 0, turnSpeed = 0;
float leftDriveSpeed = 0, rightDriveSpeed = 0;
bool lastClampButtonState = false;
bool isPistonExtended = false;
bool lastIntakeTiltButtonState = false;
bool isIntakeTilt = false;
bool doinkerButton = false;
bool doinkerButtonPrev = false;
bool doinkerState = false;
bool lastDoinkerButtonState = false;
bool isDoinkerPistonExtended = false; 
bool doinkerClampButton = false;
bool doinkerClampButtonPrev = false;
bool doinkerClampState = false;
bool lastDoinkerClampButtonState = false;
bool isDoinkerClampPistonExtended = false;

//Split Arcade
void opcontrol(void) {

    // loop forever
    while (true) {
        //Driver Control
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        if (abs(rightX) > rightY || abs(leftY) > rightY) {
            linearSpeed = leftY; turnSpeed = rightX; //turnSpeed*=0.90;

            leftDriveSpeed = linearSpeed + turnSpeed;
            rightDriveSpeed = linearSpeed - turnSpeed;

            leftDrivetrain.move(leftDriveSpeed); rightDrivetrain.move(rightDriveSpeed);
        } else {
            leftDrivetrain.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            rightDrivetrain.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            leftDrivetrain.brake(); 
            rightDrivetrain.brake();
        }

        //Intake User Control
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            intaveyor.move_velocity(600);
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intaveyor.move_velocity(-600);
        } else if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && !controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intaveyor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            intaveyor.move_velocity(0);
        }

        //Backclamp Control
        bool currentClampButtonState = controller.get_digital(E_CONTROLLER_DIGITAL_R1);
        if (currentClampButtonState && !lastClampButtonState) {
            isPistonExtended = !isPistonExtended;

            backClamp.set_value(isPistonExtended);
        }
        
        lastClampButtonState = currentClampButtonState;

        //Intaketilt control
        bool currentIntakeTiltButtonState = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
        if (currentIntakeTiltButtonState && !lastIntakeTiltButtonState) {
            isIntakeTilt = !isIntakeTilt;

            intakeTilt.set_value(isIntakeTilt); 
        }

        lastIntakeTiltButtonState = currentIntakeTiltButtonState;

        //Doinker Function
        bool doinkerButtonState = controller.get_digital(E_CONTROLLER_DIGITAL_DOWN);
        bool doinkerClampButtonState = controller.get_digital(E_CONTROLLER_DIGITAL_RIGHT);
        if (doinkerButtonState && !lastDoinkerButtonState) {
            isDoinkerPistonExtended = !isDoinkerPistonExtended;

            doinker.set_value(isDoinkerPistonExtended);
        }

        lastDoinkerButtonState = doinkerButtonState;

        //Doinker Clamp Function
        if (doinkerClampButtonState && !lastDoinkerClampButtonState && isDoinkerPistonExtended) {
            isDoinkerClampPistonExtended = !isDoinkerClampPistonExtended;

            goalRushClamp.set_value(isDoinkerClampPistonExtended);
        }

        lastDoinkerClampButtonState = doinkerClampButtonState;
        delay(20);
    }
}