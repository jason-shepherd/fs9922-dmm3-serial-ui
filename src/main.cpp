#include <windows.h>
#include <iostream>
#include <QApplication>

#include "Application.h"

#include "SerialPort.h"
#include "Interpreter.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Application window;
    window.show();
    return a.exec();

    //SerialPort serial;
    //serial.open("COM5", 2400, 8, NOPARITY);
    //Interpreter interpret;
    //
    //char byte;
    //serial.flush();
    //while(true) {
    //    if(serial.read(&byte)) {
    //        interpret.update(byte);
    //
    //        std::string dataString;
    //        dataString.resize(5);
    //
    //        if(interpret.getPoint() != 0) {
    //            dataString.resize(5);
    //            std::string rawData = interpret.getData();
    //            for(int i = 0; i < 4; i++) {
    //                if(interpret.getPoint() == i)
    //                    dataString += '.';
    //                dataString += rawData[i];
    //            }
    //        }
    //
    //        if(!interpret.getPositive())
    //           dataString = "-" + dataString;
    //        dataString += interpret.getPrefix() + interpret.getUnit();
    //
    //        std::cout << dataString << interpret.getVoltMode() << interpret.getMode() << std::endl;
    //    }
    //}
}
