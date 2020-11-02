#pragma once

#include <string>
#include <iostream>

class Interpreter {
    private:
        int m_index = 0;
        char m_byteString[14];

        bool m_positive;
        char m_data[4];
        int m_point = 0;
        std::string m_unit = "";
        std::string m_mode = "";
    public:
        void update(char byte);
        void display();
};
