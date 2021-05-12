#include <QtWidgets/QApplication>

#include "demo01.h"
#include "../stdafx.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    demo01 w;
    w.QMainWindow::show();
    return app.exec();
}
