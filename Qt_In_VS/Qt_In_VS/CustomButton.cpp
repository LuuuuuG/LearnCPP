#include "CustomButton.h"
#include "qdebug.h"

CustomButton::CustomButton(QWidget *parent) :
QPushButton(parent)
{
	connect(this, &CustomButton::clicked,
		this, &CustomButton::onButtonCliecked);
}

void CustomButton::onButtonCliecked()
{
	qDebug() << "You clicked this!";
}

void CustomButton::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		qDebug() << "left";
	}
	else {
		QPushButton::mousePressEvent(event);
	}
}