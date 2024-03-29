#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initSystemTray();

    //初始化
    point_table_serv=new PointTableViewService(ui->pointTable);
    point_rep= new PointRepository();

    point_table_serv->initPointTable();




}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_testBtn_clicked()
{
    my_debug("获取自动化");

    QList<PointEntity*> *point_list=point_rep->list_btn(ui->cur_win_size_text->text());

    int row_num=4;

    for(int i=0;i<point_list->length();i++){
        PointEntity* p=point_list->at(i);
        QPushButton *btn=new QPushButton(p->btn_text,ui->groupBox_2);
        btn->setToolTip(p->win_size);
        btn->move(20+120*(i%row_num),20+40*(i/row_num));
        btn->show();

        connect(btn,SIGNAL(clicked()),this,SLOT(on_opBtn_clicked()));

    }
}

void MainWindow::on_opBtn_clicked()
{
   QPushButton *btn=(QPushButton*)sender();

   //加载数据到table中
   QList<PointEntity*> *point_list=point_rep->list(btn->toolTip(),btn->text());
   point_table_serv->addPointItem(point_list);

   //显示当前自动化名称
   ui->cur_btn_text->setText(btn->text());




}


void MainWindow::on_get_hWnd_btn_clicked()
{
   initHwnd();

}

/*
 * 获取窗口Hwnd
 *
 * */

void MainWindow::initHwnd(){
    mainHWnd=::FindWindow(NULL,L"火影忍者online");

    bool isWebkit=false;


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
        LPRECT lpRect;
        GetWindowRect(mainHWnd,lpRect);

        QString winSize=QString::number(lpRect->right-lpRect->left)+"*"+QString::number(lpRect->bottom-lpRect->top);
        ui->cur_win_size_text->setText(winSize);
        qDebug()<<"获取窗口成功:"+winSize;
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


    m_menu->addSeparator();

    m_action =new QAction(m_menu);
    m_action->setIcon(QIcon("://resource/image/ico/Shutdown_48px_1121553_easyicon.net.png"));
    m_action->setText("退出");
    connect(m_action,&QAction::triggered,this,&MainWindow::helper_exit);
    m_menu->addAction(m_action);

    m_systemTray->setContextMenu(m_menu);



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

void MainWindow::my_debug(QString s)
{

    ui->my_debug_text->append(s);
}




void MainWindow::testFunction(){
    QMessageBox::critical(0, "信息", "测试");
}



//隐藏窗口
void MainWindow::on_hideBtn_clicked()
{
    this->hide();
}


void MainWindow::receiveAutoThreadMsg(ThreadMsg msg)
{


    //鼠标左击
    if(msg.getOperateType()==AutoThread::OP_TYPE_MOUSE_L_CLICK){

        QStringList mouse_p=msg.getMsgString().split(",");
        int x=mouse_p.at(0).toInt();
        int y=mouse_p.at(1).toInt();
        simulated_mouse("leftClick",x,y);
        my_debug("自动化:"+msg.getShowInfo());
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

        /**
         *设置是否测试模式！！！！！！！！！
         * @brief is_test_mode
         */
        bool is_test_mode=false;



        if(!is_test_mode){
            imageFileName="喵喵截图/喵喵答题-"+curtime_str+".bmp";
            screen->grabWindow(0).save(imageFileName,"bmp");
            bg = new QImage(imageFileName);
        }else{

            imageFileName="test ("+QString::number(test_index)+").bmp";

            QFile *f=new QFile(imageFileName);

            bg = new QImage(imageFileName);

            qDebug()<<"测试截图:"+imageFileName+"存在："+QString::number(f->exists());
            test_index=test_index+1;
        }



        RGBUtil* rgbUtil=new RGBUtil();
        QRgb findRgb1,findRgb2;

        findRgb1=qRgb(146,135,76);
        findRgb2=qRgb(153,151,38);
        //设置采集范围
        int rec_width=290;
        int rec_height=250;
        int sep_pixel=5;
        QString painter_text="";


        QStringList pointList;
        pointList.append("500,367,700,600");
        pointList.append("1200,365,1360,592");
        pointList.append("560,650,710,888");
        pointList.append("1137,628,1320,898");

        //获取范围内的RGB的list
        QStringList countRGBList=rgbUtil->searchRGBList(bg,pointList,rec_width,rec_height,findRgb1,findRgb2,sep_pixel);
        //RGB list中最小数值
        QString minRGB=rgbUtil->minRGBList(countRGBList);
        m_systemTray->showMessage("信息","最佳分布："+minRGB,QSystemTrayIcon::Information,2000);
        qDebug()<<"最佳分布："+minRGB;



        //范围内最佳位置
        QPoint best_point;
        for(QString point:pointList){
            if(point.contains(minRGB.split("|").at(1))){

                int best_x=point.split(",").at(2).toInt();
                int best_y=point.split(",").at(3).toInt();

                //扣除窗口顶部高度
                best_y=best_y-70;

                best_point.setX(best_x);
                best_point.setY(best_y);
            }
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

             for(int i=0;i<countRGBList.length();i++){
                 painter->drawText(350, 660+i*20, countRGBList.at(i));
             }







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



void MainWindow::on_mmdatiBtn_clicked()
{
    m_systemTray->showMessage("信息","开始喵喵答题",QSystemTrayIcon::Information,5000);
    qRegisterMetaType<ThreadMsg>("ThreadMsg");
    autoThread=new AutoThread(AutoThread::THREAD_TYPE_WENDA,m_point);
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

void MainWindow::on_setWinSizeBtn_clicked()
{
    MoveWindow(mainHWnd,0,0,1366,728,true);
}


void MainWindow::on_setPointsBtn_clicked()
{
    PointWin *pointWin=new PointWin();
    pointWin->show();
    pointWin->setGeometry(0,0,100,100);
}

void MainWindow::on_startThreadBtn_clicked()
{
    QString win_size=ui->cur_win_size_text->text();
    QString btn_text=ui->cur_btn_text->text();

    QList<PointEntity*> *point_list=point_rep->list(win_size,btn_text);

    //开始运行
    m_systemTray->showMessage("信息",btn_text,QSystemTrayIcon::Information,5000);
    qRegisterMetaType<ThreadMsg>("ThreadMsg");
    autoThread=new AutoThread(point_list);

    connect(autoThread,SIGNAL(returnMsg(ThreadMsg)),this,SLOT(receiveAutoThreadMsg(ThreadMsg)));
    autoThread->start();


}

void MainWindow::on_stopThreadBtn_clicked()
{
    autoThread->terminate();
    autoThread->wait();
}

void MainWindow::on_savePointsBtn_clicked()
{
    QList<PointEntity *> *point_list=point_table_serv->loadPointItem();
    point_rep->save(point_list);

    return;
}



void MainWindow::on_point_table_add_btn_clicked()
{
    QString win_size=ui->cur_win_size_text->text();
    QString btn_text=ui->cur_btn_text->text();

    point_table_serv->newRow(win_size,btn_text);
}

void MainWindow::on_point_table_del_btn_clicked()
{
    QString id=point_table_serv->getCurItem_ID();
    point_rep->del(id);
}

void MainWindow::on_point_table_up_btn_clicked()
{
    point_table_serv->move("up");
}


