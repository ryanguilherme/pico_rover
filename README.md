# Analytic Rover
Analytic Rover that walks autonomally and collect multiple data like humidity, temperature, luminosity and display in a WEB host in real-time using FreeRTOS and a Raspberry Pi Pico with a RP2040 processor.

## Components
| Component            | Description                                                   | Image                      |
|----------------------|---------------------------------------------------------------|----------------------------|
| **Raspberry Pi Pico**| A compact and powerful microcontroller that serves as the brain of the rover. | ![Raspberry Pi Pico](/assets/img/rpi_pico.jpg) |
| **FreeRTOS**         | A real-time operating system that efficiently manages the rover's tasks. | ![FreeRTOS](/assets/img/freertos_logo.png) |
| **L298N**            | A motor driver used to control the direction and speed of DC motors. | ![L298N](/assets/img/l298n.jpg) |
| **DC Motors 6V**     | Actuators that allow the rover to move.                      | ![DC Motors](/assets/img/dc_motors.png) |
| **DHT11**            | A sensor that measures temperature and humidity.             | ![DHT11](/assets/img/dht11.jpg) |
| **LDR (Light Dependent Resistor)** | A light sensor that turns on the rover's headlights in low-light conditions. | ![LDR](/assets/img/ldr.png) |
| **Rain Sensor**      | A sensor that detects the presence of water, simulating adverse weather conditions. | ![Rain Sensor](/assets/img/rain_sensor.png) |
## Features

The rover has several features that make it suitable for simulation and exploration that make them possible of wandering, collect data and expose in a web server:

- **Movement Control**: Uses the L298N to manage DC motors, allowing the rover to move in different directions and adjust its speed.
- **Climate Monitoring**: The DHT11 provides information on temperature and humidity, which can be used to adjust the rover's behavior.
- **Lighting**: The LDR monitors ambient light levels and turns on the rover's headlights when the light is low, ensuring visibility in dark environments.
- **Rain Detection**: The rain sensor detects water presence, allowing the rover to react to rain or simulate wet conditions.
- **Web Server**: The system read all data processed of sensors and exposed that informations in a web server for sample visualization and analysis of datas.

## Project Structure

The project is organized as follows:

- **Root Directory**:
  - `README.md`: This file, containing project information and instructions.
  - `rover`: Main project directory containing the source code and libraries.

- **Inside the `rover` Directory**:
  - `lib`: Contains libraries for each sensor. Each sensor library includes:
    - `sensor_name.c`: Source file with the implementation of the sensor.
    - `sensor_name.h`: Header file with the sensor's interface.
    - `CMakeLists.txt`: CMake configuration for building the sensor library.
  - `src`: Contains the main application source files, including:
    - `main.c`: Main source file where the application starts.
    - `FreeRTOSConfig.h`: FreeRTOS configuration file.
    - `CMakeLists.txt`: CMake configuration for building the main application.
  - `CMakeLists.txt`: General CMake configuration for the entire project.

```plaintext
.
├── README.md
└── rover
    ├── CMakeLists.txt
    ├── lib
    │   ├── dht11
    │   │   ├── dht11.c
    │   │   ├── dht11.h
    │   │   └── CMakeLists.txt
    │   ├── ldr
    │   │   ├── ldr.c
    │   │   ├── ldr.h
    │   │   └── CMakeLists.txt
    │   ├── rain_sensor
    │   │   ├── rain_sensor.c
    │   │   ├── rain_sensor.h
    │   │   └── CMakeLists.txt
    │   └── motor_control
    │       ├── motor_control.c
    │       ├── motor_control.h
    │       └── CMakeLists.txt
    └── src
        ├── main.c
        ├── FreeRTOSConfig.h
        └── CMakeLists.txt

```

## Requirements

To assemble and use the rover, you will need the following hardware and software components:

- **Hardware**:
  - Raspberry Pi Pico
  - L298N
  - DC Motors 6V
  - DHT11
  - LDR
  - Rain Sensor
  - Wires and connectors
  - Power supply

- **Software**:
  - For compiling the code, you need a Cmake and Make version installing in your machine and a crosscompiler for arm processor, where the most common is the arm-none-eabi cross compiler. 
  - So, for linux users, write in your console:
  ```bash
    sudo apt install cmake make
  ```
  - For installing the crosscompiler, you need access the arm site and installing a version is the arm-none-eabi

## Usage

To use the rover:

1. **Compilation and Upload**:
   - Compile the code using the appropriate compiler for the Raspberry Pi Pico.
   ```bash
    cd src
    mkdir build
    cmake ..
    make
   ```
   - Upload the code to the Raspberry Pi Pico. For this, you need to press the bootsel of your Raspberry Pi Pico and identificate what serial gate she connect. In general, is `/dev/ttyACM0`. After this, write in your console (inside build paste):
   ```bash
    cp rover.ufc /media/seu_usuario/RPI-RP2/
   ```

## Installation

Setting up the hardware and software is a straightforward process:

1. **Hardware Setup**:
   - Connect the DC motors to the L298N motor driver.
   - Connect the L298N to the Raspberry Pi Pico.
   - Connect the sensors (DHT11, LDR, and rain sensor) to the appropriate pins on the Raspberry Pi Pico.

2. **Software Setup**:
   - Follow the steps provided by [usage](#usage) section

## Contributions

Contributions are welcome! Feel free to open issues or submit pull requests for improvements to the project.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.
