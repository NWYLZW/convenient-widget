#include "demo01.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    demo01 w;
    w.show();
    return a.exec();
}
