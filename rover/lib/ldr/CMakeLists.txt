add_library(ldr
	ldr.h
	ldr.c
)

target_link_libraries(ldr
	pico_stdlib
    hardware_adc
)

target_include_directories(ldr PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

pico_enable_stdio_usb(${ProjectName} 1)
pico_enable_stdio_uart(${ProjectName} 0)
