add_library(dht11
	dht11.h
	dht11.c
)

target_link_libraries(ldr
	pico_stdlib
)

target_include_directories(dht11 PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
