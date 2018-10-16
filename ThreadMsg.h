#ifndef THREADMSG_H
#define THREADMSG_H

#include <QtGui>


class ThreadMsg
{
public:
    ThreadMsg();
    int getMsgType() const;
    void setMsgType(int value);

    QStringList getMsgStringList() const;
    void setMsgStringList(const QStringList &value);

    QString getMsgString() const;
    void setMsgString(const QString &value);

    int getMsgInt() const;
    void setMsgInt(int value);



    int getOperateType() const;
    void setOperateType(int value);

    QString getShowInfo() const;
    void setShowInfo(const QString &value);

private :

    int msgType;
    QStringList msgStringList;
    QString msgString;
    int msgInt;
    int operateType;
    QString showInfo;
};

#endif // THREADMSG_H
