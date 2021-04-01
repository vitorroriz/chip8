add_library(chip8 chip8.cpp)

add_subdirectory(io)
add_subdirectory(tools)

target_link_libraries(chip8 io tools)