#ifndef POINTREPOSITORY_H
#define POINTREPOSITORY_H

#include "QtGui"
#include "common/BaseDao.h"
#include "PointEntity.h"

class PointRepository : public BaseDao
{
public:
    PointRepository();


    PointEntity *point() const;
    void setPoint(PointEntity *point);
    QString init(QString winSize);

    QList<PointEntity*> *list(QString win_size,QString btn_text);
    QList<PointEntity *> *list_btn(QString win_size);
    bool save(QList<PointEntity *>* point_list);
    bool del(QString id);



private:
    PointEntity *m_point;

};

#endif // POINTREPOSITORY_H
