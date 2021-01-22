#include "Worker.h"

// connect to port using SerialPort class
void Worker::startPort(const QString port) {
    std::string temp = port.toStdString();
    const char* newPort = temp.c_str();
    if(m_serial.isOpen())
        m_serial.close();
    if(m_serial.open(newPort, 2400, 8, NOPARITY)) {
        m_interpret.reset();
        m_serial.flush();
        m_running = true;
        emit portStatus(port + " is connected and configured.");
    } else {
        emit portStatus("Could not connect to " + port + ".");
    }
}

// disconnect from the port
void Worker::stopPort() {
    m_running = false;
    m_serial.close();
    m_interpret.reset();
    emit portStatus("Serial has been disconnected.");
}

// gets an list of active lists from SerialPort and sends it to the ui thread
void Worker::refreshActivePorts() {
    std::vector<std::string> ports = m_serial.getActivePorts();
    QStringList newPorts;
    for(int i = 0; i < ports.size(); i++)
        newPorts.append(QString::fromStdString(ports[i]));
    emit refreshedActivePorts(newPorts);
}

// reads serial, sends it to interpreter, formats for ui, then sends to application
// also calls itself using invokeMethod, so it is constantly running without blocking the event loop
// will only read\interpret serial if m_running is true
void Worker::getData() {
    if(m_running) {
        char byte = '0';
        if(m_serial.read(&byte)) {
            m_interpret.update(byte);
            
            // prepare data for the ui
            std::string dataString;
            if(m_interpret.getPoint() != 0) {
                std::string rawData = m_interpret.getData();
                for(int i = 0; i < 4; i++) {
                    if(m_interpret.getPoint() == i)
                        dataString.append(".");
                   dataString.push_back(rawData[i]);
                }
            } else {
                dataString = m_interpret.getData();
            }
        
            dataString += m_interpret.getPrefix() + m_interpret.getUnit();
            if(m_interpret.getData()[0] == '?')
                dataString = "0L " + m_interpret.getUnit();
            if(!m_interpret.getPositive())
               dataString = "-" + dataString;
        
            m_data[0] = QString::fromStdString(dataString);
        
            m_data[1] = QString::fromStdString(m_interpret.getVoltMode());
            m_data[2] = QString::fromStdString(m_interpret.getMode());
            emit newData(m_data);
        }
    }
    // calls itself using a signal, so the event loop can process other signals
    QMetaObject::invokeMethod(this, "getData", Qt::QueuedConnection);
}
