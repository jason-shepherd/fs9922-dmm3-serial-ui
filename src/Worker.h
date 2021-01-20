#pragma once

#include <QObject>
#include <string>
#include <vector>

#include "SerialPort.h"
#include "Interpreter.h"

class Worker : public QObject {
    Q_OBJECT

    public slots:
        void startPort(const QString port);
        void stopPort();
        void getData();
        void refreshActivePorts();

    signals:
        void newData(const QString *data);
        void error(const std::string error);
        void refreshedActivePorts(const QStringList ports);
        void portStatus(const QString status);

    private:
        QString m_data[4];
        SerialPort m_serial;
        Interpreter m_interpret;
};
