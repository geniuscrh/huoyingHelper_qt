#include "PointRepository.h"

PointRepository::PointRepository()
{

}

PointRepository::PointRepository(QString winSize)
{
    m_point=new PointEntity();
    //家里大屏电脑-全屏
    qDebug()<<"游戏窗口大小为："+winSize;

    if(winSize=="1918*970"){
        //common
        m_point->common_kaishizhandou="900,555";
        m_point->common_zhandoujieguo="960,580";

        //组队
        m_point->zuidui_jiangli="1248,736";
        m_point->zuidui_7w="760,600";

        //羁绊
        m_point->jiban_zhandoujieguo="960,630";
        m_point->jiban_kaishizhandou="850,750";

        //强者
        m_point->qiangzhe_tongguanjiangli="791,503";
        m_point->qiangzhe_qiangzhejianglin="1256,33";
        m_point->qiangzhe_axiuluo="1057,610";
        m_point->qiangzhe_jinru="608,500";


    }
    else{
        qDebug()<<"鼠标位置库中无该窗口大小对应配置："+winSize;
    }
}

PointEntity *PointRepository::point() const
{
    return m_point;
}

void PointRepository::setPoint(PointEntity *point)
{
    m_point = point;
}

