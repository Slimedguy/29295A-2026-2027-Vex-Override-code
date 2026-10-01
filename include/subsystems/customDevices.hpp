#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

/**
 ** Custom Devices
 *TODO: 
 *: All motors for intake.
 *: All motors for cascade lift.
 *: Other things I don't know about.
 *: one of those things was a rotation sensor.
 */

inline pros::Motor intake_motors(7);

inline pros::Motor cascade_motor(16);

inline pros::Motor pickupmech_motor(15, pros::v5::MotorGears::green);
inline pros::Motor wrist_motor(11, pros::v5::MotorGears::green);

inline pros::Rotation cascade_sensor(1);

inline pros::ADIDigitalIn cascade_limit_switch('A');