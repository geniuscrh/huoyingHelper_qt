#ifndef FONTCODEDAO_H
#define FONTCODEDAO_H


#include <QtGui>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>




class FontCodeDao
{


public:
    FontCodeDao();
    void addBoldFontCode(QString font,QString normalFontCode,QString boldFontCode);
    QString getFontCode(QString boldFontCode);
    QString getFontCOdeByNormalCode(QString normalFontCode);


    void AddPlayer(QString playerName,QString playerCode,QString playerValue);


};

#endif // FONTCODEDAO_H
