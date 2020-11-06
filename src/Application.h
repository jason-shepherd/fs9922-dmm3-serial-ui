#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>

#include "SerialPort.h"
#include "Interpreter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Application; }
QT_END_NAMESPACE

class Application : public QMainWindow
{
    Q_OBJECT

public:
    Application(QWidget *parent = nullptr);
    ~Application();
    void update();

private:
    Ui::Application *ui;
    SerialPort m_serial;
    Interpreter m_interpret;

};
#endif // APPLICATION_H
