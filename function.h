#include "pid.h"

// ************* Ladybrown Control ************* //
//Constants
const int targetAngle = 67; //Robust246 Adam115
const int tolerance = 2;

//PD constants
//kP=2.5, kD=0.1 works well 
double kP = 2.5;
double kD = 0.1;
int toggleSpeed = 75;

//Global variables
bool isLadybrownUp = false;
bool r2PressedPrev = false;
int lastError = 0;
bool bPressedPrev = false;
bool yPressedPrev = false;
bool manualModeActive = false;

void ladyBrownControl() {
    // Move down for 1 second to reach the physical stopper
    controller.set_text(1,0,"Moving Down");
    ladybrown.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    ladybrown.move_velocity(-50);  // Move downward slowly
    delay(1000);  // Move for 1 second
    
    // Stop the motor
    ladybrown.move_velocity(0);
    delay(100);  // Short delay for stability
    
    // Now reset the rotation sensor at this position
    ladybrownRotation.reset();
    
    //Sets the brake type to brake
    ladybrown.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    controller.set_text(1,0,"Arm: Down");

    //For timing derivative term
    uint32_t lastTime = millis();
    
    // Variables for PD control
    int error = 0;
    double derivative = 0;
    int motorPower = 0;

    // Track manual mode
    bool manualModeActive = false;
    bool bPressedPrev = false;
    bool yPressedPrev = false;

    while (true) {
        uint32_t currentTime = millis();
        double deltaTime = (currentTime - lastTime) / 1000;
        lastTime = currentTime;

        //Read current ladybrown position from rotation sensor
        int currentAngle = ladybrownRotation.get_position() / 100;

        //R2 button toggle detection
        bool r2Pressed = controller.get_digital(E_CONTROLLER_DIGITAL_R2);
        
        //B button detection for manual forward
        bool bPressed = controller.get_digital(E_CONTROLLER_DIGITAL_B);
        
        //Y button detection for reset
        bool yPressed = controller.get_digital(E_CONTROLLER_DIGITAL_Y);

        // Check for Y button press for manual backward movement
        if (yPressed) {
            // Direct motor control - move backward
            ladybrown.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            ladybrown.move_velocity(-75);  // Move down at moderate speed
            
            // Activate manual mode if R2 is off
            if (!isLadybrownUp) {
                manualModeActive = true;
            }
            
            controller.set_text(2,0,"Manual Back");
        }

        // Check for R2 button press to toggle
        if (r2Pressed && !r2PressedPrev) {
            // Toggle ladybrown state
            isLadybrownUp = !isLadybrownUp;
            
            // Exit manual mode when toggling
            manualModeActive = false;

            if (isLadybrownUp) {
                controller.set_text(1,0,"Arm: Up");
            } else {
                // When toggling down, use one-time movement to physical stop
                controller.set_text(1,0,"Arm: Down");
                controller.set_text(2,0,"Moving Down");
                
                // Move down at moderate speed
                ladybrown.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
                ladybrown.move_velocity(-50);
                delay(1000);  // Move for 1 second
                
                // Stop and hold position
                ladybrown.set_brake_mode(E_MOTOR_BRAKE_HOLD);
                ladybrown.move_velocity(0);
                
                // Reset the rotation sensor
                ladybrownRotation.reset();
                
                // Reset control variables
                lastError = 0;
                derivative = 0;
            }
        }
        
        // Check for B button release while R2 is on
        if (bPressedPrev && !bPressed && isLadybrownUp) {
            // B was just released while R2 is on
            // Reset PD terms to ensure clean start of PD control
            lastError = 0;
            derivative = 0;
        }
        
        //Update button states for next loop
        r2PressedPrev = r2Pressed;
        bPressedPrev = bPressed;
        yPressedPrev = yPressed;

        // Handle B button (manual forward) and Y button (manual backward)
        if (bPressed) {
            // Direct motor control - move forward
            ladybrown.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
            ladybrown.move_velocity(100);
            
            // If R2 is off, activate manual mode
            if (!isLadybrownUp) {
                manualModeActive = true;
            }
            
            controller.set_text(2,0,"Manual Fwd");
        }
        else if (yPressed) {
            // Already handled above - this is just to make the else if logic clearer
        }
        else if (!isLadybrownUp && manualModeActive) {
            // B and Y are released, R2 is off, and we're in manual mode
            // Just hold position with brake - no PD
            ladybrown.set_brake_mode(E_MOTOR_BRAKE_HOLD);
            ladybrown.move_velocity(0);
            controller.set_text(2,0,"Man Hold");
        }
        else if (!isLadybrownUp && !manualModeActive) {
            // Arm is down and not in manual mode
            // Avoid PD control entirely at the down position
            // Just hold position with brake
            ladybrown.set_brake_mode(E_MOTOR_BRAKE_HOLD);
            ladybrown.move_velocity(0);
            controller.set_text(2,0,"Down Hold");
        }
        else {
            // Only use PD control for the up position
            // Calculate error
            error = targetAngle - currentAngle;
            
            // Calculate derivative of error
            if (deltaTime > 0) {
                derivative = (error - lastError) / deltaTime;
            }
            lastError = error;
            
            // Calculate PD control output
            double controlOutput = (kP * error) + (kD * derivative);

            // Limit output to maximum power
            motorPower = std::min(toggleSpeed, std::max(-toggleSpeed, (int)controlOutput));

            // Add deadband logic
            int deadband = 5;
            if (abs(motorPower) < deadband) {
                motorPower = 0;
            }

            // Apply control to motor unless we're within tolerance
            if (abs(error) <= tolerance && abs(derivative) < 5) {
                // Within tolerance - hold position
                ladybrown.set_brake_mode(E_MOTOR_BRAKE_HOLD);
                ladybrown.move_velocity(0);
                motorPower = 0;
                controller.set_text(2,0,"At Target");
            } else {
                // Apply PD control
                ladybrown.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
                ladybrown.move(motorPower);
                controller.set_text(2,0,"To Up Pos");
            }
        }

        // Display debug information on the LCD
        lcd::print(4, "Angle: %d degrees", currentAngle);
        lcd::print(5, "Error: %d D: %.2f", error, derivative);
        lcd::print(6, "R2:%s B:%s Y:%s M:%s", 
                   r2Pressed ? "ON" : "OFF", 
                   bPressed ? "ON" : "OFF",
                   yPressed ? "ON" : "OFF",
                   manualModeActive ? "ON" : "OFF");

        // Short delay to prevent CPU hogging
        delay(20);
    }
}



// Define color thresholds (you may need to adjust these based on your environment)
#define RED_HUE_MIN 10
#define RED_HUE_MAX 25
#define BLUE_HUE_MIN 200
#define BLUE_HUE_MAX 300


// Function to determine the ring color
std::string getRingColor() {
    double hue = opticalSensor.get_hue();  // Get the current hue value
    if (hue >= RED_HUE_MIN && hue <= RED_HUE_MAX) {
        return "RED";
    } else if (hue >= BLUE_HUE_MIN && hue <= BLUE_HUE_MAX) {
        return "BLUE";
    } else {
        return "NO RING";
    }
}

// Task to detect and sort blue rings
void blueColorSortTask() {
    opticalSensor.set_led_pwm(100); // Turn on LED for better color detection

    while (true) {
        std::string ringColor = getRingColor();  // Read current ring color

        if (ringColor == "RED" && conveyor.get_actual_velocity() != 0) {
            // Eject red ring
            delay(100);
            conveyor.move_velocity(0);
            delay(500);
            conveyor.move_velocity(600);

            // Delay to prevent repeated activation for the same ring
            delay(500);
        }

        delay(20);  // Small delay to prevent CPU overload
    }
}

void startColorSortTask() {
    Task colorSortTask(blueColorSortTask);
}