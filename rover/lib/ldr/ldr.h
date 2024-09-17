#ifndef LDR_H
#define LDR_H

#include "pico/stdlib.h"
#include "hardware/adc.h"

#define LDR_ADC_PIN   26
#define HEADLIGHT_PIN 15

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
uint16_t ldr_read();

/*
 * [NAME]:        Headlight Toggle
 * [FUNCTION]:    ldr_headlight_toggle();
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Toggle the Rover Headlight
 */
void ldr_headlight_toggle(uint status);

#endif //LDR_H