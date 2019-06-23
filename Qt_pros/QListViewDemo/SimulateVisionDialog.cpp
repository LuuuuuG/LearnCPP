#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QDirIterator>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QApplication>
#include "SimulateVisionDialog.h"
#include "ui_SimulateVisionDialog.h"
//#include "PluginManager.h"
//#include "util_setting.h"
//#include "util_json.h"
//#include "PclShowService.h"
#include <fstream>
#include <qDebug>

using namespace std;
namespace mmind {
namespace {
const QString kSavePointCloud = "savePointCloud";
//const QString kResDir = QApplication::applicationDirPath() + '/' + "vision_results";
const QString kResDir = "E:/workspace/QListViewDemo/release/vision_results";
string pathNoSuffix(const QString& baseName)
{
    if (baseName.isEmpty()) return {};
    const QString res = kResDir + '/' + baseName.mid(0, 4) + '-' + baseName.mid(4, 2) + '-' +
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

void SimulateVisionDialog::on_tableView_clicked(const QModelIndex &index)
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
        QModelIndex Index = ui->tableView->model()->index(_listIndex, 0);
        ui->tableView->selectionModel()->setCurrentIndex(Index, QItemSelectionModel::SelectCurrent);
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

//    QStringListModel* mode = new QStringListModel(this);
    QStandardItemModel* mode = new QStandardItemModel(this);
    mode->setHorizontalHeaderLabels(QStringList() << "Poses" << "With Cloud" << "With Transform");

//    mode->setColumnCount(3);

    QDirIterator it(kResDir, QStringList() << "*.json", QDir::Files,
                    QDirIterator::Subdirectories);

    int i = 0;
    while (it.hasNext())
    {       

        const QString file = QFileInfo(it.next()).baseName();
        QStandardItem* item0 = new QStandardItem(file);
        item0->setTextAlignment(Qt::AlignCenter);


        QStandardItem* item1 = new QStandardItem(QFile((pathNoSuffix(file) + ".cloud").c_str()).exists() ? "Yes" : "No");
//        item1->setCheckable(false);
//        item1->setCheckState(Qt::Checked);
        item1->setTextAlignment(Qt::AlignCenter);
//        item1->setSelectable(false);


        QStandardItem* item2 = new QStandardItem(QFile((pathNoSuffix(file) + ".transform").c_str()).exists() ? "Yes" : "No");
//        item2->setCheckable(false);
//        item2->setCheckState(Qt::Checked);
        item2->setTextAlignment(Qt::AlignCenter);
//        item2->setSelectable(false);

        mode->setItem(i,0, item0);
        mode->setItem(i,1, item1);
        mode->setItem(i,2, item2);

        ++i;
    }

//    mode->setStringList(_strList);



    ui->tableView->setModel(mode);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->horizontalHeader()->setSectionsClickable(false);
//    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


}

} // namespace mmind
//#include "moc_SimulateVisionDialog.cpp"
