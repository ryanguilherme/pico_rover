#include "wandering.h"

extern double mutexDistance;

void wandering_setup()
{
    movement_init();
}

void wandering_loop(SemaphoreHandle_t semphr)
{
    double distance;
    while(1)
    {
        if (xSemaphoreTake(semphr, portMAX_DELAY) != pdTRUE)
        {
            printf("[ERROR 0201]: Could not take Ultrasonic Mutex\n");
            xSemaphoreGive(semphr);
        }

        else
        {
            distance = mutexDistance;
            xSemaphoreGive(semphr);
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
