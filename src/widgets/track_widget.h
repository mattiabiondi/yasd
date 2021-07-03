#ifndef YASD_TRACK_WIDGET_H
#define YASD_TRACK_WIDGET_H

#include "src/application.h"
#include "src/configuration.h"
#include "src/const.h"
#include "src/input.h"
#include "src/widgets/cars/car.h"
#include "src/widgets/track/track.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QtCharts/QLineSeries>
#include <QPainter>
#include <QPen>
#include <QFont>

using namespace QtCharts;

QT_BEGIN_NAMESPACE
class Session;
QT_END_NAMESPACE

class TrackWidget : public QOpenGLWidget,
	protected QOpenGLFunctions
{
Q_OBJECT

public:
TrackWidget(QWidget *parent = 0);
~TrackWidget();

// OpenGL Events
void initializeGL();
void paintGL();

protected slots:
void teardownGL();
void update();

protected:
void keyPressEvent(QKeyEvent *event);
void keyReleaseEvent(QKeyEvent *event);
void initTrack();
void initCars();
void printTrack();
void printCar(Car *car);
void moveCars();
void moveCar(Car *car);
void checkCollisions(Car *car, QPointF *oldp, QPointF *newp);
void nextGeneration();
void spawnCars(vector<DNA *> DNAs);

private:
Car **cars;
Track ***tracks;
time_t startTime;

Configuration *config;
Session *session;

int n_red;
int n_green;
int n_blue;
int n_cars;

QColor *grass;
QColor *asphalt;

QLineSeries *series;

// Private Helpers
void printContextInformation();
};

#endif // YASD_TRACK_WIDGET_H
