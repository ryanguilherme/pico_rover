#include "wandering.h"

void wandering_setup()
{
    movement_init();
    ultrasonic_init();
}

void wandering_loop()
{

    while(1)
    {
        while(ultrasonic_get_distance() <= 20)
        {
            movement_forward();
        }
        while(ultrasonic_get_distance() > 20)
        {
            movement_rotate_right();
        }
    }
}