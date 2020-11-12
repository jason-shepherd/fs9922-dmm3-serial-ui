cmake_minimum_required(VERSION 3.19)

project(MultimeterMod)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(EXECUTABLE_OUTPUT_PATH ./build)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EXECUTABLE_OUTPUT_PATH})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXECUTABLE_OUTPUT_PATH})
set(CMAKE_PREFIX_PATH "C:/Qt/5.9.9/msvc2017_64")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(MultimeterMod
    src/main.cpp
    src/Application.cpp
    src/application.ui
    src/SerialPort.cpp
    src/Interpreter.cpp
    src/Worker.cpp
)

target_link_libraries(MultimeterMod Qt5::Widgets)
