#include "PointEntity.h"

PointEntity::PointEntity()
{

}

PointEntity::PointEntity(QSqlQuery query)
{
    int id;

    id=query.record().indexOf("id");
    this->ID=query.value(id).toString();

    id=query.record().indexOf("win_size");
    this->win_size=query.value(id).toString();


    id=query.record().indexOf("btn_text");
    this->btn_text=query.value(id).toString();


    id=query.record().indexOf("rn");
    this->rn=query.value(id).toString();


    id=query.record().indexOf("op_type");
    this->op_type=query.value(id).toString();


    id=query.record().indexOf("timer");
    this->timer=query.value(id).toString();


    id=query.record().indexOf("mouse_xy");
    this->mouse_xy=query.value(id).toString();



    id=query.record().indexOf("show_info");
    this->show_info=query.value(id).toString();
}
