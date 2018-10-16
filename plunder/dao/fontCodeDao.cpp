#include "fontCodeDao.h"

FontCodeDao::FontCodeDao()
{

}

QString FontCodeDao::getFontCode(QString boldFontCode){
    QString dbFilePath="D:/huoying.mdb";
    QSqlDatabase  db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ="+dbFilePath);


    bool ok = db.open();
    qDebug()<<"连接数据库状态:"+QString::number(ok);

    QSqlQuery query;
    query.prepare("select * from font_code_table where bold_font_code=?");
    query.addBindValue(boldFontCode);

    query.exec();

    QString returnText="";
    if(query.next()){
        int id=query.record().indexOf("font");
        returnText=query.value(id).toString();

        id=query.record().indexOf("normal_font_code");
        returnText=returnText+";"+query.value(id).toString();

        id=query.record().indexOf("bold_font_code");
        returnText=returnText+";"+query.value(id).toString();
    }


    query.clear();
    db.close();
    return returnText;
}

QString FontCodeDao::getFontCOdeByNormalCode(QString normalFontCode){
    QString dbFilePath="D:/huoying.mdb";
    QSqlDatabase  db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ="+dbFilePath);


    bool ok = db.open();
    qDebug()<<"连接数据库状态:"+QString::number(ok);

    QSqlQuery query;
    query.prepare("select * from font_code_table where normal_font_code=?");
    query.addBindValue(normalFontCode);

    query.exec();

    QString returnText="";
    if(query.next()){
        int id=query.record().indexOf("font");
        returnText=query.value(id).toString();

        id=query.record().indexOf("normal_font_code");
        returnText=returnText+";"+query.value(id).toString();

        id=query.record().indexOf("bold_font_code");
        returnText=returnText+";"+query.value(id).toString();
    }


    query.clear();
    db.close();

    return returnText;
}

void FontCodeDao::AddPlayer(QString playerName, QString playerCode, QString playerValue)
{
    QString dbFilePath="D:/huoying.mdb";
    QSqlDatabase  db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ="+dbFilePath);


    bool ok = db.open();
    qDebug()<<"连接数据库状态:"+QString::number(ok);

    QSqlQuery query;
    query.prepare("insert into player_table(player_name,player_code,player_value) values(?,?,?)");
    query.addBindValue(playerName);
    query.addBindValue(playerCode);
    query.addBindValue(playerValue);
    query.exec();
    query.clear();
    db.close();
}

void FontCodeDao::addBoldFontCode(QString font,QString normalFontCode,QString boldFontCode){


    QString dbFilePath="D:/huoying.mdb";
    QSqlDatabase  db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ="+dbFilePath);


    bool ok = db.open();
    qDebug()<<"连接数据库状态:"+QString::number(ok);

    QSqlQuery query;
    query.prepare("insert into font_code_table(font,normal_font_code,bold_font_code) values(?,?,?)");
    query.addBindValue(font);
    query.addBindValue(normalFontCode);
    query.addBindValue(boldFontCode);
    query.exec();
    query.clear();
    db.close();



}
