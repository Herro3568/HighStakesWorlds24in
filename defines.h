#include "lemlib/api.hpp"

//For c++, use .hpp files

using namespace pros;

// ********** Drivetrain Delcarations ********** //
//Declaring controller
Controller controller(E_CONTROLLER_MASTER);

//Declaring motors on left side of drivetrain
Motor leftFrontBottom(17,MotorGears::rpm_600);//Robust17 Adam18 
Motor leftFrontTop(18,MotorGears::rpm_600);//Robust18 Adam19
Motor leftBackBottom(20,MotorGears::rpm_600);//Robust20 Adam16
Motor leftBackTop(-19,MotorGears::rpm_600);//Robust-19 Adam-20

//Create a motorgroup for left side drivetrain
MotorGroup leftDrivetrain({17,18,20,-19}); 

//Declaring motors on right side of drivetrain
Motor rightFrontBottom(-7,MotorGears::rpm_600);//Robust-7 Adam-7
Motor rightFrontTop(-6,MotorGears::rpm_600);//Robust-6 Adam-6
Motor rightBackBottom(-10,MotorGears::rpm_600);//Robust-10 Adam-8
Motor rightBackTop(9,MotorGears::rpm_600);//Robust9 Adam9

//Create a motorgroup for right side drivetrain
MotorGroup rightDrivetrain({-7,-6,-10,9});

//Create a motorgroup for entire drivetrain
MotorGroup wholeDrivetrain({17,18,20,-19,-7,-6,-10,9});



// ********** Subsystems Delcarations ********** //
//Declaring intake motor
Motor intake(1,MotorGears::rpm_600); //Robust1 Adam-21

//Declaring conveyor motors
Motor leftConveyor(-3,MotorGears::rpm_600); //Robust-3 Adam5
Motor rightConveyor(2,MotorGears::rpm_600); //Robust2 Adam-3

//Create a motorgroup for conveyor 
MotorGroup conveyor({-3,2});

//Create a motorgroup for intake and conveyor together
MotorGroup intaveyor({1,-3,2});

//Declaring ladybrown motors
Motor leftLadybrown(4,MotorGears::rpm_100); //Robust5 Adam12
Motor rightLadybrown(-5,MotorGears::rpm_100); //Robust-4 Adam-11

//Create a motorgroup for ladybrown
MotorGroup ladybrown({4,-5});



// *********** Sensors Delcarations *********** //
//Declaring inertial sensor
Imu imu(11); //Robust11 Adam11

//Declaring rotation sensors
Rotation ladybrownRotation(6); //Robust6 Adam13
Rotation horizontalOdom(19);
Rotation verticalOdom(18);

//Delcaring color sensor
Optical opticalSensor(12);
// Optional: Configure the optical sensor
//optical_sensor.set_led_pwm(100); // Set LED brightness (0-100)

//Declaring distance sensors
Distance distanceSensor(21);
// Distance clampDistance(15);



// ********** Pneumatics Delcarations ********** //
//Delcaring pneumatics
#define DIGITAL_SENSOR_PORTB 'B'
pros::ADIDigitalOut backClamp(DIGITAL_SENSOR_PORTB);
#define DIGITAL_SENSOR_PORTD 'D'
pros::ADIDigitalOut doinker(DIGITAL_SENSOR_PORTD);
#define DIGITAL_SENSOR_PORTC 'C'
pros::ADIDigitalOut goalRushClamp(DIGITAL_SENSOR_PORTC);
#define DIGITAL_SENSOR_PORTA 'A'
pros::ADIDigitalOut intakeTilt(DIGITAL_SENSOR_PORTA);

