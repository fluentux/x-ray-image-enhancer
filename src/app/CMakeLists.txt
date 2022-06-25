set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.3 REQUIRED COMPONENTS Quick Gui REQUIRED)
qt_standard_project_setup()

qt_add_executable(xrayimageenhancer
    imageprovider.h
    imageprovider.cpp
    imageitem.h
    mainmodel.h
    mainmodel.cpp
    main.cpp
)

qt_add_qml_module(xrayimageenhancer
    URI XrayImageEnhancer
    VERSION 1.0
    QML_FILES
        main.qml
    SOURCES
        imagelistmodel.h
        imagelistmodel.cpp
    RESOURCES
)

target_link_libraries(xrayimageenhancer PRIVATE Qt6::Gui Qt6::Quick imaging imageprocessing imagestoring)

set_target_properties(xrayimageenhancer PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
