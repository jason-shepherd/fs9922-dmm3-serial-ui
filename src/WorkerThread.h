#pragma once

#include <string>
#include <vector>
#include <QThread>
#include <QThread>

#include "SerialPort.h"
#include "Interpreter.h"

class WorkerThead : public QThread {
    Q_OBJECT
    void run() override {
        std::vector<std::string> data;
        data.resize(4);
        SerialPort serial;
        serial.open("COM4", 2400, 8, NOPARITY);
        std::cout << serial.isOpen() << std::endl;

        Interpreter interpret;
        
        char byte;
        while(true) {
            serial.read(*byte);
            interpret.update(byte);

            std::string dataString = interpret.getData();
            if(interpret.getPoint() != 0)
                dataString.insert(interpret.getPoint(), ".");
            if(!interpret.getPositive())
                dataString = "-" + dataString;
            dataString += interpret.getPrefix() + interpret.getUnit();

            data[0] = dataString;
            data[1] = interpret.getUnit();
            data[2] = interpret.getVoltMode();
            data[3] = interpret.getMode();

            emit resultReady(data);
        }
    }
signals:
    void resultReady(const std::vector<std::string> &data) 
};
