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

    connect(this, &Application::startData, worker, &Worker::startData);
    connect(worker, &Worker::newData, this, &Application::showData);
    connect(ui->logButton, &QPushButton::pressed, worker, &Worker::stopData);

    connect(this, &Application::refreshPortList, worker, &Worker::refreshActivePorts);
    connect(worker, &Worker::refreshedActivePorts, this, &Application::updateActivePorts);

    connect(ui->refreshButton, &QPushButton::pressed, worker, &Worker::refreshActivePorts);
    connect(ui->connectButton, &QPushButton::pressed, this, &Application::connectToPort);
    workerThread->start();
    emit refreshPortList();
}

Application::~Application()
{
    emit stopData();
    workerThread->quit();
    workerThread->wait();
    delete ui;
}

void Application::showData(const QString *data) {
   ui->dataLabel->setText(data[0]); 
   ui->voltModeLabel->setText(data[1]); 
   ui->modeLabel->setText(data[2]); 
}

void Application::connectToPort() {
    std::string port = ui->selectPort->currentText().toStdString();
    emit startData(port.c_str());
}

void Application::updateActivePorts(const QStringList ports) {
    ui->selectPort->clear();
    for(int i = 0; i < ports.size(); i++)
        ui->selectPort->addItem(ports[i]);
}
