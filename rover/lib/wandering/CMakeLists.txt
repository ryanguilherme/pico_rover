add_library(wandering
	wandering.h
	wandering.c
)

target_link_libraries(wandering
	pico_stdlib
	movement
	ultrasonic
)

target_include_directories(movement PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
