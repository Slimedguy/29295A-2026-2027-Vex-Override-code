#include "main.h"

/*
    ? Cascade operator control
    ? Cascade calibrate function

    TODO:
    :Edit values
    ;Fix cascade code
    :change code setup
*/

//setup
int cascade_target = 0;
int max_cascade_height_deg = 360 * 2.45; // master control changing this changes every other position
int minimum_cascade_height_deg = 0;
string state = "manual";

//region markers
int forth_cascade_region_deg = max_cascade_height_deg * 0.9;
int third_cascade_region_deg = max_cascade_height_deg * 0.7;
int second_cascade_region_deg = max_cascade_height_deg * 0.5;
int first_cascade_region_deg = max_cascade_height_deg * 0.3;

void Cascade_opcontrol() {
 // these control the speed that the cascade rises based on total posiiton
    if (master.get_digital(DIGITAL_R1) && state == "manual") {
        if (cascade_sensor.get_position() > forth_cascade_region_deg) {
            cascade_motor.move(127 * 0.9);
            cascade_target = cascade_sensor.get_position() / 100.0;
        }
        else if (cascade_sensor.get_position() > third_cascade_region_deg) {
            cascade_motor.move(127 * 0.95);
            cascade_target = cascade_sensor.get_position() / 100.0;
        }
        else {
            cascade_motor.move(127 * 1);
            cascade_target = cascade_sensor.get_position() / 100.0;
        }
    }
    else if (master.get_digital(DIGITAL_L1) && state == "manual") {
        if (cascade_sensor.get_position() < forth_cascade_region_deg) {
            cascade_motor.move(-127 * 1);
            cascade_target = cascade_sensor.get_position() / 100.0;
        }
        else if (cascade_sensor.get_position() < third_cascade_region_deg) {
            cascade_motor.move(-127 * 0.95);
            cascade_target = cascade_sensor.get_position() / 100.0;
        }
        else if (cascade_sensor.get_position() < second_cascade_region_deg) {
            cascade_motor.move(-127 * 0.85);
            cascade_target = cascade_sensor.get_position() / 100.0;
        }
        else if (cascade_sensor.get_position() < first_cascade_region_deg) {
            cascade_motor.move(-127 * 0.8);
            cascade_target = cascade_sensor.get_position() / 100.0;
        }
        else {
            cascade_motor.move(-127);
            cascade_target = cascade_sensor.get_position() / 100.0;
        }
    }
    else if (state == "manual") {
        cascade_motor.brake();
    }

    int load_motor_deg = 0;
    if (state == "load") {
        cascadePID.target_set(load_motor_deg / 0.25); // gear ratio of 12-48 in the wrist motor
        cascade_motor.move(cascadePID.compute(cascade_sensor.get_position() / 100.0));
    }

    if (master.get_digital_new_press(DIGITAL_UP)) { // moves up the list of states
        if (state == "load") {
            state == "manual";
        }
        else if (state == "load") {
            state == "manual";
        }
    }
    else if (master.get_digital_new_press(DIGITAL_DOWN)) { // moves down the list of states
        if (state == "load") {
            state == "manual";
        }
        else if (state == "manual") {
            state == "load";
        }

    }


    // if (master.get_digital(DIGITAL_R1)) {
    //     cascade_motor.move(127);
    //     cascade_target = cascade_sensor.get_position() / 100.0;
    // }
    // else if (master.get_digital(DIGITAL_L1)) {
    //     cascade_motor.move(-127);
    //     cascade_target = cascade_sensor.get_position() / 100.0;
    // }
    // else {
    //     cascadePID.target_set(cascade_target);
    //     cascade_motor.move(cascadePID.compute(cascade_sensor.get_position() / 100.0));
    // }
}

void Cascade_calibrate() {
    double starttime = pros::millis();
    cascade_motor.move(70);
    while((pros::millis() - starttime) < 2500){
        pros::delay(20);
    }
    
    cascade_motor.move_velocity(-60);
    while (true) {
        int set_speed = 30;
        int speed = cascade_motor.get_actual_velocity();

        if (cascade_limit_switch.get_value()) {
            break;
        }
        if (speed > set_speed) {
            cascade_motor.move_voltage(20);
        }
        else {
            cascade_motor.move_voltage(0);
        }
        pros::delay(10);
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