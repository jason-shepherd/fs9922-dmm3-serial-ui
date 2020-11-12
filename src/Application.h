#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QThread>

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
        void showData(const std::vector<QString> &data);

    signals:
        void startData(const char* port);
    
    private:
        Ui::Application *ui;
        QThread *workerThread;
        Worker *worker;

};
#endif // APPLICATION_H
