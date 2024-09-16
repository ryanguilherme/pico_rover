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
#include "web.h"

int main()
{

    stdio_init_all();
	web_setup();
    //if (cyw43_arch_init()) return -1;
	//movement_init();
	//wandering_setup();
	//ultrasonic_init();
	//xTaskCreate(movement_tests, "WanderingLoopTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	//xTaskCreate(wandering_loop, "WanderingLoopTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	//vTaskStartScheduler();
	while(1);
}











