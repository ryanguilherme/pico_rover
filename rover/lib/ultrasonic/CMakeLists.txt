add_library(ultrasonic
        ultrasonic.h
        ultrasonic.c
)

target_link_libraries(ultrasonic
        pico_stdlib
)

target_include_directories(ultrasonic PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

pico_enable_stdio_usb(${ProjectName} 1)
pico_enable_stdio_uart(${ProjectName} 0)
