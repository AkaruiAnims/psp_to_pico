cmake_minimum_required(VERSION 3.13)
# commented stuff is for wifi. DO ON WIFI BRANCH
set(PICO_BOARD pico_w) 
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(pico C CXX)
pico_sdk_init()

# create pico executable
add_executable(pico
  src/main.cpp
)

# Driver Headers
target_include_directories(pico PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Links for the lib
target_link_libraries(pico PRIVATE 
  pico_stdlib 
  pico_cyw43_arch_lwip_poll
  cyw43_driver
  hardware_i2c
  hardware_gpio 
  hardware_timer
) 

# Extra Pico stuff
pico_add_extra_outputs(pico)
pico_enable_stdio_usb(pico 1)
pico_enable_stdio_uart(pico 0)
