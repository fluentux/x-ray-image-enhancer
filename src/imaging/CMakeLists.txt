add_library(imaging SHARED
    xrayimage.h
    xrayimage.cpp
)

set_target_properties(imaging PROPERTIES PUBLIC_HEADER xrayimage.h)

target_include_directories(imaging INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
