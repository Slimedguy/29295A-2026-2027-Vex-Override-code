#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

/**
 ** Custom PID Declaration
 *! inline ez::PID ExamplenamePID({0, 0, 0, 0, "Example_PID"})
 *? declare,       name,           P, I, D, starting I value, "also name see below"
 *! Example_PID.move(ExamplenamePID.compute(Example_PID.get_position()));
 *TODO: 
 *: Add PID for cascade lift. also make proper controls for this PID
 */
