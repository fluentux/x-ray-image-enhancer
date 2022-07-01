find_package(OpenCV REQUIRED HINTS C:/opencv)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(imagestoring SHARED
    imagereader.h
    imagereaderexception.h
    imagereader.cpp
    imagewriter.h
    imagewriterexception.h
    imagewriter.cpp
)

set_target_properties(imagestoring PROPERTIES PUBLIC_HEADER imagereader.h)

target_link_libraries(imagestoring PRIVATE ${OpenCV_LIBS} imaging)
target_include_directories(imagestoring INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
