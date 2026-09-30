#include "main.h"

void Pickupmech_opcontrol() {
     if (master.get_digital(DIGITAL_UP)) {
        pickupmech_motor.move(127);
    }
    else if (master.get_digital(DIGITAL_DOWN)) {
        pickupmech_motor.move(-127);
    }
    else {
        pickupmech_motor.move(0);
    }
}