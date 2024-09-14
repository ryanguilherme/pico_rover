/*
	Authors: Ryan Guilherme   (github.com/ryanguilherme)
			 Guilherme Araujo (github.com/guiaf04)
			 Eliton Melo      (github.com/elitonnmelo)
	Description: ---
*/

#include "FreeRTOS.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "task.h"
#include "movement.h"
#include "wandering.h"

void movement_tests()
{
	movement_init();
	sleep_ms(25);
	while(1)
	{
		movement_forward();
		sleep_ms(2500);
		movement_stop();
		sleep_ms(1000);
		movement_rotate_left();
		sleep_ms(2500);
		movement_stop();
		sleep_ms(1000);
		movement_rotate_right();
		sleep_ms(2500);
	}
}

void ultrasonic_test()
{
	gpio_init(15);
	gpio_set_dir(15, GPIO_OUT);
	while(1)
	{
		double distance = ultrasonic_get_distance();
		if (distance <= 10)
		{
			gpio_put(15, 0);
		} else
		{
			gpio_put(15, 1);
		}
	}
}

int main()
{
    stdio_init_all();

    //if (cyw43_arch_init()) return -1;
	//movement_init();
	wandering_setup();
	//ultrasonic_init();
	//xTaskCreate(movement_tests, "WanderingLoopTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	xTaskCreate(wandering_loop, "WanderingLoopTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();
}











