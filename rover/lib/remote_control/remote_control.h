#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

#include "pico/stdlib.h"

#define MOVE_FORWARD_PIN    21
#define ROTATE_LEFT_PIN     20
#define ROTATE_RIGHT_PIN    19
#define STOP_PIN            18

/*
 * [NAME]:        Init
 * [FUNCTION]:    remote_control_init()
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Initialize every necessary pin for the Remote Control functionalities
 */
void remote_control_init();
/*
 * [NAME]:        Control
 * [FUNCTION]:    remote_control_control()
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Verify if the combination of pins is current pressed to alternate the control of the rover
 */
int remote_control_control();

#endif //REMOTE_CONTROL_H
