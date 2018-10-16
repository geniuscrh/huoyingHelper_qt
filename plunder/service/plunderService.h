#ifndef PLUNDERSERVICE_H
#define PLUNDERSERVICE_H


#include <QWidget>
#include <QtGui>
#include <util/rgbutil.h>
#include <plunder/dao/fontCodeDao.h>
#include <plunder/widget/playerInfoForm.h>


class PlunderService
{
public:
    PlunderService();

    void saveBoardPlayer();//保存排行榜玩家信息

    QString searchPlayerpic(QString fileName);//根据字体，搜索玩家战力照片

    void savePic(QImage pic,QString filePath,QString ext);

    QString create_wanjia_font(QString s);//生成玩家首字母，字体为细



    void plunderPlayer();//获取打劫玩家信息
    QString getPlayerName();//获取玩家名字（玩家信息页面）
    QString getPlayerValue(int player_row_num);//获取玩家战力（排行榜）

    PlayerInfoForm* playerInfoForm;

};

#endif // PLUNDERSERVICE_H
