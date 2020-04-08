cmake_minimum_required(VERSION 3.16)

# Set the project name
project(ARM_ISA_SIMULATOR)

# Enable testing
enable_testing()

# Add subdirectories
add_subdirectory (src)
add_subdirectory (UnitTests)