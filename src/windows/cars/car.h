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
Car(int type, int id, QPointF position, int angle, int firstTime = 0, DNA dna = 0);
// void move(double accelerationPercentage, double rotationPercentage);
void move();
void print(QPaintDevice *device);
QPointF getPosition();
QLineF **getSensors();
void setPosition(QPointF position);
void die();
bool isAlive();

DNA getDNA();
double getMovement();
double getAliveTime();

private:
void setSensors();
void setHitbox();
// float *arrayPortion(float *array, int start, int end);
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
double movement;
bool *chunkTraveled;
high_resolution_clock::time_point current, start;
duration<double, std::milli> aliveTime;

DNA dna;
NeuralNetwork nn;
};

#endif // YASD_CAR_H
