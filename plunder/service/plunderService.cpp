#include "plunderService.h"

PlunderService::PlunderService()
{

}

QString PlunderService::create_wanjia_font(QString s){

    QString wanjiaName;

    QSize size(100,100); //指定图片大小;
    QImage image(size,QImage::Format_RGB32);
    image.fill(qRgba(0,0,0,100));
    QPainter painter(&image);
    //painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    QPen pen = painter.pen();
    pen.setColor(Qt::white);
    QFont font = painter.font();
    font.setPixelSize(12);
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(image.rect(),Qt::AlignLeft,s);


    RGBUtil* rgbUtil=new RGBUtil();
    QRgb findRgb=qRgb(255,255,255);
    wanjiaName=rgbUtil->getRGBArray(&image,11,12,findRgb);
    qDebug()<<"排行榜玩家名字："+wanjiaName;
    return wanjiaName;
}


QString PlunderService::searchPlayerpic(QString fileName){
    QDir dir;
    QStringList filters;

    fileName="*"+fileName+"*";

    filters << fileName;
    dir.setPath(QDir::currentPath()+"\\玩家战力");

    dir.setNameFilters(filters);
    QDirIterator iter(dir,QDirIterator::Subdirectories);


    QString returnText;
    while (iter.hasNext()) {
        iter.next();
        QFileInfo info=iter.fileInfo();
        if (info.isFile()){
            returnText=returnText+";"+info.fileName();
        }
    }
    return returnText;

}





void PlunderService::plunderPlayer(){


   //QScreen *screen = QGuiApplication::primaryScreen();
   //screen->grabWindow(0).save("jiebiao.bmp","bmp");


    QImage* bg;
    bg = new QImage("1.bmp");



    QImage pic = bg->copy(376,287,80,12);
    pic.save("整个名字.bmp");

    QRgb findRgb=qRgb(204,204,204);
    RGBUtil* rgbUtil=new RGBUtil();

    for(int i=0;i<4;i++){
        QImage pic = bg->copy(376+i*12,287,11,12);
        pic.save("第"+QString::number(i)+"个字.bmp");
        QString normalFontCode=rgbUtil->getRGBArray(&pic,11,12,findRgb);
        //qDebug()<<normalFontCode;
    }




    return;





        QString fileList="";

        for(int i=0;i<3;i++){
            //558,190：排行榜标题，从这里开始搜索,并保存照片
            int dajie_wanjia_x=376;
            int dajie_wanjia_y=286+123*i-1;
            //dajie_wanjia_x=rgbUtil->findRgbByHorizontal(bg,378,dajie_wanjia_y,findRgb,200);
            //if(dajie_wanjia_x==-1){
            //break;
            //}



            QImage pic = bg->copy(dajie_wanjia_x,dajie_wanjia_y,200,12);
            pic.save("bg1.bmp");

            qDebug()<<"劫镖啦3";



            QString normalFontCode=rgbUtil->getRGBArray(&pic,7,12,findRgb);
            qDebug()<<"劫镖界面-玩家名称(normalFontCode):"+normalFontCode;

            //搜索排行榜玩家战力

            FontCodeDao* fontCodeDao=new FontCodeDao();
            QString fontRecord=fontCodeDao->getFontCOdeByNormalCode(normalFontCode);
            QString font=fontRecord.split(";").value(0);

            if(fontRecord==""){
                continue;
            }

            if(fileList==""){
                fileList=searchPlayerpic(font);
            }else{
                fileList=fileList+";"+searchPlayerpic(font);
            }



        }





       playerInfoForm=new PlayerInfoForm();
       playerInfoForm->showPlayer(fileList);

       playerInfoForm->show();

}

QString PlunderService::getPlayerName()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    screen->grabWindow(0).save("玩家名字.bmp","bmp");
     QImage* bg;
     bg = new QImage("玩家名字.bmp");

     QRgb findRgb=qRgb(244,113,110);

     RGBUtil* rgbUtil=new RGBUtil();

     int start_x=rgbUtil->findRgbByHorizontal(bg,383,217,findRgb,50)+15;
     QString normalFontCode="";

     for(int i=0;i<6;i++){
         QImage pic = bg->copy(start_x+i*12,206,11,12);
         //pic.save("第"+QString::number(i)+"个字.bmp");
         normalFontCode=normalFontCode+rgbUtil->getRGBArray(&pic,11,12,findRgb);
     }
     return normalFontCode;
}

QString PlunderService::getPlayerValue(int player_row_num)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    screen->grabWindow(0).save("排行榜.bmp","bmp");

    QImage* bg;
    bg = new QImage("排行榜.bmp");

    //搜索第一行
    QRgb findRgb=qRgb(50,69,93);
    RGBUtil* rgbUtil=new RGBUtil();
    int start_y=rgbUtil->findRgbByVertical(bg,941,230,findRgb,20)-18;


    QString playerValue="";
    findRgb=qRgb(204,204,204);
    for(int i=0;i<6;i++){
        QImage pic = bg->copy(1031+i*6,start_y+33*player_row_num,4,9);
        pic.save("玩家第"+QString::number(i)+"个数字.bmp");
        QString normalFontCode=rgbUtil->getRGBArray(&pic,4,9,findRgb);
        if(normalFontCode=="111001100110011001100110011001101111"){
            playerValue=playerValue+"1";
        }
        else if(normalFontCode=="111011110011001100100000010011111111"){
            playerValue=playerValue+"2";
        }
        else if(normalFontCode=="011110110011011100110001000110011110"){
            playerValue=playerValue+"3";
        }
        else if(normalFontCode=="000100110111011110110011111100110011"){
            playerValue=playerValue+"4";
        }
        else if(normalFontCode=="011111111000111011110011000110011110"){
            playerValue=playerValue+"5";
        }
        else if(normalFontCode=="001101101100111110111001100111010111"){
            playerValue=playerValue+"6";
        }

        else if(normalFontCode=="111111110001000100110010001000100100"){
            playerValue=playerValue+"7";
        }
        else if(normalFontCode=="111110011001111101111011100110011111"){
            playerValue=playerValue+"8";
        }
        else if(normalFontCode=="011010111001100111011111001101101100"){
            playerValue=playerValue+"9";
        }
        else if(normalFontCode=="011010011001100110011001100110010110"){
            playerValue=playerValue+"0";
        }
        else{
            playerValue=playerValue+normalFontCode;
        }

    }

    return playerValue;
}


//保存排行榜战力
void PlunderService::saveBoardPlayer(){

    QScreen *screen = QGuiApplication::primaryScreen();
    screen->grabWindow(0).save("bg.bmp","bmp");
    QImage* bg;
    bg = new QImage("bg.bmp");


    //0,69：flash左上角位置


    RGBUtil* rgbUtil=new RGBUtil();


    QRgb findRgb=qRgb(52,74,99);

    //558,190：排行榜标题，从这里开始搜索
    int paihang_wanjia_y=0;
    paihang_wanjia_y=rgbUtil->findRgbByVertical(bg,558,190,findRgb,200);



    for(int i=0;i<10;i++){
        if(paihang_wanjia_y!=-1){
            QImage pic = bg->copy(558,paihang_wanjia_y+33*i,550,33);
            //pic.save("bg玩家整行"+QString::number(i)+".bmp");

            findRgb=qRgb(204,204,204);
            int x=rgbUtil->findRgbByHorizontal(&pic,0,13,findRgb,200);
            //qDebug()<<QString::number(x);
            //qDebug()<<"玩家名字：12,"+QString::number(x+19);

            QImage pic1 = pic.copy(x+19,12,500,12);
            QString boldFontCode=rgbUtil->getRGBArray(&pic1,7,12,findRgb);

            FontCodeDao* fontCodeDao=new FontCodeDao();

            QString fontRecord=fontCodeDao->getFontCode(boldFontCode);
            if(fontRecord==""){
                savePic(pic1,"玩家战力/"+boldFontCode,"bmp");
            }else{
                QString font=fontRecord.split(";").value(0);
                savePic(pic1,"玩家战力/OK_"+font,"bmp");
            }



            //QFile::remove("bg玩家整行"+QString::number(i)+".bmp");
        }
        else{
            qDebug()<<"搜索不到";
        }
    }
}

void PlunderService::savePic(QImage pic,QString filePath,QString ext){
    for(int i=0;i<20;i++){
        QString t=filePath+"_"+QString::number(i)+"."+ext;

        if(QFile::exists(t)){

        }else{
            pic.save(t);
            break;
        }

    }

}
