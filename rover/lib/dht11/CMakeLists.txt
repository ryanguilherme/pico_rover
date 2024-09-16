add_library(dht11
	dht11.h
	dht11.c
)

target_link_libraries(dht11
	pico_stdlib
)

target_include_directories(dht11 PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

pico_enable_stdio_usb(${ProjectName} 1)
pico_enable_stdio_uart(${ProjectName} 0)
