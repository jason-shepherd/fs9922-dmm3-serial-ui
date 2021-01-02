#pragma once

#include <string>
#include <vector>
#include <iostream>

#define CHECK_BIT(var, pos) (((var)>>(pos)) & 1)

class Interpreter {
    private:
        int m_index = 0;
        char m_byteString[14];

        bool m_positive;
        char m_data[4];
        int m_point = 0;
        std::string m_mode = "AUTO";
        std::string m_unit = "V";
        std::string m_voltMode = "DC";
        std::string m_prefix = "";
    public:
        Interpreter::Interpreter();

        void update(char byte);
        void display();
        void reset();

        const bool getPositive();
        const int getPoint();
        const std::string getData();
        const std::string getMode();
        const std::string getUnit();
        const std::string getPrefix();
        const std::string getVoltMode();
};
