#include "effect.h"

void EffectTool::delTitle(QWidget* w) {
	w->setWindowFlags(Qt::FramelessWindowHint);
}

void EffectTool::translucentBackground(QWidget* w) {
	w->setAttribute(Qt::WA_TranslucentBackground, true);
}

void EffectTool::setShadow(
	QWidget* w,
	int offsetX, int offsetY,
	const QColor& color,
	int radius
) {
	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(w);
	shadow->setOffset(offsetX, offsetY);
	shadow->setColor(color);
	shadow->setBlurRadius(radius);
	w->setGraphicsEffect(shadow);
}
