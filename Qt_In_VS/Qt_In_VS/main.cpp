#include "test.h"
#include "test_label.h"
#include "CustomButton.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Test w;
	//w.show();
	TextTicker t;
	//t.show();
	CustomButton btn;
	btn.setText("This is a Button!");
	btn.show();
	return a.exec();
}
