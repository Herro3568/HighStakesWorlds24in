#include "function.h"

void redRightSide() {
    //Robot Starting Position
    chassis.setPose(23.5,-51,0);

    //Doinker down and goal rush the far right side goal
    doinker.set_value(true);
    chassis.moveToPoint(36,-24,15000,{.minSpeed=300});
    delay(1000);
    goalRushClamp.set_value(true);

    //Bring the goal back a bit
    chassis.moveToPoint(43,-34,15000,{.forwards=false,.minSpeed=200});
    chassis.waitUntilDone();
    delay(1800);
    goalRushClamp.set_value(false);

    //Back off to let loose the goal and move to safe goal
    doinker.set_value(false);
    chassis.turnToHeading(60,2000);
    chassis.moveToPoint(20,-55.5,3000,{.forwards=false,.maxSpeed=50,.earlyExitRange=5});
    chassis.waitUntilDone();

    //Back up slowly more to accurate pick up safe goal
    chassis.turnToHeading(90,2000);
    chassis.moveToPoint(-5,-55.5,2000,{.forwards=false,.maxSpeed=40});
    delay(800);
    backClamp.set_value(true);

    //Turn to grab red bottom stack
    delay(1000);
    startColorSortTask();
    intaveyor.move_velocity(600);
    chassis.moveToPoint(50,-55.5,2000);

    chassis.turnToHeading(165,2000);
    chassis.moveToPoint(62,-62,3000);
    delay(2000);
    
    //Turn to grab red bottom stack on the line
    // chassis.turnToHeading(18,2000);
    // chassis.moveToPoint(64,-25,3000,{.maxSpeed=60});

    //Back off to avoid goal
    // chassis.moveToPoint(55,-35,3000,{.forwards=false,.maxSpeed=75});
    // chassis.moveToPoint(62,-25,2000,{.maxSpeed=70});
    // chassis.moveToPoint(55,-35,3000,{.forwards=false,.maxSpeed=75});
    // chassis.turnToHeading(200,2000);

    //Move to corner to intake bottom ring
    // chassis.moveToPoint(47,-50,2000,{.earlyExitRange=5});
    // chassis.moveToPoint(63,-67,2000);
    // chassis.moveToPoint(62,-65,2000,{.forwards=false});
    // chassis.moveToPoint(64,-67,2000);

    //Back off and doinker down to clear corner
    //chassis.moveToPoint(60,-57,2000,{.forwards=false});
    chassis.moveToPoint(50,-50,2000,{.forwards=false});
    chassis.turnToHeading(325,2000);
    chassis.moveToPoint(62,-62,4000,{.forwards=false,.maxSpeed=50});
    delay(1000);
    chassis.moveToPoint(50,-50,2000);
    chassis.turnToHeading(270,2000);
    conveyor.move_velocity(0);

    chassis.moveToPoint(8,-50,3000,{.maxSpeed=127});
    chassis.waitUntilDone();
    backClamp.set_value(false);
    conveyor.move_velocity(0);
    chassis.turnToHeading(180,2000);
    chassis.moveToPoint(8,-60,3000,{.maxSpeed=50});
    delay(500);
    
    chassis.moveToPoint(8,-48,2000,{.forwards=false});
    chassis.turnToHeading(0,2000);
    chassis.moveToPoint(8,-62,3000,{.forwards=false,.maxSpeed=50});
    chassis.waitUntilDone();
    delay(500);
    intaveyor.move_velocity(600);
    chassis.moveToPoint(8,-28,2000,{.maxSpeed=50});
}



// void blueLeftSide() {
//     //Robot Starting Position
//     chassis.setPose(-23.5,-51,0);

//     //Doinker down and goal rush the far left side goal
//     doinker.set_value(true);
//     intake.move_velocity(600);
//     chassis.moveToPoint(-28,-25,2000,{.minSpeed=127,.earlyExitRange=5});
//     chassis.waitUntilDone();
//     delay(800);
//     goalRushClamp.set_value(true);
//     delay(250);

//     //Back off to let loose the goal
//     chassis.moveToPoint(-43,-34,2000,{.forwards=false});
//     delay(1000);
//     goalRushClamp.set_value(false);
//     chassis.moveToPoint(-43,-36,2000,{.forwards=false});
//     delay(500);
//     doinker.set_value(false);
//     chassis.turnToHeading(285,2000);
//     intake.move_velocity(-600);

//     //Move to grab the safe goal
//     chassis.moveToPoint(-24,-46,4000,{.forwards=false,.maxSpeed=75});
//     chassis.moveToPoint(-12,-46,3000,{.forwards=false,.maxSpeed=25});
//     delay(2000);
//     backClamp.set_value(true);
    
    
// }

void blueRightSide() {
    //Robot Starting Position
    chassis.setPose(23.5,-51,0);

    //Doinker down and goal rush the far right side goal
    doinker.set_value(true);
    chassis.moveToPoint(36,-22,2000,{.minSpeed=300,.earlyExitRange=5});
    delay(1000);
    goalRushClamp.set_value(true);

    //Bring the goal back a bit
    chassis.moveToPoint(43,-34,2000,{.forwards=false,.minSpeed=200});
    delay(1800);
    goalRushClamp.set_value(false);

    //Back off to let loose the goal and move to safe goal
    startColorSortTask();
    doinker.set_value(false);
    chassis.turnToHeading(60,2000);
    chassis.moveToPoint(20,-53,3000,{.forwards=false,.maxSpeed=70,.earlyExitRange=5});
    chassis.waitUntilDone();

    //Back up slowly more to accurate pick up safe goal
    chassis.turnToHeading(90,2000);
    chassis.moveToPoint(2,-53,2000,{.forwards=false,.maxSpeed=25});
    chassis.waitUntilDone();
    delay(700);
    backClamp.set_value(true);

    //Turn to grab red bottom stack
    intaveyor.move_velocity(600);
    chassis.moveToPoint(44,-50,2000);
    
    //Turn to grab red bottom stack on the line
    // chassis.turnToHeading(18,2000);
    // chassis.moveToPoint(64,-10,3000,{.maxSpeed=60});

    // //Back off to avoid goal
    // chassis.moveToPoint(55,-35,3000,{.forwards=false,.maxSpeed=75});
    // chassis.moveToPoint(62,-11,2000,{.maxSpeed=70});
    // chassis.moveToPoint(55,-35,3000,{.forwards=false,.maxSpeed=75});
    // chassis.turnToHeading(200,2000);

    //Move to corner to intake bottom ring
    chassis.moveToPoint(47,-50,2000,{.earlyExitRange=5});
    chassis.moveToPoint(63,-67,2000);
    chassis.moveToPoint(62,-65,2000,{.forwards=false});
    chassis.moveToPoint(64,-67,2000);

    //Back off and doinker down to clear corner
    chassis.moveToPoint(60,-57,2000,{.forwards=false});
    chassis.turnToHeading(300,2000);

    //Drop goal in corner and touch ladder
    intaveyor.brake();
    doinker.set_value(true);
    chassis.moveToPoint(0,-24,3000,{.maxSpeed=127});
}