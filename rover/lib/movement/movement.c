#include "movement.h"

void movement_init()
{
    gpio_init(IN1);     gpio_set_dir(IN1, GPIO_OUT);
    gpio_init(IN2);     gpio_set_dir(IN2, GPIO_OUT);
    gpio_init(IN3);     gpio_set_dir(IN3, GPIO_OUT);
    gpio_init(IN4);     gpio_set_dir(IN4, GPIO_OUT);
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

