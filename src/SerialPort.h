#pragma once

#include <windows.h>
#include <vector>
#include <string>

class SerialPort {
    private:
        HANDLE m_handler;
        bool m_connected;
        COMSTAT m_status;
        DCB m_config;
    public:
        SerialPort(const char* portName, DWORD baudRate, BYTE byteSize, BYTE parity);
        SerialPort() {};
        ~SerialPort();
        bool open(const char* portName, DWORD baudRate, BYTE byteSize, BYTE parity);
        bool close();
        bool read(const char* byte);
        bool flush();
        bool isOpen();
        static const std::vector<std::string> getActivePorts();
};
