#include "SerialPort.h"

SerialPort::SerialPort(const char* portName, DWORD baudRate, BYTE byteSize, BYTE parity) {
    open(portName, baudRate, byteSize, parity);
}

SerialPort::~SerialPort() {
    close();
}

// opens and configures serial port with specified parameters
bool SerialPort::open(const char* portName, DWORD baudRate, BYTE byteSize, BYTE parity) {
    // open COM port as a file
    m_handler = CreateFile(portName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if(m_handler == INVALID_HANDLE_VALUE) {
        return false;
    }

    // configure COM port
    m_config = {0};
    m_config.DCBlength = sizeof(DCB);

    if(!GetCommState(m_handler, &m_config)) {
        return false;
    }

    m_config.BaudRate = baudRate;
    m_config.ByteSize = byteSize;
    m_config.Parity = parity;

    if(!SetCommState(m_handler, &m_config)) {
        return false;
    } else {
        return true;
    }
    return true;
}

// close serial port
bool SerialPort::close() {
    return CloseHandle(m_handler);
}

// read a single byte from the serial port
bool SerialPort::read(const char* byte) {
    DWORD read{};

    if(!ReadFile(m_handler, (void*) byte, 1, &read, NULL)) {
        return false;
    }
    return read;
}

// flush the serial data buffer
bool SerialPort::flush() {
    return PurgeComm(m_handler, PURGE_TXCLEAR);
}

// returns true if the port is open
bool SerialPort::isOpen() {
    return ClearCommError(m_handler, NULL, &m_status);
}

// returns a vector of active serial ports
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
