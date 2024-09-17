#include "ldr.h"

void ldr_init()
{
    adc_init();     adc_gpio_init(LDR_ADC_PIN);
    adc_select_input(0);
}

int16_t ldr_read()
{
    return adc_read();
}