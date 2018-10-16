#include "ThreadMsg.h"

ThreadMsg::ThreadMsg()
{

}

int ThreadMsg::getMsgType() const
{
    return msgType;
}

void ThreadMsg::setMsgType(int value)
{
    msgType = value;
}

QStringList ThreadMsg::getMsgStringList() const
{
    return msgStringList;
}

void ThreadMsg::setMsgStringList(const QStringList &value)
{
    msgStringList = value;
}

QString ThreadMsg::getMsgString() const
{
    return msgString;
}

void ThreadMsg::setMsgString(const QString &value)
{
    msgString = value;
}

int ThreadMsg::getMsgInt() const
{
    return msgInt;
}

void ThreadMsg::setMsgInt(int value)
{
    msgInt = value;
}

int ThreadMsg::getOperateType() const
{
    return operateType;
}

void ThreadMsg::setOperateType(int value)
{
    operateType = value;
}

QString ThreadMsg::getShowInfo() const
{
    return showInfo;
}

void ThreadMsg::setShowInfo(const QString &value)
{
    showInfo = value;
}
