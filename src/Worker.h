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
        void refreshedActivePorts(const QStringList ports);
        void error(const QString error);
        void connected();
        void disconnected();

    private:
        QString m_data[4];
        SerialPort m_serial;
        Interpreter m_interpret;
        bool m_running = false;
};
