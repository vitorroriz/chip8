find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
message("include dir " ${SDL2_INCLUDE_DIRS})
#add_subdirectory(sdl)

add_library(io  io.cpp )
target_link_libraries(io ${SDL2_LIBRARIES})
#target_link_libraries(io SDL2)
