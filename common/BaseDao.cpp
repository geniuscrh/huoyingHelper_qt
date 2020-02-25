#include "BaseDao.h"

BaseDao::BaseDao()
{

}

bool BaseDao::sql_init(QString table_name)
{
   qDebug()<<"BaseDao::init()";
   dbFilePath="D:/huoying.db";
   this->m_table_name=table_name;
}

bool BaseDao::sql_connect()
{
    if(QSqlDatabase::contains("qt_sql_default_connection")){
          m_db = QSqlDatabase::database("qt_sql_default_connection");
    }else{
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName(dbFilePath);
    }

    //打开数据库
    if(!m_db.open()){
         qDebug()<<m_db.lastError();;
    }


}

bool BaseDao::sql_disconnect()
{

    m_db.close();

}

bool BaseDao::sql_update(QStringList paramName, QStringList paramValue,QStringList where)
{
    bool isSuccess=false;
    sql_connect();
    QSqlQuery query(m_db);

    //生成SQL命令
    QString paramText;
    for(int i=0;i<paramName.length();i++){
        paramText=paramText+",["+paramName.at(i)+"]=:paramValue"+QString::number(i);
    }
    paramText=paramText.right(paramText.length()-1);
    QString sql="UPDATE ["+m_table_name+"] SET "+paramText;

    sql=sql+formatWhere(where);
    //qDebug()<<sql;

    //添加参数
    query.prepare(sql);
    for(int i=0;i<paramValue.length();i++){
        query.bindValue(":paramValue"+QString::number(i), paramValue.at(i));
    }

    //执行
    if(!query.exec())
    {
        qDebug()<<"BaseDao Error:update fail";
        isSuccess=false;
    }else{
        isSuccess=true;
    }


    sql_disconnect();
    return isSuccess;
}

bool BaseDao::sql_delete(QStringList where)
{
    bool isSuccess=false;
    sql_connect();
    QSqlQuery query(m_db);


    QString sql="DELETE FROM "+m_table_name+" ";

    sql=sql+formatWhere(where);
    qDebug()<<sql;

    //执行
    query.prepare(sql);
    if(!query.exec())
    {
        qDebug()<<"BaseDao Error:delete fail";
        isSuccess=false;
    }else{
        isSuccess=true;
    }


    sql_disconnect();
    return isSuccess;
}



bool BaseDao::sql_insert(QStringList paramName, QStringList paramValue,bool isAutoConnect)
{
    bool isSuccess=false;
    if(isAutoConnect){
        sql_connect();
    }

    QSqlQuery query(m_db);

    //生成SQL命令
    QString paramNameText,paramValueText;
    for(int i=0;i<paramName.length();i++){
        paramNameText=paramNameText+","+paramName.at(i);
        paramValueText=paramValueText+",:paramValue"+QString::number(i);
    }
    paramNameText=paramNameText.right(paramNameText.length()-1);
    paramValueText=paramValueText.right(paramValueText.length()-1);
    QString sql="INSERT INTO ["+m_table_name+"]("+paramNameText+") VALUES ("+paramValueText+");";

    //添加参数
    query.prepare(sql);
    for(int i=0;i<paramName.length();i++){
        query.bindValue(":paramValue"+QString::number(i), paramValue.at(i));
    }

    //执行
    if(!query.exec())
    {
        qDebug()<<"BaseDao Error:insert fail:"+sql;
        QSqlError error;
       error=m_db.lastError();
       qDebug()<<error.text();
        isSuccess=false;
    }else{
        isSuccess=true;
    }

    if(isAutoConnect){
        sql_disconnect();
    }

    return isSuccess;
}


QString BaseDao::formatWhere(QStringList where)
{
    if(where.length()<1){
        return "";
    }
    QString where_t=" where 1=1";
    for(int i=0;i<where.length();i++){
        QStringList t=where.at(i).split(",");
        if(t[1]=="like"){
            where_t=where_t+" and "+t[0]+" LIKE '%"+t[2]+"%'";
        }
        else if(t[1]=="="){

                where_t=where_t+" and "+t[0]+"='"+t[2]+"'";
        }
        else if(t[1]=="<>"){
                where_t=where_t+" and "+t[0]+"<>'"+t[2]+"'";
        }
        else if(t[1]=="!="){
                where_t=where_t+" and "+t[0]+"!='"+t[2]+"'";
        }
        else if(t[1]=="in"){
                //获取当时时间
                QDateTime current_date_time = QDateTime::currentDateTime();
                QString current_date = current_date_time.toString("yyyy-MM-dd");
                where_t=where_t+" and "+t[0]+" in("+t[2]+",'') or "+t[0]+" is null or taskStartTime like '%"+current_date+"%'";
        }


    }

    return where_t;

}
