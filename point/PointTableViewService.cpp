#include "PointTableViewService.h"



PointTableViewService::PointTableViewService()
{

}

PointTableViewService::PointTableViewService(QTableView *t)
{
    this->m_table=t;
}


bool PointTableViewService::initPointTable()
{
    table_init("ID|30##事件|80##延迟|50##位置|80##提示|80##分别率|70##名称|50");

}

bool PointTableViewService::addPointItem(QList<PointEntity *> *point_list)
{
    table_clear();
    for(int i=0;i<point_list->length();i++){
        PointEntity* p=point_list->at(i);
        table_add_item(p->ID+"##"+p->op_type+"##"+p->timer+"##"+p->mouse_xy+"##"+p->show_info+"##"+p->win_size+"##"+p->btn_text);
    }
}

QList<PointEntity *> *PointTableViewService::loadPointItem()
{
    QStandardItemModel  *myModel =(QStandardItemModel*)m_table->model();
    QList<PointEntity *> *point_list=new QList<PointEntity *>();

    for(int i=0;i<myModel->rowCount();i++){
        PointEntity *p=new PointEntity();
        p->ID=myModel->index(i,0).data().toString().trimmed();
        p->op_type=myModel->index(i,1).data().toString().trimmed();
        p->timer=myModel->index(i,2).data().toString().trimmed();
        p->mouse_xy=myModel->index(i,3).data().toString().trimmed();
        p->show_info=myModel->index(i,4).data().toString().trimmed();
        p->win_size=myModel->index(i,5).data().toString().trimmed();
        p->btn_text=myModel->index(i,6).data().toString().trimmed();
        p->rn=QString::number(i);

        point_list->append(p);
    }

    return point_list;
}

void PointTableViewService::newRow(QString win_size,QString btn_text)
{
    QStandardItemModel  *myModel =(QStandardItemModel*)m_table->model();
    int rowCount=myModel->rowCount();

    myModel->setItem(rowCount,1,new QStandardItem("mouse_left"));
    myModel->setItem(rowCount,5,new QStandardItem(win_size));
    myModel->setItem(rowCount,6,new QStandardItem(btn_text));


}

QString PointTableViewService::getCurItem_ID()
{
    QStandardItemModel  *myModel =(QStandardItemModel*)m_table->model();

    QModelIndex index = m_table->selectionModel()->currentIndex();
    int iSel = index.row();
    if(iSel<0){
        return "";
    }else{
        return myModel->index(iSel,0).data().toString().trimmed();
    }
}

bool PointTableViewService::move(QString op)
{

    QModelIndex index = m_table->selectionModel()->currentIndex();
    int cur_row = index.row();


    m_table->verticalHeader()->setSectionsMovable(true);
    m_table->setSortingEnabled(true);

    if(op=="up"&&cur_row>0){
        qDebug()<<"up:"+QString::number(cur_row);
        m_table->verticalHeader()->moveSection(cur_row,cur_row-1);
    }
    else if(op=="down"){
        m_table->verticalHeader()->moveSection(cur_row,cur_row+1);
    }



}
