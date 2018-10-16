#ifndef AUTOTHREAD_H
#define AUTOTHREAD_H

#include <QThread>
#include <QtGui>
#include <ThreadMsg.h>

class AutoThread  : public QThread
{
     Q_OBJECT
public:
    AutoThread();
    AutoThread(int type);

    //进行类别
    static const int THREAD_TYPE_ZUDUI=1001;//组队
    static const int THREAD_TYPE_JIBAN=1002;//羁绊
    static const int THREAD_TYPE_QIANGZHE=1003;//强者
    static const int THREAD_TYPE_WENDA=1004;//喵喵问答
    static const int THREAD_TYPE_XIANJIE=1005;//仙界



    //操作类别
    static const int OP_TYPE_MOUSE_L_CLICK=9001;
    static const int OP_TYPE_KEYBOARD=9002;

signals:
    void returnMsg(ThreadMsg msg);

protected:
    void run();

private :
    int m_type;

    QString point_zhandoujieguo="960,580";
    QString point_kaishizhandou="900,555";

};

#endif // AUTOTHREAD_H
