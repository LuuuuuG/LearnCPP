#include "mainwindow.h"
#include "SimulateVisionDialog.h"
#include <QApplication>
#include <qwidget.h>
#include "signalblocker.h"
using namespace mmind;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    SimulateVisionDialog sDlg;
//    sDlg.update();
//    sDlg.show();

    SignalBlocker s;
    s.show();
    return a.exec();
}
