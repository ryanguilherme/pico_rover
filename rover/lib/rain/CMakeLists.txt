add_library(rain
        rain.h
        rain.c
)

target_link_libraries(rain
        pico_stdlib
)

target_include_directories(rain PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
