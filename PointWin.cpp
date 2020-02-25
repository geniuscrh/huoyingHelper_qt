#include "PointWin.h"
#include "ui_PointWin.h"



PointWin::PointWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PointWin)
{
    ui->setupUi(this);

}

PointWin::~PointWin()
{
    delete ui;
}

void PointWin::resizeEvent(QResizeEvent *event)
{
    QString text=QString::number(frameGeometry().width())+","+QString::number(frameGeometry().height());
    ui->cur_point_text->setText(text);

}
