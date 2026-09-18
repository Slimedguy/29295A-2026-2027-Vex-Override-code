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
inline pros::Motor left_55w_motor(9, pros::MotorGearset::green, pros::MotorEncoderUnits::degrees);
inline pros::Motor right_55w_motor(10, pros::MotorGearset::green, pros::MotorEncoderUnits::degrees);