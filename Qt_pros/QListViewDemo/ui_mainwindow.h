/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QListView *listView;
    QPushButton *redBtn;
    QPushButton *blueBtn;
    QPushButton *yellowBtn;
    QPushButton *allBtn;
    QPushButton *setRedBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(771, 536);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QLatin1String("QWidget#centralWidget{\n"
"background-color: white;\n"
"}"));
        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(10, 90, 751, 401));
        listView->setStyleSheet(QLatin1String("QListView {\n"
"   background-color: transparent;\n"
"	border:1px solid #EFEFEF;\n"
"}\n"
"\n"
""));
        listView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listView->setSelectionMode(QAbstractItemView::MultiSelection);
        redBtn = new QPushButton(centralWidget);
        redBtn->setObjectName(QStringLiteral("redBtn"));
        redBtn->setGeometry(QRect(120, 30, 100, 23));
        QFont font;
        font.setPointSize(12);
        redBtn->setFont(font);
        redBtn->setStyleSheet(QLatin1String("QPushButton#redBtn{\n"
"background:white;\n"
"border:1px solid rgb(255, 84, 92);\n"
"border-radius:5px;\n"
"padding:2px 4px;\n"
"color:rgb(255, 84, 92);\n"
"}\n"
"\n"
"QPushButton#redBtn:checked{\n"
"background:rgb(255, 84, 92);\n"
"color:white;\n"
"}"));
        redBtn->setCheckable(true);
        redBtn->setChecked(false);
        blueBtn = new QPushButton(centralWidget);
        blueBtn->setObjectName(QStringLiteral("blueBtn"));
        blueBtn->setGeometry(QRect(230, 30, 100, 23));
        blueBtn->setFont(font);
        blueBtn->setStyleSheet(QLatin1String("QPushButton#blueBtn{\n"
"background:white;\n"
"border:1px solid #3288E8;\n"
"border-radius:5px;\n"
"padding:2px 4px;\n"
"color:#3288E8;\n"
"}\n"
"\n"
"QPushButton#blueBtn:checked{\n"
"background:#3288E8;\n"
"color:white;\n"
"}"));
        blueBtn->setCheckable(true);
        yellowBtn = new QPushButton(centralWidget);
        yellowBtn->setObjectName(QStringLiteral("yellowBtn"));
        yellowBtn->setGeometry(QRect(340, 30, 100, 23));
        yellowBtn->setFont(font);
        yellowBtn->setStyleSheet(QLatin1String("QPushButton#yellowBtn{\n"
"background:white;\n"
"border:1px solid rgb(255, 226, 6);\n"
"border-radius:5px;\n"
"padding:2px 4px;\n"
"color:rgb(255, 226, 6);\n"
"}\n"
"\n"
"QPushButton#yellowBtn:checked{\n"
"background:rgb(255, 226, 6);\n"
"color:white;\n"
"}"));
        yellowBtn->setCheckable(true);
        allBtn = new QPushButton(centralWidget);
        allBtn->setObjectName(QStringLiteral("allBtn"));
        allBtn->setGeometry(QRect(10, 30, 100, 23));
        allBtn->setFont(font);
        allBtn->setStyleSheet(QLatin1String("QPushButton#allBtn{\n"
"background:white;\n"
"border:1px solid gray;\n"
"border-radius:5px;\n"
"padding:2px 4px;\n"
"color:gray;\n"
"}\n"
"\n"
"QPushButton#allBtn:checked{\n"
"background:gray;\n"
"color:white;\n"
"}"));
        allBtn->setCheckable(true);
        allBtn->setChecked(true);
        setRedBtn = new QPushButton(centralWidget);
        setRedBtn->setObjectName(QStringLiteral("setRedBtn"));
        setRedBtn->setGeometry(QRect(630, 30, 75, 23));
        setRedBtn->setStyleSheet(QLatin1String("QPushButton#setRedBtn{\n"
"border:1px solid rgb(255, 84, 92);\n"
"border-radius:5px;\n"
"padding:2px 4px;\n"
"background:rgb(255, 84, 92);\n"
"color:white;\n"
"}"));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        redBtn->setText(QApplication::translate("MainWindow", "red", Q_NULLPTR));
        blueBtn->setText(QApplication::translate("MainWindow", "blue", Q_NULLPTR));
        yellowBtn->setText(QApplication::translate("MainWindow", "yellow", Q_NULLPTR));
        allBtn->setText(QApplication::translate("MainWindow", "all", Q_NULLPTR));
        setRedBtn->setText(QApplication::translate("MainWindow", "set red", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
