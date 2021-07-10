#ifndef YASD_CAR_H
#define YASD_CAR_H

#include <QPointF>
#include <QLineF>
#include <QtMath>
#include <QPainter>
#include <QPainterPath>

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
Car(int type, int id, QPointF position, double angle, DNA *dna, int sizeX, int sizeY);
void move();
void print(QPaintDevice *device);
QPointF getPosition();
QLineF **getSensors();
QLineF *getHitbox();
void setPosition(QPointF position);
void die();
bool isAlive();
int getId();
DNA *getDNA();
double getDistance();
double getAliveTime();
int getChunkScore();

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
int **chunkTraveled;
int mapSizeX;
int mapSizeY;
double aliveTime;

DNA *dna;
NeuralNetwork nn;
};

#endif // YASD_CAR_H
