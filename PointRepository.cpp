#include "PointRepository.h"

PointRepository::PointRepository()
{

}


PointEntity *PointRepository::point() const
{
    return m_point;
}

void PointRepository::setPoint(PointEntity *point)
{
    m_point = point;
}

QString PointRepository::init(QString winSize)
{
    m_point=new PointEntity();
    //家里大屏电脑-全屏
    qDebug()<<"游戏窗口大小为："+winSize;
    QString rec="";

    if(winSize=="1918*970"){
        //common
        m_point->common_kaishizhandou="900,555";
        m_point->common_zhandoujieguo="960,580";

        //组队
        m_point->zuidui_jiangli="1248,736";
        m_point->zuidui_7w="760,600";

        //羁绊
        m_point->jiban_zhandoujieguo="960,630";
        m_point->jiban_kaishipipei="850,750";

        //强者
        m_point->qiangzhe_tongguanjiangli="791,503";
        m_point->qiangzhe_qiangzhejianglin="1256,33";
        m_point->qiangzhe_axiuluo="1057,610";
        m_point->qiangzhe_jinru="608,500";

        rec="鼠标位置库加载成功:"+winSize;

    }
    //最标准
    if(winSize=="1329*681"){
        //common
        m_point->common_kaishizhandou="666,414";
        m_point->common_zhandoujieguo="666,444";

        //组队
        m_point->zuidui_jiangli="996,610";
        m_point->zuidui_7w="500,450";

        //羁绊
        m_point->jiban_zhandoujieguo="680,480";
        m_point->jiban_kaishipipei="555,611";

        //羁绊降分
        m_point->jiban_jiangfen_tuichu="1307,644";
        m_point->jiban_jiangfen_tuichu_queren="1134,582";

        //强者
        m_point->qiangzhe_tongguanjiangli="666,444";
        m_point->qiangzhe_qiangzhejianglin="999,33";
        m_point->qiangzhe_axiuluo="950,567";
        m_point->qiangzhe_jinru="520,456";

        rec="标准！鼠标位置库加载成功:"+winSize;

    }
    else{



        rec="鼠标位置库中无该窗口大小对应配置："+winSize;
    }
    return rec;
}

