#include "main.h"

/*
    ? Cascade operator control


    TODO:
    :Edit values
    :Fix cascade code
*/


int max_cascade_height = 830.0;
std::array<double, 7> cascade_position_list = {0.01, 0.10, 0.30, 0.50, 0.70, 0.90, 0.100};
int cascade_position = 0; // up to 6

int button_leniency = 200; //milliseconds

int cascade_target = 0;
void Cascade_opcontrol() {
    ez::screen_print("cascade activated", 1);
    while (true) {
        if (master.get_digital_new_press(DIGITAL_R1)) {
            int start_time = pros::millis();
            string button_state = "unknown";

            while (true) {
                cascade_motor.move(127);
                if (start_time + button_leniency <= pros::millis()) {
                    button_state = "held";
                    break;
                }
                else if (master.get_digital(DIGITAL_R1) == false) {
                    ez::screen_print("made it", 2);
                    button_state = "pressed";
                    break;
                }
                pros::delay(10);
            }
            
            if (button_state == "pressed") {
                cascade_position += 1;
                if (cascade_position > cascade_position_list.size() - 1) {cascade_position = 0;}
                cascade_target = cascade_position_list[cascade_position] * max_cascade_height;
                button_state = "unknown";
            }
            else if (button_state == "held") {
                while (master.get_digital(DIGITAL_R1)) {
                    cascade_motor.move(127);
                }
                cascade_target = cascade_sensor.get_position() / 100.0;
                button_state = "unknown";
            }
        }
        else if (master.get_digital_new_press(DIGITAL_L1)) {
            int start_time = pros::millis();
            string button_state = "unknown";

            while (true) {
                cascade_motor.move(-127);
                if (start_time + button_leniency <= pros::millis()) {
                    button_state = "held";
                    break;
                }
                else if (master.get_digital(DIGITAL_L1) == false) {
                    button_state = "pressed";
                    break;
                }
                pros::delay(10);
            }
            
            if (button_state == "pressed") {
                cascade_position -= 1;
                if (cascade_position < 0) {cascade_position = cascade_position_list.size() - 1;}
                cascade_target = cascade_position_list[cascade_position] * max_cascade_height;
                button_state = "unknown";
            }
            else if (button_state == "held") {
                while (master.get_digital(DIGITAL_L1)) {
                    cascade_motor.move(-127);
                }
                cascade_target = cascade_sensor.get_position() / 100.0;
                button_state = "unknown";
            }
        }
        else {
            cascadePID.target_set(cascade_target);
        }

        pros::delay(20);
    }
}


void cascade_task() {
    cascade_sensor.reset_position();
    cascadePID.target_set(0);
    pros::delay(2000);
    while (true) {
        cascade_motor.move(cascadePID.compute(cascade_sensor.get_position() / 100.0));

        pros::delay(ez::util::DELAY_TIME);
    }
}

// score
void score() {
    cascadePID.target_set(0);
    cascade_target = 0;
    Ratchet_claw.move(-127);
}