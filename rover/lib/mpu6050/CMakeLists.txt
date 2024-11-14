add_library(mpu
	mpu6050.h
	mpu6050.c
)

target_link_libraries(mpu
	pico_stdlib
	hardware_i2c
)

target_include_directories(mpu PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

pico_enable_stdio_usb(${ProjectName} 1)
pico_enable_stdio_uart(${ProjectName} 0)
