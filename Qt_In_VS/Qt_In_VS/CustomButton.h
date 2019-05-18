#pragma once
#include "qpushbutton.h"
#include "QMouseEvent"

class CustomButton : public QPushButton
{
	Q_OBJECT
public:
	CustomButton(QWidget *parent = 0);
protected:
	void mousePressEvent(QMouseEvent *event);
private:
	void onButtonCliecked();
};
