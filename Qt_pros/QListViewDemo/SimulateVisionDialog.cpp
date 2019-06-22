#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QDirIterator>
#include <QStringListModel>
#include <QStandardItemModel>

#include "SimulateVisionDialog.h"
#include "ui_SimulateVisionDialog.h"
//#include "PluginManager.h"
//#include "util_setting.h"
//#include "util_json.h"
//#include "PclShowService.h"
#include <fstream>

using namespace std;
namespace mmind {
namespace {
const QString kSavePointCloud = "savePointCloud";
const QString kResDir = "E:/workspace/QListViewDemo/release/vision_results";
string pathNoSuffix(const QString& baseName)
{
    if (baseName.isEmpty()) return {};
    const QString res = "vision_results/" + baseName.mid(0, 4) + '-' + baseName.mid(4, 2) + '-' +
                  baseName.mid(6, 2) + '/' + baseName;
    return res.toStdString();
}
} // namespace

SimulateVisionDialog::SimulateVisionDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::SimulateVisionDialog)
{
    ui->setupUi(this);
    initSettings();
}

SimulateVisionDialog::~SimulateVisionDialog() { delete ui; }

void SimulateVisionDialog::on_savePointCloud_clicked(bool checked)
{
    _unsavedSettings.insert(kSavePointCloud, checked);
}

void SimulateVisionDialog::on_listView_clicked(const QModelIndex& index)
{
    _listIndex = index.row();
}

void SimulateVisionDialog::on_buttonBox_accepted()
{
//    QSettings& settings = mmindSettings();
//    settings.beginGroup(kVizGroup);
//    for (auto it = _unsavedSettings.begin(), itEnd = _unsavedSettings.end(); it != itEnd; ++it)
//    {
//        settings.setValue(it.key(), it.value());
//    }
//    settings.endGroup();
    _unsavedSettings.clear();

    QDialog::accept();
}

void SimulateVisionDialog::on_buttonBox_rejected() { QDialog::reject(); }

string SimulateVisionDialog::simulateVisionPoses()
{
    if (_listIndex < 0) return {};

    const QString posesFile = _strList[_listIndex];

    if (ui->EnableAutoSimulation->isChecked())
    {
        QModelIndex Index = ui->listView->model()->index(_listIndex, 0);
        ui->listView->selectionModel()->setCurrentIndex(Index, QItemSelectionModel::SelectCurrent);
        --_listIndex;
    }

    // load poses from file
    const string filePath = pathNoSuffix(posesFile);

    ifstream t(filePath + ".json");
    const string poses = string((istreambuf_iterator<char>(t)), {});

    ifstream t2(filePath + ".cloud", ios::binary);
    const string localCloud = string((istreambuf_iterator<char>(t2)), {});

    ifstream t3(filePath + ".transform");
    const string transform = string((istreambuf_iterator<char>(t3)), {});

    // load point cloud and transform
//    if (!localCloud.empty() && !transform.empty())
//    {
//        MAffine3d* localTransform = new MAffine3d();
//        localTransform->setFromJson(deserializeJsonObject(transform));
//        notifyCloudCallbacks(localCloud, localTransform);
//    }
    return poses;
}

void SimulateVisionDialog::initSettings()
{
//    QSettings& settings = mmindSettings();
//    settings.beginGroup(kVizGroup);
//    ui->savePointCloud->setChecked(settings.value(kSavePointCloud, false).toBool());
//    settings.endGroup();

    QStringListModel* mode = new QStringListModel(this);
//    QStandardItemModel* mode = new QStandardItemModel(this);

    QDirIterator it(kResDir, QStringList() << "*.json", QDir::Files,
                    QDirIterator::Subdirectories);

    while (it.hasNext()) _strList.push_front(QFileInfo(it.next()).baseName());

    mode->setStringList(_strList);

    ui->listView->setModel(mode);
}

} // namespace mmind
//#include "moc_SimulateVisionDialog.cpp"
