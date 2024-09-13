#ifndef DHT11_H
#define DHT11_H

#include "pico/stdlib.h"

#define DHT11_DATA_PIN 15

/*
 * [NAME]:        Init
 * [FUNCTION]:    dht11_init()
 * [PARAMETERS]:  void
 * [DESCRIPTION]: Initialize and configure DHT11 sensor
 */
void dht11_init();
/*
 * [NAME]:        Read Data
 * [FUNCTION]:    dht11_read_data()
 * [PARAMETERS]:  float *, float *
 * [DESCRIPTION]: Read DHT11 temperature and humidity and associate it with a respective pointer
 */
int dht11_read_data(float *temperature, float *humidity);

#endif 