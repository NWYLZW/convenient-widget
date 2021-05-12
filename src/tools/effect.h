#pragma once

#include <QWidget>
#include <QGraphicsDropShadowEffect>

namespace EffectTool {
    void delTitle(QWidget* w);
    void translucentBackground(QWidget* w);
    void setShadow(
        QWidget* w,
        int offsetX = 0, int offsetY = 0,
        const QColor& color = QColor("#999999"),
        int radius = 10
    );
}