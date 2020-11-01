cmake_minimum_required(VERSION "3.15.3")
project("MultimeterMod")

add_executable("${PROJECT_NAME}" "src/main.cpp" "src/SerialPort.cpp" "src/Interpreter.cpp")

install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
install(FILES "main.cpp" DESTINATION src)
