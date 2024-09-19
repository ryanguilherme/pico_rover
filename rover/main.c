#include "FreeRTOS.h"
#include "pico/stdlib.h"
#include "web.h"
#include "ultrasonic.h"
#include "task.h"
#include "queue.h"
#include "wandering.h"
#include "ldr.h"
#include "dht11.h"
#include "rain.h"
#include "remote_control.h"

#define QUEUE_LENGTH    10
#define ALERT_LED       13

QueueHandle_t ultrasonic_queue;
QueueHandle_t alert_queue;

TaskHandle_t xDHT11TaskHandle;
TaskHandle_t xUltrasonicTaskHandle;
TaskHandle_t xWanderingTaskHandle;
TaskHandle_t xRemoteControlTaskHandle;
TaskHandle_t xAlertTaskHandle;

void alert_task(void *pvParameters)
{
    printf("ALERT TASK INITIALIZED!\n");
    uint queue_flag;
    gpio_init(ALERT_LED);       gpio_set_dir(ALERT_LED, GPIO_OUT);
    while(1)
    {
        xQueueReceive(alert_queue, &queue_flag, portMAX_DELAY/2);
        if (queue_flag == 1)
        {
            gpio_put(ALERT_LED, GPIO_HIGH);
            sleep_ms(250);
            gpio_put(ALERT_LED, GPIO_LOW);
        }
    }
}

void ultrasonic_task(void *pvParameters)
{
    ultrasonic_init();
    while(1)
    {
        double distance = ultrasonic_get_distance();
        if (xQueueSend(ultrasonic_queue, &distance, portMAX_DELAY /1000) != pdPASS)
        {
            printf("[ERROR 0101]: Failed to send Ultrasonic Distance Data to respective queue!\n");
            xQueueSend(alert_queue, 1, portMAX_DELAY/5);
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void wandering_task(void *pvParameters)
{
    wandering_setup();
    wandering_loop(ultrasonic_queue);
}

void dht11_task(void *pvParameters)
{
    int temperature;
    int humidity;
    dht11_init();
    while(1)
    {
        if (dht11_read_data(&temperature, &humidity) == 0)
            printf("TEMPERATURE: %d, HUMIDITY: %d\n", temperature, humidity);
        else
        {
            printf("[ERROR 0301]: Could not Read Data from DHT11\n");
            xQueueSend(alert_queue, 1, portMAX_DELAY/5);
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void ldr_task(void *pvParameters)
{
    ldr_init();
    uint16_t ldr_data;
    while(1)
    {
        ldr_data = ldr_read();
        printf("LDR Light Intensity: %d\n", ldr_data);
        if (ldr_data > 2000)        ldr_headlight_toggle(1);
        else                        ldr_headlight_toggle(0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void rain_task(void *pvParameters)
{
    rain_init();
    while(1)
    {
        if (rain_read() == 1)
        {
            printf("[ALERT] IT IS CURRENTLY RAINING!\n");
            xQueueSend(alert_queue, 1, portMAX_DELAY/5);
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void pwm_test_task(void *pvParameters) {
    movement_init();
    movement_set_speed(47);
    while(1) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void remote_control_task(void *pvParameters)
{
    remote_control_init();
    int state = 0;
    while(1) {
        printf("%d %d %d %d\n", gpio_get(MOVE_FORWARD_PIN), gpio_get(ROTATE_LEFT_PIN), gpio_get(ROTATE_RIGHT_PIN), gpio_get(STOP_PIN));
        printf("STATE IS %d\n", state);
        if ((gpio_get(MOVE_FORWARD_PIN) == 0 && gpio_get(STOP_PIN) == 0) && state == 0) {
            state = 1;
            sleep_ms(1000);
        }
        if ((gpio_get(MOVE_FORWARD_PIN) == 0 && gpio_get(STOP_PIN) == 0) && state == 1) {
            state = 0;
            sleep_ms(1000);
        }

        if (state == 1)
        {
            vTaskSuspend(xWanderingTaskHandle);
            vTaskSuspend(xUltrasonicTaskHandle);
            printf("INSIDE CONTROL FUNCTIONS\n");
            printf("%d %d %d %d\n", gpio_get(MOVE_FORWARD_PIN), gpio_get(ROTATE_LEFT_PIN), gpio_get(ROTATE_RIGHT_PIN), gpio_get(STOP_PIN));
            if(gpio_get(MOVE_FORWARD_PIN) == 0)
            {
                printf("MOVE FORWARD BUTTON PRESSED-----------------------\n");
                movement_forward();
            }
            if(gpio_get(ROTATE_LEFT_PIN) == 0)
            {
                printf("ROTATE LEFT BUTTON PRESSED-----------------------\n");
                movement_rotate_left();
            }
            if(gpio_get(ROTATE_RIGHT_PIN) == 0)
            {
                printf("ROTATE RIGHT BUTTON PRESSED-----------------------\n");
                movement_rotate_right();
            }
            if(gpio_get(STOP_PIN) == 0)
            {
                printf("STOP BUTTON PRESSED-----------------------\n");
                movement_stop();
            }
            vTaskDelay(pdMS_TO_TICKS(25));
        }
        if (state == 0)
        {
            vTaskResume(xWanderingTaskHandle);
            vTaskResume(xUltrasonicTaskHandle);
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    // Print the name of the task who overflowed
    printf("Stack overflow detected in task: %s\n", pcTaskName);
}

int main() {
    stdio_init_all();
    movement_init();
    movement_set_speed(70);
	//web_setup();
    //printf("WEB successfully setup\n");

    ultrasonic_queue = xQueueCreate(QUEUE_LENGTH, sizeof(double));
    alert_queue = xQueueCreate(QUEUE_LENGTH, sizeof(uint));
    //
    xTaskCreate(dht11_task, "dht11Task", 128, NULL, 1, NULL);
    xTaskCreate(wandering_task, "WanderingTask", 1024, NULL, 1, &xWanderingTaskHandle);
    xTaskCreate(ultrasonic_task, "UltrasonicTask", 1024, NULL, 2, &xUltrasonicTaskHandle);
    xTaskCreate(remote_control_task, "RemoteControlTask", 1024, NULL, 1, &xRemoteControlTaskHandle);
    xTaskCreate(alert_task, "AlertTask", 128, NULL, 1, &xAlertTaskHandle);
    xTaskCreate(ldr_task, "LDRTask", 1024, NULL, 1, NULL);
    xTaskCreate(rain_task, "RainTask", 128, NULL, 1, NULL);

    //xTaskCreate(pwm_test_task, "pwmTestTask", 256, NULL, 1, NULL);
    //xTaskCreate(web_test_task, "webTestTask", 256, NULL, 1, NULL);

    vTaskStartScheduler();
    // Code should never reach here
    while(1);
}
