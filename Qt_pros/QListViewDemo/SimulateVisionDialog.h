#pragma once
#include <QDialog>
#include <QHash>
//#include "util_global.h"
//#include "MAffine3d.h"

namespace mmind {
namespace Ui {
class SimulateVisionDialog;
}

class SimulateVisionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SimulateVisionDialog(QWidget* parent = nullptr);
    ~SimulateVisionDialog();
    void initSettings();
    std::string simulateVisionPoses();

private slots:
    void on_savePointCloud_clicked(bool checked);

    void on_listView_clicked(const QModelIndex& index);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    int _listIndex;
    QStringList _strList;
    Ui::SimulateVisionDialog* ui;
    QHash<QString, QVariant> _unsavedSettings;
};
} // namespace mmind
