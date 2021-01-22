#include "Application.h"
#include "./ui_application.h"

Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Application)
{
    ui->setupUi(this);
    
    //create thread for worker and move worker object to it
    workerThread = new QThread;
    worker = new Worker();
    worker->moveToThread(workerThread);

    // connect thread signals to start and delete worker
    connect(workerThread, &QThread::started, worker, &Worker::getData);
    connect(workerThread, &QThread::finished, worker, &Worker::deleteLater);

    // connect signals and slots that start and stop the worker's work
    connect(this, &Application::startPort, worker, &Worker::startPort);
    connect(this, &Application::stopPort, worker, &Worker::stopPort);
    connect(worker, &Worker::newData, this, &Application::showData);

    // connect signals that are used for getting active ports and the status of the current port
    connect(this, &Application::refreshPortList, worker, &Worker::refreshActivePorts, Qt::QueuedConnection);
    connect(worker, &Worker::refreshedActivePorts, this, &Application::updateActivePorts, Qt::QueuedConnection);
    connect(worker, &Worker::portStatus, this, &Application::updatePortStatus);

    connect(ui->refreshButton, &QPushButton::pressed, worker, &Worker::refreshActivePorts, Qt::QueuedConnection);
    connect(ui->connectButton, &QPushButton::pressed, this, &Application::togglePortConnection, Qt::QueuedConnection);

    workerThread->start();

    // get the initial list of active ports
    emit refreshPortList();
}

Application::~Application()
{
    emit stopPort();
    workerThread->quit();
    workerThread->wait();
    delete ui;
}

// update ui from worker data
void Application::showData(const QString *data) {
   ui->dataLabel->setText(data[0]); 
   ui->voltModeLabel->setText(data[1]); 
   ui->modeLabel->setText(data[2]); 
}

// connect\disconnect from selected port on button press
void Application::togglePortConnection() {
    if(!isPortConnected) {
        emit startPort(ui->selectPort->currentText());
        ui->connectButton->setText("Disconnect");
        isPortConnected = true;
    } else {
        emit stopPort();
        ui->connectButton->setText("Connect");
        isPortConnected = false;
    }
}

// update the list of active ports on the combobox
void Application::updateActivePorts(const QStringList ports) {
    ui->selectPort->clear();
    for(int i = 0; i < ports.size(); i++)
        ui->selectPort->addItem(ports[i]);
}

// update the ports status on the ui
void Application::updatePortStatus(const QString status) {
    ui->comStatusLabel->setText(status);
}
