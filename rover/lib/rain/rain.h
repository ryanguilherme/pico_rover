//
// Created by guilherme on 15/09/24.
//

#ifndef RAIN_H
#define RAIN_H

#include "pico/stdlib.h"

#define RAIN_PIN 10
#define RAIN_ADC_PIN 27
#define RAIN_ADC_CHANNEL 1

/*
 * [NAME]:        Init
 * [FUNCTION]:    rain_init()
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Initialize every necessary pin for the Raindrops sensor usage
 */
void rain_init();

/*
 * [NAME]:        Read
 * [FUNCTION]:    rain_read()
 * [PARAMETERS]:  int
 * [DESCRIPTION]: Read the rain sensor value and return the presence or not of water above 50%
 */
int rain_read();

#endif //RAIN_H
