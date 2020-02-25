#ifndef BASEDAO_H
#define BASEDAO_H

#include <QtGui>
#include <QtSql>

class BaseDao
{
public:
    BaseDao();
    bool sql_init(QString table_name);
    bool sql_connect();
    bool sql_disconnect();

    bool sql_update(QStringList paramName, QStringList paramValue,QStringList where);   //更新
    bool sql_delete(QStringList where);                                                 //删除
    bool sql_insert(QStringList paramName, QStringList paramValue,bool isAutoConnect);  //插入，是否带连接

    QString formatWhere(QStringList where);

private:
    QString dbFilePath;


protected:
    QSqlDatabase  m_db;
    QString m_table_name;


};

#endif // BASEDAO_H
