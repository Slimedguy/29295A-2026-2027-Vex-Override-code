#include "main.h"

//* Although you can use the built in drive controls this allow for better Driver personalization

// The drivecode variable declaration
float pCurve = 0.5;        //? curve for fwd/back
float tCoefficient = 1.1;  //? curve for turn
float tCurve = 0.66;       //? coefficient for turn
double power;
double powerC;
double turn;
double turnC;
bool halfSpeed = false;
double leftDrv;
double rightDrv;

void drivetrain_opcontrol() {
    // Setting power and turn variables
    power = master.get_analog(ANALOG_LEFT_Y);  // Left stick vertical
    turn = master.get_analog(ANALOG_RIGHT_X);  // Right stick horizontal

    // Calculating velocity
    powerC = ((1 - pCurve) * power) + ((pCurve * pow(power, 3)) / 16129); // don't change 16129
    //https://www.desmos.com/calculator/asjs86sdpy

    // Calculating turn curve
    turnC = tCoefficient * ((1 - tCurve) * turn) + ((tCurve * pow(turn, 3)) / 16129); // don't change 16129

    leftDrv = powerC + turnC;
    rightDrv = powerC - turnC;

    // Arcade Drive, setting the motor velocity
    left_55w_motor.move(leftDrv);
    right_55w_motor.move(rightDrv);
    chassis.drive_set(leftDrv, rightDrv);
}