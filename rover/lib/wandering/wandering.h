#ifndef WANDERING_H
#define WANDERING_H

#include "FreeRTOS.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "movement.h"
#include "queue.h"


#define MAX_DISTANCE 40

/*
 * [NAME]:        Setup
 * [FUNCTION]:    wandering_setup()
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Initialize every necessary pin for the rover wandering functionality
 */
void wandering_setup();
/*
 * [NAME]:        Loop
 * [FUNCTION]:    wandering_loop(QueueHandle_t queue)
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Makes the rover starts wandering avoiding obstacles
 */
void wandering_loop(QueueHandle_t queue);

#endif //WANDERING_H
