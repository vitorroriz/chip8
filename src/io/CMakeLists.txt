find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
message("include dir " ${SDL2_INCLUDE_DIRS})
#add_subdirectory(sdl)

add_library(io INTERFACE)
target_include_directories(io INTERFACE .)
set_target_properties(io PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(io INTERFACE ${SDL2_LIBRARIES})
#target_link_libraries(io SDL2)
