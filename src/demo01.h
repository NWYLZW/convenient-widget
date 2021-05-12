#pragma once

#include <QDebug>
#include <QtWidgets/QMainWindow>
#include <iostream>

#include "ui_demo01.h"

#define PADDING 10

class demo01
    : public QMainWindow {
    Q_OBJECT

    public:
    demo01(QWidget *parent = Q_NULLPTR);
    enum Direction {
        TOP = 0,
        BOTTOM = 1,
        LEFT,
        RIGHT,
        TOPLEFT,
        TOPRIGHT,
        BOTTOMLEFT,
        BOTTOMRIGHT,
        NONE
    };

    protected:
    bool eventFilter(QObject* o, QEvent* e);
    void widgetMouseMoveEvent(QMouseEvent* event);
    void widgetMousePressEvent(QMouseEvent* event);
    void widgetMouseReleaseEvent(QMouseEvent* event);

    private:
    Ui::demo01Class ui;
    void region(const QPoint& cursorPoint, bool isTemp = false);

    bool isLeftPressDown;
    QRect dragGeo;
    QPoint dragPos;
    QPoint dragGloPos;

    Direction dir = NONE;
    std::map<demo01::Direction, Qt::CursorShape> dirCursor = { {
        TOPLEFT, Qt::SizeFDiagCursor
    } , {
        BOTTOMRIGHT, Qt::SizeFDiagCursor
    } , {
        BOTTOMLEFT, Qt::SizeBDiagCursor
    } , {
        TOPRIGHT, Qt::SizeBDiagCursor
    } , {
        LEFT, Qt::SizeHorCursor
    } , {
        RIGHT, Qt::SizeHorCursor
    } , {
        TOP, Qt::SizeVerCursor
    } , {
        BOTTOM, Qt::SizeVerCursor
    } , {
        NONE, Qt::ArrowCursor
    } };
};
