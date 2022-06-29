
#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost CONFIG HINTS C:/Boost REQUIRED COMPONENTS )

find_package(OpenCV REQUIRED HINTS C:/opencv)
include_directories(${OpenCV_INCLUDE_DIRS})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

add_library(imagestoring SHARED
    imagereader.h
    imagereaderexception.h
    imagereader.cpp
    imagewriter.h
    imagewriterexception.h
    imagewriter.cpp
)

set_target_properties(imagestoring PROPERTIES PUBLIC_HEADER imagereader.h)

target_link_libraries(imagestoring PRIVATE ${Boost_LIBRARIES} ${OpenCV_LIBS} imaging)
target_include_directories(imagestoring INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

