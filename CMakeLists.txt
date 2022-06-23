cmake_minimum_required(VERSION 3.5)

project(XrayImageEnhancer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/imaging)
add_subdirectory(src/imagestoring)
add_subdirectory(src/imageprocessing)
add_subdirectory(src/app)

add_subdirectory(tests)
