# Definir o mínimo requerido do CMake
cmake_minimum_required(VERSION 3.13)

# Incluir o SDK do Raspberry Pi Pico
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Definir o nome do projeto
project(mpu6050_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Inicializar o SDK do Pico
pico_sdk_init()

# Adicionar os arquivos de origem ao projeto
add_executable(mpu6050_main
    main.c
    mpu6050.c
)

# Incluir diretórios de cabeçalhos
target_include_directories(mpu6050_main PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Vincular as bibliotecas necessárias
target_link_libraries(mpu6050_main
    pico_stdlib        # Biblioteca padrão do Pico (para GPIO, I2C, etc)
    hardware_i2c       # Biblioteca de hardware I2C
)

# Habilitar a saída de USB e UART padrão para debug
pico_enable_stdio_usb(mpu6050_main 1)
pico_enable_stdio_uart(mpu6050_main 1)

# Criar o arquivo UF2 para upload na Raspberry Pi Pico
pico_add_extra_outputs(mpu6050_main)
