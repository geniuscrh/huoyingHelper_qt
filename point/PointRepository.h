#ifndef POINTREPOSITORY_H
#define POINTREPOSITORY_H

#include <QtGui>
#include "common/BaseDao.h"
#include <PointEntity.h>

class PointRepository : public BaseDao
{
public:
    PointRepository();
    QList<PointEntity> list();
};

#endif // POINTREPOSITORY_H
