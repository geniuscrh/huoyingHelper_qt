#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initSystemTray();


}


MainWindow::~MainWindow()
{
    delete ui;
}


/*
 * 获取窗口Hwnd
 *
 * */

void MainWindow::initHwnd(){
    mainHWnd=::FindWindow(NULL,L"火影忍者online");


    bool isWebkit=false  ;


    if(isWebkit){
        hWnd = FindWindowEx(mainHWnd, hWnd, L"CefBrowserWindow", NULL);
        if(ui->hwndIndex_2->isChecked()){
            //QMessageBox::critical(0, "信息", "获取第二个窗口");
            hWnd = FindWindowEx(mainHWnd, hWnd, L"CefBrowserWindow", NULL);
        }


        hWnd = FindWindowEx(hWnd, NULL, L"Chrome_WidgetWin_0", NULL);
        hWnd = FindWindowEx(hWnd, NULL, L"Chrome_RenderWidgetHostHWND", NULL);



    }else{
        hWnd = FindWindowEx(mainHWnd, NULL, L"iecontainerclass", NULL);

        if(ui->hwndIndex_2->isChecked()){
            qDebug()<<"获取第二个";
            //QMessageBox::eBox::critical(0, "信息", "获取第二个窗口");
            hWnd = FindWindowEx(mainHWnd, hWnd, L"iecontainerclass", NULL);

        }


        hWnd = FindWindowEx(hWnd, NULL, L"AtlAxWin120", NULL);
        hWnd = FindWindowEx(hWnd, NULL, L"Shell Embedding", NULL);
        hWnd = FindWindowEx(hWnd, NULL, L"Shell DocObject View", NULL);
        hWnd = FindWindowEx(hWnd, NULL, L"Internet Explorer_Server", NULL);
        hWnd = FindWindowEx(hWnd, NULL, L"MacromediaFlashPlayerActiveX", NULL);

    }






    if(hWnd==NULL) {
        m_systemTray->show();
        m_systemTray->showMessage("信息","无法获取hWnd",QSystemTrayIcon::Information,5000);
        return;
    }else{
        //this->hide();
        LPRECT lpRect;
        GetWindowRect(hWnd,lpRect);

        QString winSize=QString::number(lpRect->right-lpRect->left)+"*"+QString::number(lpRect->bottom-lpRect->top);
        PointRepository *point_rep=new PointRepository(winSize);
        m_point=point_rep->point();

        m_systemTray->show();
        m_systemTray->showMessage("信息","获取hWnd",QSystemTrayIcon::Information,5000);
    }
}


/*
 * 初始化托盘
 * */
void MainWindow::initSystemTray(){

    QString systemTrayIcoSrc=":/resource/image/ico/systemTray.png";
    QString systemTrayMenuIcoSrc=":/resource/image/ico/systemTrayMenu.png";



    QIcon icon = QIcon(systemTrayIcoSrc);
    m_systemTray = new QSystemTrayIcon(this);
    m_systemTray->setIcon(icon);


    //设置托管图标菜单
    QAction *m_action;
    QMenu *m_menu;

    m_menu = new QMenu(this);


    m_action =new QAction(m_menu);
    m_action->setIcon(QIcon("://resource/image/ico/MSN_48px_1121664_easyicon.net.png"));
    m_action->setText("自动羁绊");
    connect(m_action,&QAction::triggered,this,&MainWindow::huoying_jiban_auto_start);
    m_menu->addAction(m_action);

    m_menu->addSeparator();



    m_menu->addSeparator();

    m_action =new QAction(m_menu);
    m_action->setIcon(QIcon("://resource/image/ico/Shutdown_48px_1121553_easyicon.net.png"));
    m_action->setText("退出");
    connect(m_action,&QAction::triggered,this,&MainWindow::helper_exit);
    m_menu->addAction(m_action);

    m_systemTray->setContextMenu(m_menu);


}










void MainWindow::on_autoXianjieBtn_clicked()
{
    huoying_xianjie_auto_start();
}

/*
 *
 * 开始自动仙界流程
 *
 * */
void MainWindow::huoying_xianjie_auto_start(){

    /*
    m_systemTray->showMessage("信息","开始仙界",QSystemTrayIcon::Information,5000);
    qRegisterMetaType<ThreadMsg>("ThreadMsg");
    AutoThread *autoThread=new AutoThread(AutoThread::THREAD_TYPE_XIANJIE);
    connect(autoThread,SIGNAL(returnMsg(ThreadMsg)),this,SLOT(receiveAutoThreadMsg(ThreadMsg)));
    autoThread->start();
    */
}




void MainWindow::helper_exit(){
    QApplication* app;
    app->exit(0);
}

void MainWindow::simulated_mouse(QString type, int x, int y)
{
    if(type=="leftClick"){
        ::SendMessage(hWnd,WM_LBUTTONDOWN,MK_LBUTTON,MAKELONG(x,y));
        Sleep(50);
        ::SendMessage(hWnd,WM_LBUTTONUP,MK_LBUTTON,MAKELONG(x,y));
    }

}

void MainWindow::simulated_keyboard(QString key){
    if(key=="esc"){
        ::SendMessage(hWnd,WM_KEYDOWN,VK_ESCAPE,0);
    }
}


void MainWindow::testFunction(){
    QMessageBox::critical(0, "信息", "测试");
}





void MainWindow::showPlayerNameChangeForm(){
    //更新排行榜名字
    playerNameChangeForm= new PlayerNameChangeForm();
    playerNameChangeForm->show();

}

void MainWindow::saveBoardPlayer(){
    //保存排行榜 玩家 战力
    PlunderService* plunderService=new PlunderService();
    plunderService->saveBoardPlayer();
    m_systemTray->showMessage("信息","获取保存成功",QSystemTrayIcon::Information,5000);
}

void MainWindow::plunderPlay(){
    //劫镖,获取玩家信息
    PlunderService* plunderService=new PlunderService();
    plunderService->plunderPlayer();

}

void MainWindow::on_testBtn_clicked()
{
    initHwnd();
}




//隐藏窗口
void MainWindow::on_hideBtn_clicked()
{
    this->hide();
}

void MainWindow::on_autoJibanBtn_clicked()
{
    huoying_jiban_auto_start();
}



/*
 *
 * 开始自动组队流程
 *
 * */

void MainWindow::on_zuduiBtn_clicked()
{
    m_systemTray->showMessage("信息","开始组队",QSystemTrayIcon::Information,5000);

    qRegisterMetaType<ThreadMsg>("ThreadMsg");
    AutoThread *autoThread=new AutoThread(AutoThread::THREAD_TYPE_ZUDUI,m_point);

    connect(autoThread,SIGNAL(returnMsg(ThreadMsg)),this,SLOT(receiveAutoThreadMsg(ThreadMsg)));
    autoThread->start();
}

/*
 *
 * 开始自动羁绊流程
 *
 * */
void MainWindow::huoying_jiban_auto_start(){

    m_systemTray->showMessage("信息","开始羁绊",QSystemTrayIcon::Information,5000);
    qRegisterMetaType<ThreadMsg>("ThreadMsg");


    AutoThread *autoThread=new AutoThread(AutoThread::THREAD_TYPE_JIBAN,m_point);
    connect(autoThread,SIGNAL(returnMsg(ThreadMsg)),this,SLOT(receiveAutoThreadMsg(ThreadMsg)));
    autoThread->start();

}


void MainWindow::receiveAutoThreadMsg(ThreadMsg msg)
{

    //鼠标左击
    if(msg.getOperateType()==AutoThread::OP_TYPE_MOUSE_L_CLICK){

        QStringList mouse_p=msg.getMsgString().split(",");

        int x=mouse_p.at(0).toInt();
        int y=mouse_p.at(1).toInt();

        simulated_mouse("leftClick",x,y);
        m_systemTray->showMessage("信息",msg.getShowInfo()+":"+QString::number(x)+","+QString::number(y),QSystemTrayIcon::Information,5000);
    }
    else if(msg.getOperateType()==AutoThread::OP_TYPE_KEYBOARD){

        QString key=msg.getMsgString();

        simulated_keyboard(key);
        m_systemTray->showMessage("信息",msg.getShowInfo()+":"+key,QSystemTrayIcon::Information,5000);
    }



    if(msg.getMsgType()==AutoThread::THREAD_TYPE_ZUDUI){

    }
    if(msg.getMsgType()==AutoThread::THREAD_TYPE_JIBAN){

    }
    if(msg.getMsgType()==AutoThread::THREAD_TYPE_WENDA){


        QDir dir("喵喵截图/");
        if(dir.exists()){
            qDebug()<<"'喵喵截图'文件夹存在";
        }else{
             m_systemTray->showMessage("信息","'喵喵截图'文件夹不存在",QSystemTrayIcon::Information,2000);
            return;
        }



        QScreen *screen = QGuiApplication::primaryScreen();
        QImage* bg;
        QDateTime time;
        time = QDateTime::currentDateTime();
        QString curtime_str = time.toString("yyyyMMddhhmmss");
        QString imageFileName;

        bool is_test_mode=false;



        if(!is_test_mode){
            imageFileName="喵喵截图/喵喵答题-"+curtime_str+".bmp";
            screen->grabWindow(0).save(imageFileName,"bmp");
            bg = new QImage(imageFileName);
        }else{
            imageFileName="test ("+QString::number(test_index)+").bmp";
            bg = new QImage(imageFileName);
            qDebug()<<"测试截图:"+imageFileName;
            test_index=test_index+1;
        }



        RGBUtil* rgbUtil=new RGBUtil();
        QRgb findRgb1,findRgb2;
        findRgb1=qRgb(230,45,30);
        findRgb2=qRgb(29,12,0);
        int rec_width=200;
        int rec_height=200;
        int sep_pixel=5;
        QString painter_text="";


        QStringList pointList;
        pointList.append("372,330");
        pointList.append("1092,314");
        pointList.append("371,615");
        pointList.append("1088,618");

        //获取范围内的RGB的list
        QStringList countRGBList=rgbUtil->searchRGBList(bg,pointList,rec_width,rec_height,findRgb1,findRgb2,sep_pixel);
        //RGB list中最大数值
        QString maxRGB=rgbUtil->maxRGBList(countRGBList);
        m_systemTray->showMessage("信息","最佳红点分布："+maxRGB,QSystemTrayIcon::Information,2000);
        qDebug()<<"最佳红点分布："+maxRGB;

        for(QString t:countRGBList){
            painter_text=painter_text+"("+t+")";
        }
        painter_text=painter_text+"最佳："+maxRGB;




        //范围内最佳位置
        QPoint best_point;
        QStringList tempList=maxRGB.split("|");
        int total_count_num=tempList.at(0).toInt();

        if(total_count_num<=3){
            m_systemTray->showMessage("信息","红点分布<=3,不进行点位选择",QSystemTrayIcon::Information,2000);
            qDebug()<<"红点分布<=3,不进行点位选择";
            painter_text=painter_text+"红点分布<=3,不进行点位选择";
            best_point.setX(0);
            best_point.setY(0);

        }else{
            QStringList point=tempList.at(1).split(",");
            int point_x=point.at(0).toInt();
            int point_y=point.at(1).toInt();



            QStringList count_list=tempList.at(2).split(",");
            int count_a=count_list.at(0).toInt();
            int count_b=count_list.at(1).toInt();
            int count_c=count_list.at(2).toInt();
            int count_d=count_list.at(3).toInt();


            int best_x=point_x+rec_width/2+rec_width*(count_b+count_d-count_a-count_c)/total_count_num/4;
            int best_y=point_y+rec_height/2+rec_height*(count_c+count_d-count_a-count_b)/total_count_num/4+70;

            //扣除窗口顶部高度
            best_y=best_y-70;


            best_point.setX(best_x);
            best_point.setY(best_y);
            qDebug()<<"最佳红点位置："+QString::number(best_x)+","+QString::number(best_y);
            m_systemTray->showMessage("信息","最佳红点位置："+QString::number(best_x)+","+QString::number(best_y),QSystemTrayIcon::Information,5000);
            qDebug()<<"--------------------------";
        }




        if(best_point.x()==0&&best_point.y()==0){
            //simulated_mouse("leftClick", 687,332);
        }
        else{
            simulated_mouse("leftClick",best_point.x(),best_point.y());

        }



         if(is_test_mode){
             QPainter * painter = new QPainter();
             painter->begin (bg);



             //输出文字信息
             painter->setPen(QColor(0, 0, 0));
             QFont font;
             font.setFamily("Microsoft YaHei");
             font.setPointSize(13);
             painter->setFont(font);
             painter->drawText(350, 660, painter_text);




             //输出判断画框
             for(QString point_xy:pointList){
                 int start_x, start_y;
                 start_x=point_xy.split(",").at(0).toInt();
                 start_y=point_xy.split(",").at(1).toInt();
                 painter->drawRect(start_x, start_y, rec_width, rec_height);

             }

             //输出点击位置
             painter->setBrush(QColor(255, 160, 90));
             painter->drawEllipse(QPointF(best_point.x(), best_point.y()+70), 5, 5);

             painter->end();
             bg->save("debug"+imageFileName,"bmp");


         }



        delete bg;


    }

}

void MainWindow::on_qiangzheBtn_clicked()
{
    m_systemTray->showMessage("信息","开始强者",QSystemTrayIcon::Information,5000);
    qRegisterMetaType<ThreadMsg>("ThreadMsg");
    AutoThread *autoThread=new AutoThread(AutoThread::THREAD_TYPE_QIANGZHE,m_point);
    connect(autoThread,SIGNAL(returnMsg(ThreadMsg)),this,SLOT(receiveAutoThreadMsg(ThreadMsg)));
    autoThread->start();
}

void MainWindow::on_mmdatiBtn_clicked()
{
    m_systemTray->showMessage("信息","开始喵喵答题",QSystemTrayIcon::Information,5000);
    qRegisterMetaType<ThreadMsg>("ThreadMsg");
    AutoThread *autoThread=new AutoThread(AutoThread::THREAD_TYPE_WENDA,m_point);
    connect(autoThread,SIGNAL(returnMsg(ThreadMsg)),this,SLOT(receiveAutoThreadMsg(ThreadMsg)));
    autoThread->start();



    return;


    /*
     *
     * 以下是判断时间点，赞不用
     *

    rgb=bg->pixel(540,165);
    findRgb=qRgb(252,212,78);
    if(rgbUtil->matchRGB(rgb,findRgb,50)){
        //目前正在处于公布答案
        qDebug()<<"时间点：公布答案";
        m_systemTray->showMessage("信息","时间点：公布答案",QSystemTrayIcon::Information,1000);

        return;
    }

    rgb=bg->pixel(370,114);
    findRgb=qRgb(90,45,37);
    if(rgbUtil->matchRGB(rgb,findRgb,50)){
        //目前正在处于--答题时间
        qDebug()<<"时间点：答题时间";
        m_systemTray->showMessage("信息","时间点：答题时间",QSystemTrayIcon::Information,1000);

        Sleep(50);

        return;
    }


    qDebug()<<"时间点：开始等待，及其他未知判断时间";

    */

}

void MainWindow::on_openDirBtn_clicked()
{
    QString youFilePath=QDir::currentPath();
    QDesktopServices::openUrl(QUrl(youFilePath,QUrl::TolerantMode));
}
