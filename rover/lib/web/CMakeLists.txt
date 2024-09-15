add_library(web
	cgi.h
	ssi.h
	web.h
)

target_link_libraries(web
	pico_stdlib
    	pico_cyw43_arch_lwip_threadsafe_background
	pico_lwip_http
	hardware_adc
)

target_include_directories(web PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
