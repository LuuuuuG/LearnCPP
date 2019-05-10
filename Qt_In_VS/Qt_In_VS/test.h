#ifndef TEST_H
#define TEST_H

#include <QtWidgets/QMainWindow>
#include "ui_test.h"

class Test : public QMainWindow
{
	Q_OBJECT

public:
	Test(QWidget *parent = 0);
	void paintEvent(QPaintEvent *);
	~Test();

private:
	Ui::TestClass ui;
};

#endif // TEST_H
