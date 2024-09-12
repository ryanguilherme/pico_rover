#ifndef WANDERING_H
#define WANDERING_H

#include "pico/stdlib.h"
#include "movement.h"
#include "ultrasonic.h"

/*
 * [NAME]:        Setup
 * [FUNCTION]:    wandering_setup()
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Initialize every necessary pin for the rover wandering functionality
 */
void wandering_setup();
/*
 * [NAME]:        Loop
 * [FUNCTION]:    wandering_loop()
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Makes the rover starts wandering avoiding obstacles
 */
void wandering_loop();

#endif //WANDERING_H
