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

void Pickupmech_opcontrol() {
    if (master.get_digital(DIGITAL_L2)) {
        pickupmech_motor.move(127);
    }
    else if (master.get_digital(DIGITAL_R2)) {
        pickupmech_motor.move(-127);
    }
    else {
        pickupmech_motor.move(0);
        pickupmech_motor.brake();
    }
}

void Wrist_opcontrol() {
    if (master.get_digital(DIGITAL_LEFT)) {
        wrist_motor.move(127);
    }
    else if (master.get_digital(DIGITAL_RIGHT)) {
        wrist_motor.move(-127);
    }
    else {
        wrist_motor.move(0);
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