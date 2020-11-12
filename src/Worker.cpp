#include "Worker.h"

Worker::Worker() {
   m_data.resize(3);
   m_quit = false;
}

void Worker::startData(const char *port) {
    if(m_serial.isOpen())
        m_serial.close();
    m_serial.open(port, 2400, 8, NOPARITY);
    m_interpret.reset();
    
    char byte;
    while(!m_quit) {
        m_serial.read(&byte);
        m_interpret.update(byte);

        std::string dataString = m_interpret.getData();
        if(m_interpret.getPoint() != 0)
            dataString.insert(m_interpret.getPoint(), ".");
        if(!m_interpret.getPositive())
            dataString = "-" + dataString;
        dataString += m_interpret.getPrefix() + m_interpret.getUnit();
        m_data[0] = QString::fromStdString(dataString);

        m_data[1] = QString::fromStdString(m_interpret.getVoltMode());
        m_data[2] = QString::fromStdString(m_interpret.getMode());
        emit newData(m_data);
    }
}

void Worker::stopData() {
    m_serial.close();
    m_interpret.reset();
    m_quit = true;
}
