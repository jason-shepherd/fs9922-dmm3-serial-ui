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
    connect(ui->refreshButton, &QPushButton::pressed, worker, &Worker::refreshActivePorts);
    connect(this, &Application::refreshPortList, worker, &Worker::refreshActivePorts);
    connect(worker, &Worker::refreshedActivePorts, this, &Application::updateActivePorts);
    workerThread->start();
    emit refreshPortList();
    //emit startData("COM15");
}

Application::~Application()
{
    delete worker;
    workerThread->quit();
    workerThread->wait();
    delete ui;
}

void Application::showData(const QString *data) {
   ui->dataLabel->setText(data[0]); 
   ui->voltModeLabel->setText(data[1]); 
   ui->modeLabel->setText(data[2]); 
}

void Application::updateActivePorts(const QStringList ports) {
    ui->selectPort->clear();
    for(int i = 0; i < ports.size(); i++)
        ui->selectPort->addItem(ports[i]);
}
