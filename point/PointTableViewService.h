#ifndef POINTTABLEVIEWSERVICE_H
#define POINTTABLEVIEWSERVICE_H

#include "common/TableViewService.h"
#include "PointEntity.h"

class PointTableViewService : public TableViewService
{
public:
    PointTableViewService();
    PointTableViewService(QTableView *t);

    bool initPointTable();
    bool addPointItem(QList<PointEntity*> *point_list);
    QList<PointEntity*> * loadPointItem();
    void newRow(QString win_size,QString btn_text);
    QString getCurItem_ID();
    bool move(QString op);
};

#endif // POINTTABLEVIEWSERVICE_H
