#include <windows.h>
#include <iostream>
#include <QApplication>

#include "Application.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Application window;
    window.show();
    while(true) {
        window.update();
    }
    return a.exec();
}
