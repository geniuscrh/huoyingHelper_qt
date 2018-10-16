#ifndef PLAYERNAMECHANGEFORM_H
#define PLAYERNAMECHANGEFORM_H

#include <QWidget>
#include <QtGui>
#include <QFileDialog>
#include <plunder/service/plunderService.h>
#include <plunder/dao/fontCodeDao.h>
#include <util/rgbutil.h>


namespace Ui {
class PlayerNameChangeForm;
}

class PlayerNameChangeForm : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerNameChangeForm(QWidget *parent = 0);
    ~PlayerNameChangeForm();
    void loadPlayerPic(QString filePath);
    void savePlayerPic();

private slots:
    void on_loadBtn_clicked();
    void on_changeBtn_clicked();

    void on_delteButton_clicked();

private:
    Ui::PlayerNameChangeForm *ui;
    void closeEvent(QCloseEvent *event);//重新关闭窗口
};

#endif // PLAYERNAMECHANGEFORM_H
