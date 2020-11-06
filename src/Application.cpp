#include "Application.h"
#include "./ui_application.h"

Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Application)
{
    ui->setupUi(this);

    m_serial.open("COM3", 2400, 8, NOPARITY);
    std::cout << m_serial.isOpen() << std::endl;
    m_serial.flush();
}

Application::~Application()
{
    delete ui;
}

void Application::update() {
    char byte;
    
    m_serial.read(&byte);
    m_interpret.update(byte);
    
    
    ui->dataLabel->setText(QString::fromStdString(dataString));
    ui->voltModeLabel->setText(QString::fromStdString(m_interpret.getVoltMode()));
    ui->modeLabel->setText(QString::fromStdString(m_interpret.getMode()));
}
