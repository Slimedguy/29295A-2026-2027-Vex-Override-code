#include "main.h"


void Cascade_opcontrol() {

    if (master.get_digital(DIGITAL_L1)) {
        cascadePID.target_set(180);
    }
    else if (master.get_digital(DIGITAL_L2)) {
        cascadePID.target_set(0);
    }

    cascade_motor.move(cascadePID.compute(cascade_motor.get_position()));
}