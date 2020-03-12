#ifndef SIGNALBLOCKER_H
#define SIGNALBLOCKER_H

#include <QWidget>

namespace Ui {
class signalBlocker;
}

class SignalBlocker : public QWidget
{
    Q_OBJECT

public:
    explicit SignalBlocker(QWidget *parent = nullptr);
    ~SignalBlocker();
    void setValue();
signals:
    void value();
private slots:
    void on_pushButton_clicked();

private:
    Ui::signalBlocker *ui;
};

#endif // SIGNALBLOCKER_H
