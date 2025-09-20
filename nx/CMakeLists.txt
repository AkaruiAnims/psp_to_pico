cmake_minimum_required(VERSION 3.13)
project(nx_to_pico)

# Enable C++17 (or whatever you prefer)
set(CMAKE_CXX_STANDARD 17)

# Find your source files
set(SOURCES src/main.cpp)

# Create the executable
add_executable(nx_to_pico ${SOURCES})

# Link against libnx
target_link_libraries(nx_to_pico nx)

# Add a post-build command to generate the .nro automatically
add_custom_command(TARGET nx_to_pico POST_BUILD
    COMMAND ${DEVKITPRO}/tools/bin/elf2nro $<TARGET_FILE:nx_to_pico> ${CMAKE_CURRENT_BINARY_DIR}/nx_to_pico.nro
    COMMENT "Generating nx_to_pico.nro from main_nx.elf"
)
