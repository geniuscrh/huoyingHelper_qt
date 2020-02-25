#include "PointRepository.h"

PointRepository::PointRepository()
{
    this->sql_init("point_table");

}

QList<PointEntity*> *PointRepository::list(QString win_size,QString btn_text)
{
    sql_connect();

    QSqlQuery query(m_db);
    query.prepare("select * from "+this->m_table_name+" where win_size=? and btn_text=?");
    query.addBindValue(win_size);
    query.addBindValue(btn_text);
    query.exec();
    QList<PointEntity*> *list=new QList<PointEntity*>;

    while(query.next()){
            PointEntity *point_e=new PointEntity(query);
            list->append(point_e);
    }

    query.clear();

    sql_disconnect();
    return list;
}

QList<PointEntity *> *PointRepository::list_btn(QString win_size)
{
    QList<PointEntity*> *list=new QList<PointEntity*>;
    sql_connect();

    QSqlQuery query(m_db);
    query.prepare("select win_size,btn_text from "+this->m_table_name+" group by win_size,btn_text  HAVING win_size=?");
    query.addBindValue(win_size);

    query.exec();

    while(query.next()){
            PointEntity *point_e=new PointEntity();
            int id;
            id=query.record().indexOf("btn_text");
            point_e->btn_text=query.value(id).toString();

            id=query.record().indexOf("win_size");
            point_e->win_size=query.value(id).toString();

            list->append(point_e);
    }


    sql_disconnect();
    return list;
}

bool PointRepository::save(QList<PointEntity *> *point_list)
{


    for(int i=0;i<point_list->length();i++){
        PointEntity* p=point_list->at(i);
        QStringList paramName,paramValue,where;

        //更新操作
        if(p->ID.length()>0){
            paramName.append("rn");paramValue.append(p->rn);
            paramName.append("op_type");paramValue.append(p->op_type);
            paramName.append("timer");paramValue.append(p->timer);
            paramName.append("mouse_xy");paramValue.append(p->mouse_xy);
            paramName.append("show_info");paramValue.append(p->show_info);

            where.append("id,=,"+p->ID);
            sql_update(paramName,paramValue,where);
        }
        //新增操作
        else{

            paramName.append("rn");paramValue.append(p->rn);
            paramName.append("op_type");paramValue.append(p->op_type);
            paramName.append("timer");paramValue.append(p->timer);
            paramName.append("mouse_xy");paramValue.append(p->mouse_xy);
            paramName.append("show_info");paramValue.append(p->show_info);
            paramName.append("win_size");paramValue.append(p->win_size);
            paramName.append("btn_text");paramValue.append(p->btn_text);

            sql_insert(paramName,paramValue,true);

        }
    }
}

bool PointRepository::del(QString id)
{
    QStringList where;
    where.append("ID,=,"+id);
    sql_delete(where);
}




PointEntity *PointRepository::point() const
{
    return m_point;
}

void PointRepository::setPoint(PointEntity *point)
{
    m_point = point;
}

QString PointRepository::init(QString winSize)
{
    m_point=new PointEntity();
    //家里大屏电脑-全屏
    qDebug()<<"游戏窗口大小为："+winSize;
    QString rec="";

    if(winSize=="1918*970"){
        //common
        m_point->common_kaishizhandou="900,555";
        m_point->common_zhandoujieguo="960,580";

        //组队
        m_point->zuidui_jiangli="1248,736";
        m_point->zuidui_7w="760,600";

        //羁绊
        m_point->jiban_zhandoujieguo="960,630";
        m_point->jiban_kaishipipei="850,750";

        //强者
        m_point->qiangzhe_tongguanjiangli="791,503";
        m_point->qiangzhe_qiangzhejianglin="1256,33";
        m_point->qiangzhe_axiuluo="1057,610";
        m_point->qiangzhe_jinru="608,500";

        rec="鼠标位置库加载成功:"+winSize;

    }
    //最标准
    else if(winSize=="1329*681"){
        //common
        m_point->common_kaishizhandou="666,414";
        m_point->common_zhandoujieguo="666,444";

        //组队
        m_point->zuidui_jiangli="996,610";
        m_point->zuidui_7w="500,450";

        //羁绊
        m_point->jiban_zhandoujieguo="680,480";
        m_point->jiban_kaishipipei="555,611";

        //羁绊降分
        m_point->jiban_jiangfen_tuichu="1307,644";
        m_point->jiban_jiangfen_tuichu_queren="1134,582";

        //强者
        m_point->qiangzhe_tongguanjiangli="666,444";
        m_point->qiangzhe_qiangzhejianglin="999,33";
        m_point->qiangzhe_axiuluo="950,567";
        m_point->qiangzhe_jinru="520,456";

        rec="标准！鼠标位置库加载成功:"+winSize;

    }

    //Hp 430G
    else if(winSize=="1364*658"){
        //common
        m_point->common_kaishizhandou="666,414";
        m_point->common_zhandoujieguo="690,430";//OK

        //组队
        m_point->zuidui_jiangli="996,610";
        m_point->zuidui_7w="500,450";

        //羁绊-OK
        m_point->jiban_zhandoujieguo="684,470";//战斗结果
        m_point->jiban_kaishipipei="569,573";//开始匹配

        //羁绊降分-OK
        m_point->jiban_jiangfen_tuichu="1310,635";
        m_point->jiban_jiangfen_tuichu_queren="1173,563";

        //强者
        m_point->qiangzhe_tongguanjiangli="666,444";
        m_point->qiangzhe_qiangzhejianglin="999,33";
        m_point->qiangzhe_axiuluo="950,567";
        m_point->qiangzhe_jinru="520,456";

        rec="Hp 430G！鼠标位置库加载成功:"+winSize;

    }
    else{



        rec="鼠标位置库中无该窗口大小对应配置："+winSize;
    }
    return rec;
}



