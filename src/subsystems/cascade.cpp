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
    cascade_motor.move(cascadePID.compute(cascade_sensor.get_position() / 100));
}

void Cascade_reset() {
    double starttime = pros::millis();
    cascade_motor.move_velocity(-30);
    while((pros::millis() - starttime) < 2500){
        pros::delay(20);
    }
    
    cascade_motor.move_velocity(30);
    while ( cascade_limit_switch.get_value()) {
        pros::delay(20);
    }
    cascade_motor.brake();
    cascade_sensor.reset_position();
}
/*
void Cascade_opcontrol() {
    if (abs(master.get_analog(ANALOG_LEFT_Y)) > 10) {
    target += abs(master.get_analog(ANALOG_LEFT_Y)) * 0.05;
    }
    cascade_motor.move_absolute(target, 100);


}*/