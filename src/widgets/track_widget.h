#ifndef YASD_TRACK_TAB0_H
#define YASD_TRACK_TAB0_H

#include "src/application.h"
#include "src/configuration.h"
#include "src/const.h"
#include "src/input.h"
#include "src/widgets/cars/car.h"
#include "src/widgets/track/track.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QPainter>
#include <QPen>
#include <QFont>

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

private:
Car **cars;
Track ***tracks;
time_t startTime;
int num_gen = 0;

Configuration *config;
int n_red;
int n_green;
int n_blue;
int n_cars;

QColor *grass;
QColor *asphalt;

// Private Helpers
void printContextInformation();
};

#endif // YASD_TRACK_TAB0_H
