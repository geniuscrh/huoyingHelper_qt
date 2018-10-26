#include "rgbutil.h"

RGBUtil::RGBUtil()
{

}


bool RGBUtil::matchRGB(QRgb rgb, QRgb findRgbs,int limit){


    if( qAbs(qRed(rgb)- qRed(findRgbs))>limit){
        return false;
    }
    if( qAbs(qGreen(rgb)- qGreen(findRgbs))>limit){
        return false;
    }
    if( qAbs(qBlue(rgb)- qBlue(findRgbs))>limit){
        return false;
    }

    return true;
}


QString RGBUtil::getRGB(QImage* bg_rgb,int x,int y){
    QRgb rgb=bg_rgb->pixel(x,y);
    int r,g,b;
    r=qRed(rgb);
    g=qGreen(rgb);
    b=qBlue(rgb);
    QString t;
    t=QString::number(r,16)+QString::number(g,16)+QString::number(b,16);
    t=t.toUpper();
   return t;
}

int RGBUtil::findRgbByVertical(QImage* bg,int x,int y,QRgb findRGB,int maxNum){

    for(int i=0;i<maxNum;i++){
        QRgb rgb=bg->pixel(x,y+i);
        if(matchRGB(rgb,findRGB,10)){
            return (y+i);
        }
    }
    return -1;
}

int RGBUtil::findRgbByHorizontal(QImage* bg,int x,int y,QRgb findRGB,int maxNum){

    for(int i=0;i<maxNum;i++){
        QRgb rgb=bg->pixel(x+i,y);
        if(matchRGB(rgb,findRGB,10)){
            return (x+i);
        }
    }
    return -1;
}





QStringList RGBUtil::searchRGBList(QImage *bg, QStringList pointList, int width, int height, QRgb findRGB1,QRgb findRGB2, int sep_pixel)
{
    QStringList countRGBList;
    for(QString point_xy:pointList){
        int start_x, start_y;
        start_x=point_xy.split(",").at(0).toInt();
        start_y=point_xy.split(",").at(1).toInt();
        QString countRGB_str=countRGB(bg,start_x,start_y,width,height,findRGB1,findRGB2,sep_pixel);
        qDebug()<<"红点分布："+countRGB_str;
        countRGBList.append(countRGB_str);
    }
    return countRGBList;
}

QString RGBUtil::maxRGBList(QStringList countRGBList)
{
    int max_num=-1;
    QString maxRGB="";
    for(QString countRGB:countRGBList){
        int countRgbNum=countRGB.split("|").at(0).toInt();
        if(countRgbNum>max_num){
            max_num=countRgbNum;
            maxRGB=countRGB;
        }
    }

    return maxRGB;
}

QString RGBUtil::minRGBList(QStringList countRGBList)
{
    int min_num=99999999999;
    QString minRGB="";
    for(QString countRGB:countRGBList){
        int countRgbNum=countRGB.split("|").at(0).toInt();
        if(countRgbNum<min_num){
            min_num=countRgbNum;
            minRGB=countRGB;
        }
    }

    return minRGB;
}



QString RGBUtil::countRGB(QImage *bg, int start_x, int start_y, int width, int height, QRgb findRGB1,QRgb findRGB2, int sep_pixel)
{
    int  count_num=0;


    for(int x=0;x<=width;x=x+sep_pixel){
        for(int y=0;y<=height;y=y+sep_pixel){
            QRgb rgb=bg->pixel(start_x+x,start_y+y);
            if(matchRGB(rgb,findRGB1,20)||matchRGB(rgb,findRGB2,20)){
                count_num++;
            }
        }
    }

    return QString::number(count_num)+"|"+QString::number(start_x)+","+QString::number(start_y);

}

QString RGBUtil::getRGBArray(QImage *bg, int w, int h, QRgb trueRgb){

    QString s1="";
    for(int i=0;i<h;i++){
        QString s2="";
        for(int j=0;j<w;j++){
            QRgb rgb=bg->pixel(j,i);
            if(matchRGB(rgb,trueRgb,50)){
                s2=s2+"1";
            }else{
                s2=s2+"0";
            }

        }
        s1=s1+s2;
    }
    return s1;
}



