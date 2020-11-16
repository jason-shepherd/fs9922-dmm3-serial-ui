#include "Interpreter.h"

Interpreter::Interpreter() {
    for(int i = 0; i < 4; i++)
        m_data[i] = 0;
}

void Interpreter::update(char byte) {
    m_byteString[m_index] = byte;

    //data
    m_positive = m_byteString[0] == '+';
    for(int i = 0; i < 4; i++)
        m_data[i] = m_byteString[i+1];
    m_point = (int)m_byteString[6] - 48;
    if(m_point == 4)
        m_point = 3;

    //sb bytes interpretation, not pretty but better than nothing
    //mode
    if(CHECK_BIT(m_byteString[7], 2))
        m_mode = "REL";
    else if(CHECK_BIT(m_byteString[7], 5))
        m_mode = "AUTO";
    else if(CHECK_BIT(m_byteString[8], 5))
        m_mode = "MAX";
    else if(CHECK_BIT(m_byteString[8], 4))
        m_mode = "MIN";
    else if(CHECK_BIT(m_byteString[9], 3))
        m_mode = "Beep";
    else if(CHECK_BIT(m_byteString[9], 2))
        m_mode = "Diode";
    else if(CHECK_BIT(m_byteString[9], 1))
        m_mode = "%";
    else
        m_mode = "";

    //voltMode
    if(CHECK_BIT(m_byteString[7], 3))
        m_voltMode = "AC";
    else if(CHECK_BIT(m_byteString[7], 4))
        m_voltMode = "DC";
    else
        m_voltMode = "";

    //prefix
    if(CHECK_BIT(m_byteString[8], 1))
        m_prefix = 'n';
    else if(CHECK_BIT(m_byteString[9], 7))
            m_prefix = "μ";
    else if(CHECK_BIT(m_byteString[9], 6))
            m_prefix = "m";
    else if(CHECK_BIT(m_byteString[9], 5))
            m_prefix = "k";
    else if(CHECK_BIT(m_byteString[9], 4))
            m_prefix = "M";
    else
        m_prefix = "";

    //unit 
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
    }
}

void Interpreter::display() {
    if(!m_positive)
        std::cout << "-";
    if(m_data[0] == '?')
        std::cout << "0L" << " " << m_unit << " " << m_mode << " " << m_voltMode << std::endl;
    else {
        for(int i = 0; i < 4; i++) {
            if(i == m_point && m_point != 0)
                std::cout << '.';
            std::cout << m_data[i];
        }
        std::cout << " " << m_prefix << m_unit << " " << m_mode << " " << m_voltMode << std::endl;
    }
}

void Interpreter::reset() {
    m_index = 0;
}

const bool Interpreter::getPositive() {
    return m_positive;
}

const int Interpreter::getPoint() {
    return m_point;
}

const std::string Interpreter::getData() {
    return m_data;
}

const std::string Interpreter::getMode() {
    return m_mode;
}

const std::string Interpreter::getUnit() {
    return m_unit;
}

const std::string Interpreter::getPrefix() {
    return m_prefix;
}

const std::string Interpreter::getVoltMode() {
    return m_voltMode;
}
