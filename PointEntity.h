#ifndef POINTENTITY_H
#define POINTENTITY_H

#include "QtGui"
#include "QtSql"


class PointEntity
{
public:
    PointEntity();
    PointEntity(QSqlQuery query);

public:
    QString common_zhandoujieguo;
    QString common_kaishizhandou;

    QString zuidui_jiangli;
    QString zuidui_7w;

    QString jiban_zhandoujieguo;
    QString jiban_kaishipipei;
    QString jiban_jiangfen_tuichu;
    QString jiban_jiangfen_tuichu_queren;

    QString qiangzhe_tongguanjiangli;
    QString qiangzhe_qiangzhejianglin;
    QString qiangzhe_axiuluo;
    QString qiangzhe_jinru;


    QString ID;
    QString win_size;
    QString btn_text;
    QString rn;
    QString op_type;
    QString timer;
    QString mouse_xy;
    QString show_info;

};

#endif // POINTENTITY_H
