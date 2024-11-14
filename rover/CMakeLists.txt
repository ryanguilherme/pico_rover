cmake_minimum_required(VERSION 3.13)

#Name project
set(ProjectName rover)

#Set board to the Wireless version
set(PICO_BOARD pico_w)

# Import those libraries
include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/pico_sdk_import.cmake)
include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

#Define project
project(${ProjectName} CXX C ASM)

#Initialize the Raspberry Pi Pico SDK
pico_sdk_init()


message("Running makefsdata python script")
execute_process(COMMAND
    py makefsdata.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

add_executable(${ProjectName}
    main.c
)

include_directories(${CMAKE_SOURCE_DIR})

target_include_directories(${ProjectName} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${PROJECT_SOURCE_DIR}/lib
)

#Link libraries
target_link_libraries(${ProjectName}
    FreeRTOS-Kernel-Heap4
    pico_stdlib
    hardware_adc
    web
    ultrasonic
    wandering
    ldr
    dht11
    rain
    remote_control
    mpu
)

#Add subdirectories
add_subdirectory(lib)

#Enable USB Uart output
pico_enable_stdio_usb(${ProjectName} TRUE)
pico_enable_stdio_uart(${ProjectName} FALSE)

#Add extra outputs
pico_add_extra_outputs(${ProjectName})
