
find_package(OpenCV REQUIRED HINTS C:/opencv-build )
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(imageprocessing SHARED
    binning.h
    binning.cpp
)

set_target_properties(imageprocessing PROPERTIES PUBLIC_HEADER binning.h)

target_link_libraries(imageprocessing PRIVATE ${OpenCV_LIBS} imaging)
target_include_directories(imageprocessing INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
