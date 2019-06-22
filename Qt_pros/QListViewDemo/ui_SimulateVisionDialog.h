/********************************************************************************
** Form generated from reading UI file 'SimulateVisionDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATEVISIONDIALOG_H
#define UI_SIMULATEVISIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace mmind {

class Ui_SimulateVisionDialog
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *saveVisualPoses;
    QCheckBox *savePointCloud;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QCheckBox *EnableAutoSimulation;
    QListView *listView;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *mmind__SimulateVisionDialog)
    {
        if (mmind__SimulateVisionDialog->objectName().isEmpty())
            mmind__SimulateVisionDialog->setObjectName(QStringLiteral("mmind__SimulateVisionDialog"));
        mmind__SimulateVisionDialog->resize(550, 400);
        mmind__SimulateVisionDialog->setMaximumSize(QSize(16777215, 500));
        gridLayout_2 = new QGridLayout(mmind__SimulateVisionDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox = new QGroupBox(mmind__SimulateVisionDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(1024, 100));
        groupBox->setBaseSize(QSize(0, 20));
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        saveVisualPoses = new QCheckBox(groupBox);
        saveVisualPoses->setObjectName(QStringLiteral("saveVisualPoses"));
        saveVisualPoses->setEnabled(false);
        saveVisualPoses->setCheckable(true);
        saveVisualPoses->setChecked(true);

        verticalLayout_2->addWidget(saveVisualPoses);

        savePointCloud = new QCheckBox(groupBox);
        savePointCloud->setObjectName(QStringLiteral("savePointCloud"));
        savePointCloud->setCheckable(true);

        verticalLayout_2->addWidget(savePointCloud);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(mmind__SimulateVisionDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setEnabled(true);
        groupBox_2->setMaximumSize(QSize(1024, 500));
        groupBox_2->setBaseSize(QSize(0, 20));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        EnableAutoSimulation = new QCheckBox(groupBox_2);
        EnableAutoSimulation->setObjectName(QStringLiteral("EnableAutoSimulation"));
        EnableAutoSimulation->setEnabled(true);

        gridLayout->addWidget(EnableAutoSimulation, 0, 0, 1, 1);

        listView = new QListView(groupBox_2);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setEnabled(true);
        listView->setMouseTracking(true);
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listView->setSelectionRectVisible(false);

        gridLayout->addWidget(listView, 3, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(mmind__SimulateVisionDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 3, 0, 1, 1);


        retranslateUi(mmind__SimulateVisionDialog);

        QMetaObject::connectSlotsByName(mmind__SimulateVisionDialog);
    } // setupUi

    void retranslateUi(QWidget *mmind__SimulateVisionDialog)
    {
        mmind__SimulateVisionDialog->setWindowTitle(QApplication::translate("mmind::SimulateVisionDialog", "Set Vision Results", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("mmind::SimulateVisionDialog", "Save To File", Q_NULLPTR));
        saveVisualPoses->setText(QApplication::translate("mmind::SimulateVisionDialog", "Save Vision Poses", Q_NULLPTR));
        savePointCloud->setText(QApplication::translate("mmind::SimulateVisionDialog", "Save Point Cloud", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("mmind::SimulateVisionDialog", "Load From File", Q_NULLPTR));
        label->setText(QApplication::translate("mmind::SimulateVisionDialog", "Choose Local Vision Poses", Q_NULLPTR));
        EnableAutoSimulation->setText(QApplication::translate("mmind::SimulateVisionDialog", "Auto Simulation", Q_NULLPTR));
    } // retranslateUi

};

} // namespace mmind

namespace mmind {
namespace Ui {
    class SimulateVisionDialog: public Ui_SimulateVisionDialog {};
} // namespace Ui
} // namespace mmind

#endif // UI_SIMULATEVISIONDIALOG_H
