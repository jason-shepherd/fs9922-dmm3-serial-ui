#pragma once

#include <QObject>
#include <QTimer>
#include <string>
#include <vector>

#include "SerialPort.h"
#include "Interpreter.h"

class Worker : public QObject {
    Q_OBJECT

    public:
        Worker();
        ~Worker();

    public slots:
        void startData(const char *port);
        void stopData();
        void refreshActivePorts();

    private slots:
        void getData();

    signals:
        void newData(const QString *data);
        void error(const std::string error);
        void refreshedActivePorts(const QStringList ports);

    private:
        char *m_port;
        QString m_data[4];
        QTimer *m_timer;
        SerialPort m_serial;
        Interpreter m_interpret;
};
