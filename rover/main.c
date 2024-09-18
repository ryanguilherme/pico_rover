#include "FreeRTOS.h"
#include "pico/stdlib.h"
#include "web.h"
#include "ultrasonic.h"
#include "task.h"
#include "queue.h"
#include "wandering.h"
#include "ldr.h"
#include "dht11.h"

#define QUEUE_LENGTH 10

QueueHandle_t ultrasonic_queue;

void ultrasonic_task()
{
    ultrasonic_init();
    while(1)
    {
        double distance = ultrasonic_get_distance();
        if (xQueueSend(ultrasonic_queue, &distance, portMAX_DELAY) != pdPASS)
        {
            printf("[ERROR 0101]: Failed to send Ultrasonic Distance Data to respective queue!\n");
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void wandering_task()
{
    wandering_setup();
    wandering_loop(ultrasonic_queue);
}

void dht11_task()
{
    sleep_ms(2000);
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

void ldr_task(void *pvParameters)
{
    ldr_init();
    uint16_t ldr_data;
    while(1)
    {
        ldr_data = ldr_read();
        printf("LDR Light Intensity: %d", ldr_data);
        if (ldr_data > 3800)    ldr_headlight_toggle(1);
        else                    ldr_headlight_toggle(0);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void pwm_test_task() {
    movement_init();
    while(1) {
        movement_set_speed(50);
        printf("DUTY CYCLE 50\n");
        sleep_ms(2000);
        movement_set_speed(25);
        printf("DUTY CYCLE 25\n");
        sleep_ms(2000);
        movement_set_speed(10);
        printf("DUTY CYCLE 10\n");
        sleep_ms(2000);
        movement_set_speed(100);
        printf("DUTY CYCLE 10\n");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

int main() {
    stdio_init_all();
	//web_setup();

    // ultrasonic_queue = xQueueCreate(QUEUE_LENGTH, sizeof(double));
    //
    // xTaskCreate(ultrasonic_task, "UltrasonicTask", 256, NULL, 1, NULL);
    // xTaskCreate(wandering_task, "WanderingTask", 256, NULL, 1, NULL);
    // xTaskCreate(dht11_task, "dht11Task", 256, NULL, 1, NULL);
    xTaskCreate(pwm_test_task, "pwmTestTask", 256, NULL, 1, NULL);

    vTaskStartScheduler();
    // Code should never reach here
    while(1);
}
