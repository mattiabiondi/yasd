#ifndef YASD_CAR_H
#define YASD_CAR_H

#include "src/const.h"

#include <QPointF>
#include <QLineF>
#include <QtMath>
#include <QPainter>

class Car
{
public:
Car(int type, QPointF *position, int angle);
void move(double accelerationPercentage, double rotationPercentage);
void print(QPaintDevice *device);
QPointF *getPosition();
QLineF **getSensors();

private:
void setSensors();
QPointF *position;
QLineF **sensors;
double acceleration;
double speed;
int angle;
int type;
};

#endif // YASD_CAR_H
