#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "pico/stdlib.h"

#define ECHO_PIN     2
#define TRIGGER_PIN  3

/*
 * [NAME]:        Init
 * [FUNCTION]:    ultrasonic_init()
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Initialize every necessary pin for the HC-SR04 usage
 */
void ultrasonic_init();
/*
 * [NAME]:        Get Distance
 * [FUNCTION]:    ultrasonic_get_distance()
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Get the distance of what is in front of the Rover
 */
double ultrasonic_get_distance();

#endif //ULTRASONIC_H
