#ifndef YASD_TRACK_WINDOW_H
#define YASD_TRACK_WINDOW_H

#include "src/application.h"
#include "src/configuration.h"
#include "src/const.h"
#include "src/input.h"
#include "src/windows/cars/car.h"
#include "src/windows/track/track.h"

#include <QOpenGLWindow>
#include <QOpenGLFunctions>

#include <QPainter>
#include <QPen>
#include <QFont>

class Application;

class TrackWindow : public QOpenGLWindow,
	protected QOpenGLFunctions
{
Q_OBJECT

public:
TrackWindow();
~TrackWindow();

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

// Private Helpers
void printContextInformation();
};

#endif // YASD_TRACK_WINDOW_H
