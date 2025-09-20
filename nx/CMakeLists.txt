cmake_minimum_required(VERSION 3.13)
project(main_nx)

# Enable C++17 (or whatever you prefer)
set(CMAKE_CXX_STANDARD 17)

# Find your source files
set(SOURCES src/main.cpp)

# Create the executable
add_executable(main_nx ${SOURCES})

# Link against libnx
target_link_libraries(main_nx nx)

# Add a post-build command to generate the .nro automatically
add_custom_command(TARGET main_nx POST_BUILD
    COMMAND ${DEVKITPRO}/tools/bin/elf2nro $<TARGET_FILE:main_nx> ${CMAKE_CURRENT_BINARY_DIR}/main_nx.nro
    COMMENT "Generating main_nx.nro from main_nx.elf"
)
