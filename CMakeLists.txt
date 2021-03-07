# CMakeList.txt : CMake project for chip8, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.18.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("chip8emu")
set(SRC "./src")

# Add source to this project's executable.
add_executable (app "src/main.cpp") 

add_subdirectory(SRC)

target_link_libraries(app chip8)

# TODO: Add tests and install targets if needed.
