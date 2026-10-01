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

void hand_opcontrol() {
    if (master.get_digital(DIGITAL_LEFT)) {
        pickupmech_motor.move(127);
    }
    else if (master.get_digital(DIGITAL_RIGHT)) {
        pickupmech_motor.move(-127);
    }
    else {
        pickupmech_motor.move(0);
    }

    if (cascade_sensor.get_position() < 180) {
        wrist_motor.move_absolute(0, 200);
    }
    else if (cascade_sensor.get_position() > 180) {
        wrist_motor.move_absolute(-90, 200); //negative will rotate the arm up
    }
}

void hand_reset();