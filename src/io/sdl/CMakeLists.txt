message("-- Linking SDL")
add_library(SDL2 SDL2d.dll)
set_target_properties(SDL2 PROPERTIES LINKER_LANGUAGE CXX)