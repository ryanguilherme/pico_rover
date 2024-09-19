add_library(remote_control
        remote_control.h
        remote_control.c
)

target_link_libraries(remote_control
        pico_stdlib
        movement
        FreeRTOS-Kernel-Heap4
)

target_include_directories(remote_control PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

pico_enable_stdio_usb(${ProjectName} 1)
pico_enable_stdio_uart(${ProjectName} 0)
