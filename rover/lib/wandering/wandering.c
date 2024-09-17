#include "wandering.h"

double mutexDistance;
void wandering_setup()
{
    movement_init();
}

void wandering_loop(QueueHandle_t queue)
{
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
                movement_rotate_right();
            } else
            {
                movement_forward();
            }
            vTaskDelay(pdMS_TO_TICKS(200));
        }
    }
}
