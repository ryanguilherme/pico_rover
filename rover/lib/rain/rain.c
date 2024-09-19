//
// Created by guilherme on 15/09/24.
//

#include "rain.h"

void rain_init(){
     gpio_init(RAIN_PIN); gpio_set_dir(RAIN_PIN, GPIO_IN);
}

int rain_read(){
      return gpio_get(RAIN_PIN);
}