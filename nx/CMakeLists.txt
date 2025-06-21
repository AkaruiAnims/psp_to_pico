# cmake_minimum_required(VERSION 3.10)
# project(main_nx)
#
# # 1. Force Switch toolchain (absolute path)
# set(CMAKE_TOOLCHAIN_FILE "/opt/devkitpro/cmake/switch.cmake")
#
# # 2. Basic project setup
# set(APP_NAME "main_nx")
# add_executable(${APP_NAME} src/main.cpp)
#
# # 3. Critical Switch-specific settings
# target_include_directories(${APP_NAME} PRIVATE
#     /opt/devkitpro/libnx/include
#     /opt/devkitpro/portlibs/switch/include
# )
#
# target_link_directories(${APP_NAME} PRIVATE
#     /opt/devkitpro/portlibs/switch/lib
# )
#
# target_link_libraries(${APP_NAME} PRIVATE nx)
#
# # 4. NRO conversion
# find_program(ELF2NRO elf2nro)
# if(ELF2NRO)
#     add_custom_command(TARGET ${APP_NAME} POST_BUILD
#         COMMAND ${ELF2NRO} $<TARGET_FILE:${APP_NAME}> ${APP_NAME}.nro
#         COMMENT "Building NRO"
#     )
# endif()
#
cmake_minimum_required(VERSION 3.10)
project(main_nx)

# ABSOLUTE PATH - NO VARIABLES
set(CMAKE_TOOLCHAIN_FILE "/opt/devkitpro/cmake/switch.cmake")

# Critical compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/devkitpro/devkitA64/aarch64-none-elf/include")

# Simple executable
add_executable(main_nx src/main.cpp)

# Required include paths
target_include_directories(main_nx PRIVATE
    /opt/devkitpro/libnx/include
    /opt/devkitpro/devkitA64/aarch64-none-elf/include
    /opt/devkitpro/devkitA64/lib/gcc/aarch64-none-elf/*/include
)

target_link_libraries(main_nx PRIVATE nx)
