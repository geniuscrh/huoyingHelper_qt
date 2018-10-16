#include "playerInfoForm.h"
#include "ui_playerInfoForm.h"

PlayerInfoForm::PlayerInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerInfoForm)
{
    ui->setupUi(this);
}

PlayerInfoForm::~PlayerInfoForm()
{
    delete ui;
}

void PlayerInfoForm::showPlayer(QString files){

    QGridLayout *mainLayout = new QGridLayout(this);
    QStringList fileNameList=files.split(";");
    int i=0;
    for(QString fileName:fileNameList){
        if(fileName.length()>0){
            qDebug()<<"加载文件"+fileName;
            QLabel *lbl = new QLabel(this);

            QImage bg;
            bg.load("玩家战力/"+fileName);
            lbl->setPixmap(QPixmap::fromImage(bg));

            mainLayout->addWidget(lbl,i,0);
            i++;
        }

    }

    //QImage bg;
    //
    //ui->label->setPixmap(QPixmap::fromImage(bg));


}

void PlayerInfoForm::closeEvent(QCloseEvent *event){
    qDebug()<<"asdfasdfa";
    event->ignore();
    this->hide();
}
