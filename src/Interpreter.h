#pragma once

#include <string>
#include <iostream>

class Interpreter {
    private:
        int m_index = 0;
        bool m_positive;
        char m_data[4];
        int m_point;
        std::string m_unit = "";
    public:
        void update(char byte);
        void display();
};
