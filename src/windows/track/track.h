#ifndef YASD_TRACK_H
#define YASD_TRACK_H

#include "src/const.h"

#include <QLineF>
#include <QPointF>
#include <QtMath>

class Track
{
public:
Track();
Track(int type, double friction);
QLineF **lines;
int numLines;

protected:
double friction;
};

#endif // YASD_TRACK_H
