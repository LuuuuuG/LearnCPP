#include "signalblocker.h"
#include "ui_signalblocker.h"
#include <QDateTime>
#include <qDebug>

namespace  {
template <typename F, typename Cls, typename... Args>
inline void blockedSet(Cls* const obj, F Cls::*fn, Args&&... args)
{
    const auto blocked = obj->blockSignals(true);
    (obj->*fn)(std::forward<Args>(args)...);
    obj->blockSignals(blocked);
}
}
SignalBlocker::SignalBlocker(QWidget* parent) : QWidget(parent), ui(new Ui::signalBlocker)
{
    ui->setupUi(this);
    connect(this, &SignalBlocker::value, ui->pushButton, &QAbstractButton::click);
}

SignalBlocker::~SignalBlocker() { delete ui; }

void SignalBlocker::setValue()
{
    ui->label->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
    emit value();
}

void SignalBlocker::on_pushButton_clicked()
{
//    const bool wasBlocked = this->blockSignals(true);
    qDebug() << "on_pushButton_clicked";// << "wasBlocked:" << wasBlocked;
//    setValue();
    blockedSet(this,&SignalBlocker::setValue);
//    this->blockSignals(wasBlocked);
}
