#include "demo01.h"
#include "../stdafx.h"
#include "tools/effect.h"

void demo01::widgetMouseMoveEvent(QMouseEvent* event) {
    if (isLeftPressDown) {
        QWidget* curW = ui.widget;
        QPoint gloPos = QCursor::pos();

        if (dir == NONE) {
            move(gloPos - dragPos);
        } else {
            QRect newGeo = dragGeo;
            QPoint moveSize = gloPos - dragGloPos;
            switch (dir) {
                case TOP:
                    newGeo.setTop(dragGeo.top() + moveSize.y());
                    break;
                case BOTTOM:
                    newGeo.setBottom(dragGeo.bottom() + moveSize.y());
                    break;
                case LEFT:
                    newGeo.setLeft(dragGeo.left() + moveSize.x());
                    break;
                case RIGHT:
                    newGeo.setRight(dragGeo.right() + moveSize.x());
                    break;
                case BOTTOMLEFT:
                    newGeo.setBottomLeft(dragGeo.bottomLeft() + moveSize);
                    break;
                case BOTTOMRIGHT:
                    newGeo.setBottomRight(dragGeo.bottomRight() + moveSize);
                    break;
                case TOPLEFT:
                    newGeo.setTopLeft(dragGeo.topLeft() + moveSize);
                    break;
                case TOPRIGHT:
                    newGeo.setTopRight(dragGeo.topRight() + moveSize);
                    break;
            }
            if (
                newGeo.width() >= curW->minimumWidth() &&
                newGeo.height() >= curW->minimumHeight()
            ) {
                setGeometry(newGeo);
            }
        }
    }
    QWidget::mouseMoveEvent(event);
}

void demo01::widgetMousePressEvent(QMouseEvent* event) {
    dragGloPos = event->globalPos();
    dragPos = event->globalPos() - pos();
    dragGeo = geometry();
    if (event->button() == Qt::LeftButton) {
        isLeftPressDown = true;
        if (dir != NONE) {
            mouseGrabber();
        }
    }
    QWidget::mousePressEvent(event);
}

void demo01::widgetMouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isLeftPressDown = false;
        releaseMouse();
        setCursor(QCursor(Qt::ArrowCursor));
    }
    QWidget::mouseReleaseEvent(event);
}

void demo01::region(
    const QPoint& cursorGlobalPoint, bool isTemp
) {
    QRect rect = this->ui.widget->rect();
    rect.setX(rect.x() + 10);
    rect.setY(rect.y() + 10);
    rect.setWidth(rect.width() + 10);
    rect.setHeight(rect.height() + 10);
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());
    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    Direction* dir = new Direction;
    if (!isTemp) {
        dir = &this->dir;
    }
    if (tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
        *dir = TOPLEFT;
    } else if (x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        *dir = BOTTOMRIGHT;
    } else if (x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        *dir = BOTTOMLEFT;
    } else if (x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
        *dir = TOPRIGHT;
    } else if (x <= tl.x() + PADDING && x >= tl.x()) {
        *dir = LEFT;
    } else if (x <= rb.x() && x >= rb.x() - PADDING) {
        *dir = RIGHT;
    } else if (y >= tl.y() && y <= tl.y() + PADDING) {
        *dir = TOP;
    } else if (y <= rb.y() && y >= rb.y() - PADDING) {
        *dir = BOTTOM;
    } else {
        *dir = NONE;
    }
    auto iter = dirCursor.find(*dir);
    if (iter != dirCursor.end()) {
        auto cur = QCursor(iter->second);
        if (cur != this->cursor()) {
            this->setCursor(cur);
        }
    }
}

bool demo01::eventFilter(QObject* o, QEvent* e) {
    if (o == ui.widget) {
        switch (e->type()) 	{
            case QEvent::MouseMove:
                widgetMouseMoveEvent(
                    (QMouseEvent*) e
                );
                break;
            case QEvent::MouseButtonPress:
                region(QCursor::pos());
                widgetMousePressEvent(
                    (QMouseEvent*) e
                );
                break;
            case QEvent::MouseButtonRelease:
                widgetMouseReleaseEvent(
                    (QMouseEvent*) e
                );
                break;
        }
    }
    if (underMouse()) {
        region(QCursor::pos(), true);
    }
    return QWidget::eventFilter(o, e);
}

demo01::demo01(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    EffectTool::delTitle(this);
    EffectTool::translucentBackground(this);
    EffectTool::setShadow(this);

    installEventFilter(this);
    ui.widget->installEventFilter(this);
}
