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

    public slots:
        void startData(const char *port);
        void stopData();

    signals:
        void newData(const QString *data);
        void error(const std::string error);

    private:
        QString m_data[4];
        bool m_quit;

        SerialPort m_serial;
        Interpreter m_interpret;
};
