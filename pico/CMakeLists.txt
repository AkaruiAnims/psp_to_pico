cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w)

# Include the Pico SDK
include(pico_sdk_import.cmake)

# Project configuration
project(sub_pico C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Initialize the Pico SDK
pico_sdk_init()

# Create the executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Enable Wi-Fi support on the Raspberry Pi Pico W
target_link_libraries(${PROJECT_NAME} pico_stdlib 
  hardware_pwm
	hardware_gpio
	pico_stdlib
	pico_cyw43_arch_none
  pico_multicore
  pico_lwip
)

# Enable USB and UART (optional)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

# Allow extra outputs (e.g., UF2 files for flashing)
pico_add_extra_outputs(${PROJECT_NAME})

