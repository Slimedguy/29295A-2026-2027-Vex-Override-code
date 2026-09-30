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

inline pros::MotorGroup intake_motors({7, 8});

inline pros::Motor cascade_motor(24);

inline pros::Motor pickupmech_motor(21, pros::v5::MotorGears::green);
inline pros::Motor arm_motor(22, pros::v5::MotorGears::green);
