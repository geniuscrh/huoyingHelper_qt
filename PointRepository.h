#ifndef POINTREPOSITORY_H
#define POINTREPOSITORY_H

#include "QtGui"

#include "PointEntity.h"

class PointRepository
{
public:
    PointRepository();
    PointRepository(QString winSize);



    PointEntity *point() const;
    void setPoint(PointEntity *point);

private:
    PointEntity *m_point;

};

#endif // POINTREPOSITORY_H
