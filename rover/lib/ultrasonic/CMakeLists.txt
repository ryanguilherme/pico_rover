add_library(ultrasonic
        ultrasonic.h
        ultrasonic.c
)

target_link_libraries(ultrasonic
        pico_stdlib
)

target_include_directories(movement PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
