#include "wandering.h"

double mutexDistance;
void wandering_setup()
{
    movement_init();
}

void wandering_loop(QueueHandle_t queue)
{
    gpio_init(15); gpio_set_dir(15, GPIO_OUT);
    double distance;
    while(1)
    {
        if (!xQueueReceive(queue, &distance, portMAX_DELAY))
        {
            printf("[ERROR 0201]: Could not read from Ultrasonic Data Queue\n");
        }
        else
        {
            printf("ULTRASONIC DISTANCE: %f\n", distance);
            if (distance <= MAX_DISTANCE)
            {
                gpio_put(15, 1);
                movement_rotate_right();
            } else
            {
                gpio_put(15, 0);
                movement_forward();
            }
            sleep_ms(10);
        }
    }
}
