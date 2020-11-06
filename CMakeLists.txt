cmake_minimum_required(VERSION 3.5)

project(MultimeterMod LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/5.9.9/mingw53_32/lib/cmake")
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(MultimeterMod
	src/main.cpp
	src/Application.cpp
	src/SerialPort.cpp
	src/Interpreter.cpp
	src/application.ui
)

target_link_libraries(MultimeterMod Qt5::Widgets)