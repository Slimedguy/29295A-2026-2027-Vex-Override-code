#include "main.h"

void arm_opcontrol() {
     if (master.get_digital(DIGITAL_LEFT)) {
        pickupmech_motor.move(127);
    }
    else if (master.get_digital(DIGITAL_RIGHT)) {
        pickupmech_motor.move(-127);
    }
    else {
        pickupmech_motor.move(0);
    }
}