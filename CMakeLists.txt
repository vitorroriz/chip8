# CMakeList.txt : CMake project for chip8, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.18.0)

project ("chip8")
set(SRC "./src")

# Add source to this project's executable.
add_executable (chip8 "${SRC}/chip8.cpp" "${SRC}/chip8.h")

# TODO: Add tests and install targets if needed.
