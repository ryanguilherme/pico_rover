#ifndef LDR_H
#define LDR_H

#include "pico/stdlib.h"
#include "hardware/adc.h"

#define LDR_ADC_PIN 26

/*
 * [NAME]:        Init
 * [FUNCTION]:    ldr_init()
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Initialize every necessary pin for the LDR sensor usage
 */
void ldr_init();
/*
 * [NAME]:        Read
 * [FUNCTION]:    ldr_read()
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Read the LDR sensor value and return the light intensity
 */
double ldr_read();

#endif LDR_H