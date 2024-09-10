add_library(movement
	movement.h
	movement.c
)

target_link_libraries(movement
	pico_stdlib
)

target_include_directories(movement PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
