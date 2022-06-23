find_package(Boost CONFIG HINTS C:/Boost REQUIRED COMPONENTS filesystem system unit_test_framework)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_executable(unittests
    unittests.cpp
)

target_link_libraries(unittests PRIVATE ${Boost_LIBRARIES} imaging imageprocessing)
enable_testing()
