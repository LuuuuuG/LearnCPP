#include "test.h"
#include "test_label.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Test w;
	//w.show();
	TextTicker t;
	t.show();
	return a.exec();
}
