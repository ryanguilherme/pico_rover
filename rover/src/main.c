/*
	Authors: Ryan Guilherme   (github.com/ryanguilherme)
		 Guilherme Araujo (github.com/guiaf04)
		 Eliton Melo      (github.com/elitonnmelo)
	Description: ---
*/

#include "FreeRTOS.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main()
{
    stdio_init_all();

    if (cyw43_arch_init()) return -1;

}
