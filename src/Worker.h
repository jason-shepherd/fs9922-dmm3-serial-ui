#pragma once

#include <QObject>
#include <string>
#include <vector>

#include "SerialPort.h"
#include "Interpreter.h"

class Worker : public QObject {
    Q_OBJECT

    public:
        Worker();
        ~Worker() { stopData(); }

    public slots:
        void startData(const char *port);
        void stopData();

    signals:
        void newData(const std::vector<QString> &data);
        void error(const std::string error);

    private:
        std::vector<QString> m_data;
        bool m_quit;

        SerialPort m_serial;
        Interpreter m_interpret;
};
