#include "mainwindow.h"
#include "SimulateVisionDialog.h"
#include <QApplication>
using namespace mmind;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.show();
    SimulateVisionDialog sDlg;
    sDlg.initSettings();
    sDlg.show();

    return a.exec();
}
