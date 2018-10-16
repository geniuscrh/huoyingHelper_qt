#ifndef PLAYERINFOFORM_H
#define PLAYERINFOFORM_H

#include <QWidget>
#include <QtGui>
#include <QLabel.h>
#include <QGridLayout.h>

namespace Ui {
class PlayerInfoForm;
}

class PlayerInfoForm : public QWidget
{
    Q_OBJECT



public:
    explicit PlayerInfoForm(QWidget *parent = 0);
    ~PlayerInfoForm();
    void showPlayer(QString files);

private:
    Ui::PlayerInfoForm *ui;
    void closeEvent(QCloseEvent *event);//重新关闭窗口
};

#endif // PLAYERINFOFORM_H
