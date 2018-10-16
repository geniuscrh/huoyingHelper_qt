#include "playerNameChangeForm.h"
#include "ui_playerNameChangeForm.h"

PlayerNameChangeForm::PlayerNameChangeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerNameChangeForm)
{
    ui->setupUi(this);
}

PlayerNameChangeForm::~PlayerNameChangeForm()
{
    delete ui;
}


void PlayerNameChangeForm::loadPlayerPic(QString filePath){
    //加载玩家照片,显示在label中
    QImage bg;
    bg.load(filePath);
    ui->filePathEdit->setText(filePath);
    ui->label->setPixmap(QPixmap::fromImage(bg));

    //获取粗字体代码
    RGBUtil* rgbUtil=new RGBUtil();
    QRgb findRgb=qRgb(204,204,204);
    QString boldFontCode=rgbUtil->getRGBArray(&bg,7,12,findRgb);
    ui->boldFontCodeEdit->setText(boldFontCode);

    //获取中文字
    FontCodeDao* fontCodeDao=new FontCodeDao();
    QString fontRecord=fontCodeDao->getFontCode(boldFontCode);
    if(fontRecord==""){
        ui->stausLabel->setText("");
        ui->nameEdit->selectAll();
        ui->nameEdit->setFocus();
    }
    else{
        ui->stausLabel->setText("数据库已存在");
        QStringList recordArray=fontRecord.split(";");
        ui->nameEdit->setText(recordArray.value(0));
        ui->normalFontCodeEdit->setText(recordArray.value(1));
        ui->nameEdit->selectAll();
        ui->nameEdit->setFocus();
    }



}

void PlayerNameChangeForm::savePlayerPic(){

    PlunderService* plunderService=new PlunderService();
    QString font=ui->nameEdit->text();
    QString normalFontCode=plunderService->create_wanjia_font(font);


    plunderService->savePic(ui->label->pixmap()->toImage(),"玩家战力/OK_"+font,"bmp");

    QString fileName=ui->filePathEdit->text();
    QFile::remove(fileName);


    if(ui->stausLabel->text()=="数据库已存在"){

    }else{
        FontCodeDao* fontCodeDao=new FontCodeDao();
        QString boldFontCode=ui->boldFontCodeEdit->text();
        fontCodeDao->addBoldFontCode(font,normalFontCode,boldFontCode);

    }


    ui->stausLabel->setText("转换成功！");

}

void PlayerNameChangeForm::on_loadBtn_clicked()
{

        QString fileName = QFileDialog::getOpenFileName(
                    this,
                    "玩家战力",
                    QDir::currentPath()+"\\玩家战力",
                    "BMP文件(*.bmp);;All files(*.*)"
        );
        if (!fileName.isNull()) {
            loadPlayerPic(fileName);
        }
        else{

        }
}



void PlayerNameChangeForm::on_changeBtn_clicked()
{
    savePlayerPic();
}

void PlayerNameChangeForm::on_delteButton_clicked()
{
    QString fileName=ui->filePathEdit->text();
    QFile::remove(fileName);
}

void PlayerNameChangeForm::closeEvent(QCloseEvent *event){

    event->ignore();
    this->hide();
}
