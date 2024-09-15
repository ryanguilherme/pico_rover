//
// Created by guilherme on 15/09/24.
//

#include "rain.h"

void rain_init(){
     gpio_init(RAIN_PIN); gpio_set_dir(RAIN_PIN, GPIO_IN);

     adc_init(); adc_select_input(RAIN_ADC_CHANNEL); adc_gpio_init(RAIN_ADC_PIN);
}

int rain_read(){
      return gpio_get(RAIN_PIN);
}

float rain_read_percentual(){
      return 100 - adc_read() * (100.0 / 4096);
}