#ifndef YASD_CAR_H
#define YASD_CAR_H

#include <QPointF>
#include <QLineF>
#include <QtMath>
#include <QPainter>

#include <chrono>
#include <ctime>
#include <iostream>
#include <ratio>
#include <stdio.h>
#include <math.h>

#include "src/const.h"
#include "src/utils.h"

#include "src/genetic_algorithm/dna.h"
#include "src/neural_network/neural_network.h"

#define sign(x) (signbit(x) ? -1 : 1)

using namespace std::chrono;
class Car
{
public:
Car(int type, int id, QPointF position, double angle, int firstTime = 0, DNA dna = 0);
void move();
void print(QPaintDevice *device);
QPointF getPosition();
QLineF **getSensors();
QLineF *getHitbox();
void setPosition(QPointF position);
void die();
bool isAlive();

DNA getDNA();
double getDistance();
double getAliveTime();

private:
void setSensors();
void setHitbox();
NeuralNetwork initNeuralNetwork();

QPointF position;
QLineF **sensors;
QLineF hitbox[4];
double acceleration;
double speed;
double angle;
int type;
int id;
bool alive;
double distance;
bool *chunkTraveled;
high_resolution_clock::time_point t_current, t_start;
duration<double, std::milli> aliveTime;

DNA dna;
NeuralNetwork nn;
};

#endif // YASD_CAR_H
