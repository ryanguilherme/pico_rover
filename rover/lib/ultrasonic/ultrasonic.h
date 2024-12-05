#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "pico/stdlib.h"

#define M_ECHO_PIN     2
#define M_TRIGGER_PIN  3
#define L_ECHO_PIN     0
#define L_TRIGGER_PIN  1

/*
 * [NAME]:        Init
 * [FUNCTION]:    ultrasonic_init()
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Initialize every necessary pin for the HC-SR04 usage
 */
void ultrasonic_init();
/*
 * [NAME]:        Get Distance
 * [FUNCTION]:    middle_ultrasonic_get_distance()
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Get the distance of what is in the middle of the front of the Rover
 */
double middle_ultrasonic_get_distance();
/*
 * [NAME]:        Get Distance
 * [FUNCTION]:    left_ultrasonic_get_distance()
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Get the distance of what is in front of the left corner of the Rover
 */
double left_ultrasonic_get_distance();

#endif //ULTRASONIC_H
