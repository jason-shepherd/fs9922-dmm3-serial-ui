#pragma once

#include <QMainWindow>
#include <QThread>
#include <QTimer>

#include "Worker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Application; }
QT_END_NAMESPACE

class Application : public QMainWindow
{
    Q_OBJECT

    public:
        Application(QWidget *parent = nullptr);
        ~Application();
        void startData();
        void stopData();

    public slots:
        void showData(const QString *data);
        void togglePortConnection();
        void updateActivePorts(const QStringList ports);
        void updatePortStatus(const QString status);

    signals:
        void startPort(const QString port);
        void stopPort();
        void refreshPortList();
    
    private:
        Ui::Application *ui;
        QThread *workerThread;
        Worker *worker;
        bool isPortConnected = false;
};
