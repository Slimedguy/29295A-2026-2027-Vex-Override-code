#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

/**
 ** Custom Devices
 *TODO: 
 *; All motors for intake.
 *; All motors for cascade lift.
 *; Other things I don't know about.
 *; one of those things was a rotation sensor.
 */

inline pros::Motor intake_motors(19);

inline pros::Motor cascade_motor(-16);

inline pros::Motor pickupmech_motor(17, pros::v5::MotorGears::green);
inline pros::Motor wrist_motor(15, pros::v5::MotorGears::green);

inline pros::Rotation cascade_sensor(-12);

inline pros::adi::DigitalIn cascade_limit_switch('G');