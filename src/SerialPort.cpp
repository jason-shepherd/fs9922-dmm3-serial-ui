#include "SerialPort.h"
#include <iostream>

SerialPort::SerialPort(const char* portName, DWORD baudRate, BYTE byteSize, BYTE parity) {
    open(portName, baudRate, byteSize, parity);
}

SerialPort::~SerialPort() {
    close();
}

bool SerialPort::open(const char* portName, DWORD baudRate, BYTE byteSize, BYTE parity) {
    //Open COM port as a file
    m_handler = CreateFile(portName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if(m_handler == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening " << portName << " port: " << GetLastError() << std::endl;
        return false;
    }

    //Configure COM port
    m_config = {0};
    m_config.DCBlength = sizeof(DCB);

    if(!GetCommState(m_handler, &m_config)) {
        std::cerr << "Could not get status of " << portName << ". Reason " << GetLastError() << std::endl;
        return false;
    }

    m_config.BaudRate = baudRate;
    m_config.ByteSize = byteSize;
    m_config.Parity = parity;

    if(!SetCommState(m_handler, &m_config)) {
        std::cerr << "Could not configure " << portName << ". Reason " << GetLastError() << std::endl;
        return false;
    } else {
        std::cout << portName << " has been opened and configured." << std::endl;
        return false;
    }
    return true;
}

bool SerialPort::close() {
    return CloseHandle(m_handler);
}

bool SerialPort::read(const char* byte) {
    DWORD read{};

    if(!ReadFile(m_handler, (void*) byte, 1, &read, NULL)) {
        std::cerr << "Could not read from COM port. Reason " << GetLastError() << std::endl;
        return false;
    }
    return read;
}

bool SerialPort::flush() {
    return PurgeComm(m_handler, PURGE_TXCLEAR);
}

bool SerialPort::isOpen() {
    return ClearCommError(m_handler, NULL, &m_status);
}

const std::vector<std::string> SerialPort::getActivePorts() {
    char lpTargetPath[5000];
    std::vector<std::string> foundPorts;

    for(int i = 0; i < 255; i++) {
        std::string port = "COM" + std::to_string(i);
        DWORD test = QueryDosDevice(port.c_str(), lpTargetPath, 5000);
        if(test != 0) {
            foundPorts.push_back(port);
        }
    }
    return foundPorts;
}
