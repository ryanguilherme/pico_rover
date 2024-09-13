cmake_minimum_required(VERSION 3.12)

# Name project
SET(ProjectName rover)

# Set board to the Wireless version
SET(PICO_BOARD pico_w)

# Import those libraries
include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/pico_sdk_import.cmake)
include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Define project
project(${ProjectName} CXX C ASM)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add subdirectories
add_subdirectory(src)

# file to the "lib" directory
add_subdirectory(lib/movement)
add_subdirectory(lib/ultrasonic)
add_subdirectory(lib/wandering)
add_subdirectory(lib/ldr)
