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
int cascade_target = 0.0;
int max_cascade_height_deg = -720; // master control changing this changes every other position, rotation sensor detects reverse as up
int minimum_cascade_height_deg = 0;
int cascade_state = 0;
std::vector<int> positions = {15, 33, 50, 66, 90, 100};

int buttontime = 200;

//region markers
double forth_cascade_region_deg = max_cascade_height_deg * 0.9;
double third_cascade_region_deg = max_cascade_height_deg * 0.7;
double second_cascade_region_deg = max_cascade_height_deg * 0.5;
double first_cascade_region_deg = max_cascade_height_deg * 0.3;

void Cascade_opcontrol() {
 
    if (master.get_digital_new_press(DIGITAL_R1)) {
        int time = pros::millis();
        bool held = false;
        while (true) {
            if (pros::millis() - buttontime < time && master.get_digital(DIGITAL_R1) == false) {
                held = false;
                break;
            }
            else if (pros::millis() - buttontime >= time && master.get_digital(DIGITAL_R1) == true) {
                held = true;
                break;
            }
            pros::delay(2);
        }
        if (held == true) {
            while (master.get_digital(DIGITAL_R1)) {
                cascade_motor.move(127);
                cascade_target = cascade_sensor.get_position() / 100.0;
            }
        }
        else if (held == false) {
            cascade_state += 1;
            cascade_target = max_cascade_height_deg * (positions[cascade_state] / 100);
        }
    }
    else {
        cascadePID.target_set(cascade_target);
        cascade_motor.move(cascadePID.compute(cascade_sensor.get_position() / 100.0));
    }

    // if (master.get_digital(DIGITAL_R1)) {
    //     cascade_motor.move(127);
    //     cascade_target = cascade_sensor.get_position() / 100.0;
    // }
    // else if (master.get_digital(DIGITAL_L1)) {
    //     cascade_motor.move(-127);
    //     cascade_target = cascade_sensor.get_position() / 100.0;
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
    cascade_sensor.set_position(0);
}
/*
void Cascade_opcontrol() {
    if (abs(master.get_analog(ANALOG_LEFT_Y)) > 10) {
    target += abs(master.get_analog(ANALOG_LEFT_Y)) * 0.05;
    }
    cascade_motor.move_absolute(target, 100);


}*/