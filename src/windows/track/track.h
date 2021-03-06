#ifndef YASD_TRACK_H
#define YASD_TRACK_H

#include "src/const.h"

#include <QLineF>
#include <QPointF>
#include <QtMath>
#include <QPainter>

class Track
{
public:
Track();
Track(int type, double friction);
QLineF **lines;
int numLines;
void print(QPaintDevice *device, int x, int y);

protected:
double friction;
};

#endif // YASD_TRACK_H
