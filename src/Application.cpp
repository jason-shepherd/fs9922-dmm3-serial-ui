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
    workerThread->start();
    emit startData("COM5");
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
