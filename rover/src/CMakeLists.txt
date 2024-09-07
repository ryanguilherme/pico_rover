add_executable(${ProjectName}
    main.c
)

target_include_directories(${ProjectName} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${ProjectName} 
    pico_stdlib 
    FreeRTOS-Kernel-Heap4 
    pico_cyw43_arch_none
    )

pico_enable_stdio_usb(${ProjectName} 1)
pico_enable_stdio_usb(${ProjectName} 0)

pico_add_extra_outputs(${ProjectName})
