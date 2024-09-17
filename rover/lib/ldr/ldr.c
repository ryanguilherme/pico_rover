#include "ldr.h"

void ldr_init()
{
    adc_init();                 adc_gpio_init(LDR_ADC_PIN);
    gpio_init(HEADLIGHT_PIN);   gpio_set_dir(HEADLIGHT_PIN, GPIO_OUT);
    adc_select_input(0);
}

uint16_t ldr_read()
{
    return adc_read();
}

void ldr_headlight_toggle(uint status)
{
    gpio_put(HEADLIGHT_PIN, status);
}