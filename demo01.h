#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_demo01.h"

class demo01 : public QMainWindow {
    Q_OBJECT

    public:
    demo01(QWidget *parent = Q_NULLPTR);

    private:
    Ui::demo01Class ui;
};
