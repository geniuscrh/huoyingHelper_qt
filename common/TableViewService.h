#ifndef TABLEVIEWSERVICE_H
#define TABLEVIEWSERVICE_H

#include <QtGui>
#include <QTableView>
#include <QHeaderView>


class TableViewService
{
public:
    TableViewService();


    bool table_init(QString cols_config_text);
    bool table_clear();
    bool table_add_item(QString add_item_text);

protected:
    QTableView *m_table;

};

#endif // TABLEVIEWSERVICE_H
