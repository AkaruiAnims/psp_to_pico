#!/bin/bash
# build.sh - Build Nintendo Switch homebrew with devkitPro
# Make sure everything in installed properly! 
# read:https://devkitpro.org/wiki/devkitPro_pacman
# and fix any errors as they come

# Exit on any error
set -e

# Make sure build directory exists
mkdir -p build
cd build

# Run CMake with the Switch toolchain
cmake .. -DCMAKE_TOOLCHAIN_FILE=/opt/devkitpro/cmake/switch.cmake

# Build the project
make

echo "Build complete! ELF and NRO should be in the build/ folder."
