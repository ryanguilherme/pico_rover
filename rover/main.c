#include "FreeRTOS.h"
#include "pico/stdlib.h"
#include "web.h"
#include "ultrasonic.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "wandering.h"
#include "ldr.h"
#include "dht11.h"

#define QUEUE_LENGTH 10

QueueHandle_t ultrasonic_queue;
SemaphoreHandle_t ultrasonic_semaphore;

double mutex_distance;

void ultrasonic_task()
{
    ultrasonic_init();
    while(1)
    {

        double distance = ultrasonic_get_distance();
        if (xSemaphoreTake(ultrasonic_semaphore, portMAX_DELAY) != pdTRUE)
        {
            printf("[ERROR 0101]: Could not take Ultrasonic Mutex\n");
        }
        else{
            mutex_distance = distance;
        }
        xSemaphoreGive(ultrasonic_semaphore);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void wandering_task()
{
    wandering_setup();
    wandering_loop(ultrasonic_semaphore);
}

void dht11_task()
{
    int temperature;
    int humidity;
    dht11_init();
    while(1)
    {
        if (dht11_read_data(&temperature, &humidity) == 0)
            printf("TEMPERATURE: %d, HUMIDITY: %d\n", temperature, humidity);
        else
            printf("[ERROR 0301]: Could not Read Data from DHT11\n");
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void ldr_task()
{
    uint16_t ldr_value;
    ldr_init();
    while(1)
    {
        ldr_value = ldr_read();
        if (ldr_value >= 3800) ldr_headlight_toggle(1);
        else                   ldr_headlight_toggle(0);
        printf("LDR VALUE: %d\n", ldr_value);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

int main() {
    stdio_init_all();
	//web_setup();

    ultrasonic_queue = xQueueCreate(QUEUE_LENGTH, sizeof(double));
    ultrasonic_semaphore = xSemaphoreCreateMutex();

    if(ultrasonic_semaphore == NULL)
    {
        printf("[ERROR 0001]: Could not create Ultrasonic Semaphore\n");
        while(1);
    }

    xTaskCreate(ultrasonic_task, "UltrasonicTask", 256, NULL, 1, NULL);
    xTaskCreate(wandering_task, "WanderingTask", 256, NULL, 1, NULL);
    xTaskCreate(dht11_task, "DHT11Task", 256, NULL, 2, NULL);
    xTaskCreate(ldr_task, "LDRTask", 256, NULL, 1, NULL);

    vTaskStartScheduler();
    // Code should never reach here
    while(1);
}
