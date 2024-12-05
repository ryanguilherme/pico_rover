#include "wandering.h"

double mutexDistance;
void wandering_setup()
{
    movement_init();
}

void wandering_loop(QueueHandle_t queue)
{
    double distance[2];
    while(1)
    {
        if (!xQueueReceive(queue, &distance, portMAX_DELAY))
        {
            printf("[ERROR 0201]: Could not read from Ultrasonic Data Queue\n");
        }
        else
        {
            printf("[WANDER] MIDDLE ULTRASONIC DISTANCE: %f\n", distance[0]);
            printf("[WANDER] MIDDLE ULTRASONIC DISTANCE: %f\n", distance[1]);
            if (distance[0] <= MAX_DISTANCE || distance[1] <= MAX_DISTANCE)
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
