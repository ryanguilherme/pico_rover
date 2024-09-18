#include "movement.h"

void movement_init()
{
    gpio_init(IN1);     gpio_set_dir(IN1, GPIO_OUT);
    gpio_init(IN2);     gpio_set_dir(IN2, GPIO_OUT);
    gpio_init(IN3);     gpio_set_dir(IN3, GPIO_OUT);
    gpio_init(IN4);     gpio_set_dir(IN4, GPIO_OUT);
    float duty_cycle=50;
    // Set the GPIO function to PWM
    gpio_set_function(PWM_SPEED_PIN, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to the specified GPIO
    uint slice_num = pwm_gpio_to_slice_num(PWM_SPEED_PIN);

    // Calculate the PWM frequency and set the PWM wrap value
    float clock_freq = 125000000.0f;  // Default Pico clock frequency in Hz
    uint32_t divider = clock_freq / (100 * 4096);  // Compute divider for given frequency
    pwm_set_clkdiv(slice_num, divider);

    // Set the PWM wrap value (maximum count value)
    pwm_set_wrap(slice_num, 99);  // 12-bit resolution (0-4095)
    // Enable the PWM
    pwm_set_enabled(slice_num, true);
}

void movement_forward()
{
    gpio_put(IN1, GPIO_HIGH);
    gpio_put(IN2, GPIO_LOW);
    gpio_put(IN3, GPIO_HIGH);
    gpio_put(IN4, GPIO_LOW);
}

void movement_rotate_right()
{
    gpio_put(IN1, GPIO_HIGH);
    gpio_put(IN2, GPIO_LOW);
    gpio_put(IN3, GPIO_LOW);
    gpio_put(IN4, GPIO_HIGH);
}

void movement_rotate_left()
{
    gpio_put(IN1, GPIO_LOW);
    gpio_put(IN2, GPIO_HIGH);
    gpio_put(IN3, GPIO_HIGH);
    gpio_put(IN4, GPIO_LOW);
}

void movement_stop()
{
    gpio_put(IN1, GPIO_LOW);
    gpio_put(IN2, GPIO_LOW);
    gpio_put(IN3, GPIO_LOW);
    gpio_put(IN4, GPIO_LOW);
}

void movement_set_speed(uint speed)
{

    uint slice_num = pwm_gpio_to_slice_num(PWM_SPEED_PIN);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, speed);
}

