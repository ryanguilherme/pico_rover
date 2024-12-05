#include "ultrasonic.h"

void ultrasonic_init()
{
    gpio_init(M_ECHO_PIN);    gpio_set_dir(M_ECHO_PIN, GPIO_IN);
    gpio_init(M_TRIGGER_PIN); gpio_set_dir(M_TRIGGER_PIN, GPIO_OUT);

    gpio_init(L_ECHO_PIN);    gpio_set_dir(L_ECHO_PIN, GPIO_IN);
    gpio_init(L_TRIGGER_PIN); gpio_set_dir(L_TRIGGER_PIN, GPIO_OUT);
}

double middle_ultrasonic_get_distance()
{
    gpio_put(M_TRIGGER_PIN, 1);
    sleep_us(10);
    gpio_put(M_TRIGGER_PIN, 0);

    while(gpio_get(M_ECHO_PIN) == 0) {}
    const uint32_t time = time_us_32();

    while(gpio_get(M_ECHO_PIN) == 1) {}
    const uint32_t end_time = time_us_32();

    const uint32_t pulse_duration = end_time - time;

    return (pulse_duration * 0.0343) / 2;

}

double left_ultrasonic_get_distance()
{
    gpio_put(L_TRIGGER_PIN, 1);
    sleep_us(10);
    gpio_put(L_TRIGGER_PIN, 0);

    while(gpio_get(L_ECHO_PIN) == 0) {}
    const uint32_t time = time_us_32();

    while(gpio_get(L_ECHO_PIN) == 1) {}
    const uint32_t end_time = time_us_32();

    const uint32_t pulse_duration = end_time - time;

    return (pulse_duration * 0.0343) / 2;

}

