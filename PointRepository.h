#ifndef POINTREPOSITORY_H
#define POINTREPOSITORY_H

#include "QtGui"

#include "PointEntity.h"

class PointRepository
{
public:
    PointRepository();




    PointEntity *point() const;
    void setPoint(PointEntity *point);


    QString init(QString winSize);
private:
    PointEntity *m_point;

};

#endif // POINTREPOSITORY_H
