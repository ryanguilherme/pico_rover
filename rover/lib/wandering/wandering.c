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
        double distance = ultrasonic_get_distance();
        if (distance <= 20)
        {
            movement_rotate_right();
        } else
        {
            movement_forward();
        }
        sleep_ms(50);
    }
}