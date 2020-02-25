#include "AutoThread.h"

AutoThread::AutoThread()
{

}

AutoThread::AutoThread(int type,PointEntity* point)
{
    this->m_type=type;
    this->m_point=point;
}

AutoThread::AutoThread(QList<PointEntity *> *pointList)
{
    m_point_list=pointList;
}


void AutoThread::run(){


     ThreadMsg msg;

    while(1>0) {
        for(int i=0;i<m_point_list->length();i++){
            PointEntity *p=m_point_list->at(i);
            Sleep(p->timer.toInt());
            if(p->op_type=="mouse_left"){
                msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
                msg.setMsgString(p->mouse_xy);
                msg.setShowInfo(p->show_info);
                emit returnMsg(msg);
            }
            else if(p->op_type=="wait_time"){
                QTime current_time =QTime::currentTime();
                int hour = current_time.hour();//当前的小时
                int minute = current_time.minute();//当前的分
                int current_time_int=hour*100+minute;
                int wait_timer_int=p->timer.replace(":","").toInt();
                if(wait_timer_int>current_time_int){

                    qDebug()<<"时间未到,目前时间:"+QString::number(current_time_int)+",目标时间："+QString::number(wait_timer_int);
                    qDebug()<<"wait：10秒，并且i--，继续等待";
                    Sleep(10*1000);
                    i--;
                }
            }

        }
    }

    return;


    //进行组队操作
    if(m_type==THREAD_TYPE_ZUDUI){
        ThreadMsg msg;
        msg.setMsgType(m_type);

        while(1>0){
            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->zuidui_jiangli);
            msg.setShowInfo("点击组队奖励");
            emit returnMsg(msg);
            Sleep(1000);


            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->zuidui_7w);
            msg.setShowInfo("点击7W组队");
            emit returnMsg(msg);
            Sleep(1000);

            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->common_kaishizhandou);
            msg.setShowInfo("点击开始战斗");
            emit returnMsg(msg);
            Sleep(1000);
        }

    }


    //进行羁绊循环---已更新
    else if(m_type==THREAD_TYPE_JIBAN){
        ThreadMsg msg;
        msg.setMsgType(m_type);

        while(1>0){
            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->common_zhandoujieguo);
            msg.setShowInfo("点击战斗结果");
            emit returnMsg(msg);
            Sleep(2000);


            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->jiban_zhandoujieguo);
            msg.setShowInfo("点击段位结果");
            emit returnMsg(msg);
            Sleep(1000);

            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->jiban_kaishipipei);
            msg.setShowInfo("点击开始羁绊");
            emit returnMsg(msg);
            Sleep(10*1000);
        }


    }

    //进行羁绊降分
    else if(m_type==THREAD_TYPE_JIBAN_JIANGFEN){
        ThreadMsg msg;
        msg.setMsgType(m_type);

        while(1>0){
            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->common_zhandoujieguo);
            msg.setShowInfo("点击战斗结果");
            emit returnMsg(msg);
            Sleep(2000);


            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->jiban_zhandoujieguo);
            msg.setShowInfo("点击段位结果");
            emit returnMsg(msg);
            Sleep(1000);

            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->jiban_kaishipipei);
            msg.setShowInfo("点击开始羁绊");
            emit returnMsg(msg);
            Sleep(5*1000);

            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->jiban_jiangfen_tuichu);
            msg.setShowInfo("点击撤退");
            emit returnMsg(msg);
            Sleep(2*1000);

            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->jiban_jiangfen_tuichu_queren);
            msg.setShowInfo("撤退确认");
            emit returnMsg(msg);
            Sleep(2*1000);
        }


    }

    //进行强者--已更新
    else if(m_type==THREAD_TYPE_QIANGZHE){
        ThreadMsg msg;
        msg.setMsgType(m_type);

        while(1>0){
            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->common_zhandoujieguo);
            msg.setShowInfo("点击战斗结果");
            emit returnMsg(msg);
            Sleep(4000);


            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->qiangzhe_tongguanjiangli);
            msg.setShowInfo("点击通关奖励");
            emit returnMsg(msg);
            Sleep(500);
            emit returnMsg(msg);
            Sleep(1500);

            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->qiangzhe_qiangzhejianglin);
            msg.setShowInfo("点击强者降临");
            emit returnMsg(msg);
            Sleep(1500);

            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->qiangzhe_axiuluo);
            msg.setShowInfo("点击阿修罗");
            emit returnMsg(msg);
            Sleep(1500);

            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->qiangzhe_jinru);
            msg.setShowInfo("点击进入");      
            emit returnMsg(msg);
            Sleep(500);
            emit returnMsg(msg);
            Sleep(6000);

            msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
            msg.setMsgString(m_point->common_kaishizhandou);
            msg.setShowInfo("点击开始战斗");
            emit returnMsg(msg);
            Sleep(5*1000);
        }


    }
    else if(m_type==THREAD_TYPE_WENDA){
        ThreadMsg msg;
        msg.setMsgType(m_type);
        while(1>0){
            msg.setShowInfo("答题自动判别");
            emit returnMsg(msg);
            Sleep(2*1000);
        }

    }

    else if(m_type==THREAD_TYPE_XIANJIE){
        ThreadMsg msg;
        msg.setMsgType(m_type);

        while (true) {
            //进行时间判断
            QDateTime current_date_time = QDateTime::currentDateTime();
            QString current_date = current_date_time.toString("hhmm");

            qDebug()<<"目前时间:"+current_date;


            int current_date_int=current_date.toInt();
            //current_date_int=1931;


            if(current_date_int>=1930&&current_date_int<=1941){
                //等待进入仙界
                qDebug()<<"目前状态:等待进入仙界";

                msg.setOperateType(OP_TYPE_KEYBOARD);
                msg.setMsgString("esc");
                msg.setShowInfo("退出所有窗口");
                emit returnMsg(msg);
                Sleep(1000);

                /*
                msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
                msg.setMsgString("1588,25");
                msg.setShowInfo("返回村庄");
                emit returnMsg(msg);
                Sleep(3*1000);
                */

                msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
                msg.setMsgString("100,150");
                msg.setShowInfo("点击活动页面");
                emit returnMsg(msg);
                Sleep(1*1000);

                msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
                msg.setMsgString("560,222");//每次都不一样,第一个。
                msg.setShowInfo("点击仙界选项");
                emit returnMsg(msg);
                Sleep(1*1000);

                msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
                msg.setMsgString("1050,534");
                msg.setShowInfo("点击参加");
                emit returnMsg(msg);
                Sleep(4*1000);


                msg.setOperateType(OP_TYPE_MOUSE_L_CLICK);
                msg.setMsgString("1090,625");
                msg.setShowInfo("点击报名参加、进入");
                emit returnMsg(msg);
                Sleep(2*1000);




            }

            else if(current_date_int>=1942&&current_date_int<=2005){
                //进行仙界战斗
                qDebug()<<"目前状态:进行仙界战斗";
                 Sleep(10*1000);

            }
             else if(current_date_int>2005){
                //仙界结束
                qDebug()<<"目前状态:仙界结束";
                break;
            }
            else{
                //仙界结束
                qDebug()<<"目前状态:仙界活动未开启";
                Sleep(10*1000);
            }

        }



    }






}
