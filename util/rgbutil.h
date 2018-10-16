#ifndef RGBUTIL_H
#define RGBUTIL_H

#include <QMainWindow>
#include <QtGui>
#include <QSystemTrayIcon>

class RGBUtil
{
public:
    RGBUtil();

    QString getRGB(QImage* bg,int x,int y);
    bool matchRGB(QRgb rgb,QRgb findRgbs,int limit);

    int findRgbByVertical(QImage* bg,int x,int y,QRgb findRGB,int maxNum);
    int findRgbByHorizontal(QImage* bg,int x,int y,QRgb findRGB,int maxNum);

    QStringList searchRGBList(QImage* bg,QStringList pointList,int width,int height,QRgb findRGB1,QRgb findRGB2,int sep_pixel);
    QString maxRGBList(QStringList countRGBList);
    QString countRGB(QImage* bg,int start_x,int start_y,int width,int height,QRgb findRGB1,QRgb findRGB2,int sep_pixel);

    QString getRGBArray(QImage* bg,int w,int h,QRgb trueRgb);
};

#endif // RGBUTIL_H
