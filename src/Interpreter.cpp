#include "Interpreter.h"

void Interpreter::update(char byte) {
    if(byte == '+' || byte == '-') { 
        m_index = 0;
        m_positive = byte == '+';
        display();
    } else if(m_index < 5)
        m_data[m_index-1] = byte;
    else if(m_index == 6)
        m_point = (int)byte - 48;
    else if(m_index == 10) {
        switch((int)byte) {
            case -128:
                m_unit = 'V';
                break;
            case 64:
                m_unit = 'A';
                break;
            case 32:
                m_unit = "Ohms";
                break;
            case 16:
                m_unit = "hFe";
                break;
            case 8:
                m_unit = "Hz";
                break;
            case 4:
                m_unit = "F";
                break;
            case 2:
                m_unit = "C";
                break;
            case 1:
                m_unit = "F";
                break;
        }
    }
    m_index++;
}

void Interpreter::display() {
    if(!m_positive)
        std::cout << "-";
    if(m_data[0] == '?')
        std::cout << "0L";
    else {
        for(int i = 0; i < 4; i++) {
            if(i == m_point && m_point != 0)
                std::cout << '.';
            std::cout << m_data[i];
        }
    }
    std::cout << " " << m_unit << std::endl;
}
