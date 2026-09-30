#include "main.h"

int target;


void Cascade_opcontrol() {

    if (master.get_digital(DIGITAL_L1)) {
        target -= 10;
    }
    else if (master.get_digital(DIGITAL_R2)) {
        target += 10;
    }

    cascadePID.target_set(target);
    cascade_motor.move(cascadePID.compute(cascade_motor.get_position()));
}
/*
void Cascade_opcontrol() {
    if (abs(master.get_analog(ANALOG_LEFT_Y)) > 10) {
    target += abs(master.get_analog(ANALOG_LEFT_Y)) * 0.05;
    }
    cascade_motor.move_absolute(target, 100);


}*/