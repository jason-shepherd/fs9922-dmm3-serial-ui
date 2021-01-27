#pragma once

#include <QMainWindow>
#include <QThread>
#include <QFileDialog>
#include <QDebug>

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

    public slots:
        void showData(const QString *data);
        void togglePortConnection();
        void updateActivePorts(const QStringList ports);
        void portError(const QString error);
        void portConnected();
        void portDisconnected();
        void toggleDatalog();

    signals:
        void startPort(const QString port);
        void stopPort();
        void refreshPortList();
        void startDatalog();
        void stopDatalog(const QString filePath);
    
    private:
        Ui::Application *ui;
        QThread *workerThread;
        Worker *worker;
        bool isPortConnected = false;
        bool isDatalogging = false;
};
