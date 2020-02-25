#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <windows.h>
#include <QSystemTrayIcon>
#include <QtGui>


#include <util/rgbutil.h>
#include <plunder/widget/playerInfoForm.h>
#include <plunder/widget/playerNameChangeForm.h>
#include <plunder/service/plunderService.h>
#include <plunder/dao/fontCodeDao.h>

#include <AutoThread.h>
#include <ThreadMsg.h>

#include "PointRepository.h"
#include "PointEntity.h"
#include "point/PointTableViewService.h"
#include "PointWin.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QSystemTrayIcon *m_systemTray;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void initHwnd();
    void initSystemTray();
    void testFunction();


    void huoying_jiban_auto_start();

    void huoying_xianjie_auto_start();
    void showPlayerNameChangeForm();//玩家名字转换
    void saveBoardPlayer();//保存排行榜信息
    void plunderPlay();//劫镖,获取玩家信息

    void helper_exit();

    void simulated_mouse(QString type,int x,int y);
    void simulated_keyboard(QString key);

    void my_debug(QString s);


private slots:

    void on_opBtn_clicked();

    void on_testBtn_clicked();

    void on_hideBtn_clicked();






    void on_mmdatiBtn_clicked();

    void on_openDirBtn_clicked();

    void on_setWinSizeBtn_clicked();



    void on_setPointsBtn_clicked();

    void on_startThreadBtn_clicked();

    void on_savePointsBtn_clicked();

    void on_get_hWnd_btn_clicked();

    void on_point_table_add_btn_clicked();

    void on_point_table_del_btn_clicked();

    void on_point_table_up_btn_clicked();

    void on_stopThreadBtn_clicked();

public slots:

    void receiveAutoThreadMsg(ThreadMsg msg);

private:
    Ui::MainWindow *ui;
    HWND hWnd;
    HWND mainHWnd;
    PlayerNameChangeForm* playerNameChangeForm;

    PointEntity * m_point;
    PointTableViewService *point_table_serv;
    PointRepository *point_rep;


    AutoThread *autoThread;

    int test_index=1;



};

#endif // MAINWINDOW_H
