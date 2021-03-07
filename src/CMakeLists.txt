add_library(chip8 chip8.cpp)

add_subdirectory(io)
target_link_libraries(chip8 io)