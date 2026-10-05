#include "main.h"

/*
    ? Cascade operator control
    ? Cascade calibrate function

    TODO:
    :Edit values
    :Fix cascade code
*/

int cascade_target = 0;
void Cascade_opcontrol() {

    if (master.get_digital(DIGITAL_R1)) {
        cascade_motor.move(127);
        cascade_target = cascade_sensor.get_position() / 100.0;
    }
    else if (master.get_digital(DIGITAL_L1)) {
        cascade_motor.move(-127);
        cascade_target = cascade_sensor.get_position() / 100.0;
    }
    else {
        cascadePID.target_set(cascade_target);
        cascade_motor.move(cascadePID.compute(cascade_sensor.get_position() / 100.0));
    }
}

void Cascade_calibrate() {
    double starttime = pros::millis();
    cascade_motor.move_velocity(15);
    while((pros::millis() - starttime) < 2500){
        pros::delay(20);
    }
    
    cascade_motor.move_velocity(-15);
    while (cascade_limit_switch.get_value()) {
        pros::delay(15);
    }
    cascade_motor.brake();
    cascade_sensor.set_position(0);
}
/*
void Cascade_opcontrol() {
    if (abs(master.get_analog(ANALOG_LEFT_Y)) > 10) {
    target += abs(master.get_analog(ANALOG_LEFT_Y)) * 0.05;
    }
    cascade_motor.move_absolute(target, 100);


}*/