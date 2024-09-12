#include "ultrasonic.h"

void ultrasonic_init()
{
    gpio_init(ECHO_PIN);    gpio_set_dir(ECHO_PIN, GPIO_IN);
    gpio_init(TRIGGER_PIN); gpio_set_dir(TRIGGER_PIN, GPIO_OUT);
}

double ultrasonic_get_distance()
{
    while(1)
    {
        gpio_put(TRIGGER_PIN, 1);
        sleep_us(10);
        gpio_put(TRIGGER_PIN, 0);

        while(gpio_get(ECHO_PIN) == 0) {}
        const uint32_t time = time_us_32();

        while(gpio_get(ECHO_PIN) == 1) {}
        const uint32_t end_time = time_us_32();

        const uint32_t pulse_duration = end_time - time;

        return ((double)pulse_duration * 0.000343) / 2;
    }
}