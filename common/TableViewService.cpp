#include "TableViewService.h"

TableViewService::TableViewService()
{

}



bool TableViewService::table_init(QString cols_config_text)
{
    QStandardItemModel  *myModel = new QStandardItemModel();
    QStringList cols_config=cols_config_text.split("##");

    //设置标题
    myModel->setColumnCount(cols_config.length());
    for(int i=0;i<cols_config.length();i++){
        QStringList t=cols_config.at(i).split("|");
        myModel->setHeaderData(i,Qt::Horizontal,t[0]);
    }
    m_table->setModel(myModel);

    //设置宽度
    for(int i=0;i<cols_config.length();i++){
        QStringList t=cols_config.at(i).split("|");
        m_table->setColumnWidth(i,t[1].toInt());

    }


    m_table->setAlternatingRowColors(true);//交替行
    m_table->horizontalHeader()->setStretchLastSection(true);//最后一列自动拉长
    m_table->setSortingEnabled(true);//可以排序
}

bool TableViewService::table_clear()
{
    QStandardItemModel  *myModel =(QStandardItemModel*)m_table->model();
    for(;myModel->rowCount()>0;){
        myModel->removeRow(0);
    }
}

bool TableViewService::table_add_item(QString add_item_text)
{



    QStandardItemModel  *myModel =(QStandardItemModel*)m_table->model();

    QStringList add_item=add_item_text.split("##");
    int rowCount=myModel->rowCount();

    for(int i=0;i<add_item.length();i++){

        myModel->setItem(rowCount,i,new QStandardItem(add_item[i]));
    }

}
