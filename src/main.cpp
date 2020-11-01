#include <windows.h>

#include <iostream>

#include "SerialPort.h"
#include "Interpreter.h"

int main() {
    char byte;
    SerialPort serial;
    serial.open("COM3", 2400, 8, NOPARITY);
    std::cout << serial.isOpen() << std::endl;
    
    serial.flush();
    Interpreter interpret;
    while(true) {
        serial.read(&byte);
        interpret.update(byte);
    }
}
