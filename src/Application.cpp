#include "Application.h"
#include "./ui_application.h"

Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Application)
{
    ui->setupUi(this);

    workerThread = new QThread;
    worker = new Worker();
    worker->moveToThread(workerThread);

    connect(this, &Application::startPort, worker, &Worker::startPort, Qt::QueuedConnection);
    connect(worker, &Worker::newData, this, &Application::showData, Qt::QueuedConnection);
    connect(this, &Application::stopPort, worker, &Worker::stopPort, Qt::QueuedConnection);

    connect(this, &Application::refreshPortList, worker, &Worker::refreshActivePorts, Qt::QueuedConnection);
    connect(worker, &Worker::refreshedActivePorts, this, &Application::updateActivePorts, Qt::QueuedConnection);

    connect(ui->refreshButton, &QPushButton::pressed, worker, &Worker::refreshActivePorts, Qt::QueuedConnection);
    connect(ui->connectButton, &QPushButton::pressed, this, &Application::togglePortConnection, Qt::QueuedConnection);
    workerThread->start();

    timer = new QTimer();
    connect(timer, &QTimer::timeout, worker, &Worker::getData, Qt::QueuedConnection);

    emit refreshPortList();
}

Application::~Application()
{
    stopData();
    workerThread->quit();
    workerThread->wait();
    delete ui;
}

void Application::startData() {
    std::string currentPort = ui->selectPort->currentText().toStdString();
    emit startPort(currentPort.c_str());
    timer->start(25);
    ui->connectButton->setText("Disconnect");
    isPortConnected = true;
}

void Application::stopData() {
    timer->stop();
    emit stopPort();
    ui->connectButton->setText("Connect");
    isPortConnected = false;
}

void Application::showData(const QString *data) {
   ui->dataLabel->setText(data[0]); 
   ui->voltModeLabel->setText(data[1]); 
   ui->modeLabel->setText(data[2]); 
}

void Application::togglePortConnection() {
    if(!isPortConnected) {
        startData();
    } else {
        stopData();
    }
}

void Application::updateActivePorts(const QStringList ports) {
    ui->selectPort->clear();
    for(int i = 0; i < ports.size(); i++)
        ui->selectPort->addItem(ports[i]);
}
