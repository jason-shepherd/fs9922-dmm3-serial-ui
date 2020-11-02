#include "Interpreter.h"

//TODO seperate out SB1-4 interpretation :)
void Interpreter::update(char byte) {
    m_byteString[m_index] = byte;

    m_positive = m_byteString[0] == '+';
    for(int i = 0; i < 4; i++)
        m_data[i] = m_byteString[i+1];
    m_point = (int)m_byteString[6] - 48;

    switch((int)m_byteString[10]) {
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
    
    m_index++; 

    if((int)byte == 10) {
        m_index = 0;
        display();
    }
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
