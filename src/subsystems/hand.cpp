#include "main.h"

/*
    ! this file does contain both pickup mech and wrist motor control frameworks
    ? the pickup mech control is first
    ? the wrist control is second
    ? second ufnction is position reset

    TODO:
    ;the wrist motor control
    ;pickup mech control
*/

int wristState = 1;

void Ratchet_claw_opcontrol() {
    if (master.get_digital(DIGITAL_R2)) {
        Ratchet_claw.move(127);
    }
    else if (master.get_digital(DIGITAL_L2)) {
        Ratchet_claw.move(-127);
    }
    else {
        Ratchet_claw.move(0);
        Ratchet_claw.brake();
    }
}

void Wrist_opcontrol() {
    if (master.get_digital_new_press(DIGITAL_DOWN)) {
        wristState = 1;
    }
    else if (master.get_digital_new_press(DIGITAL_RIGHT)) {
        wristState = 0;
    }

    if (wristState == 1) {
        if (wrist_motor.get_current_draw() >= 2000) {
            wrist_motor.brake();
            wristState = 2;
        }
        else {
            wrist_motor.move(-127);
        }
    }
    else if (wristState == 0) {
        if (wrist_motor.get_current_draw() >= 2000) {
            wrist_motor.brake();
            wristState = 3;
        }
        else {
            wrist_motor.move(127);
        }
    }
    else if (wristState == 2) {
        wrist_motor.move(-5);
    }
    else if (wristState == 3) {
        wrist_motor.move(10);
    }
    else {
        wrist_motor.brake();
    }
}

void Wrist_autcontrol() {
    if (cascade_sensor.get_position() < 180) {
        wrist_motor.move_absolute(0, 200);
    }
    else if (cascade_sensor.get_position() > 180) {
        wrist_motor.move_absolute(-90, 200); //negative will rotate the arm up
    }
}

//void Hand_calibrate();