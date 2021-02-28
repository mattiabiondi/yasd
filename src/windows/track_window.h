#ifndef YASD_TRACK_WINDOW_H
#define YASD_TRACK_WINDOW_H

#include "src/input.h"
#include "src/const.h"
#include "src/windows/cars/car.h"
#include "src/windows/track/track.h"

#include <QOpenGLWindow>
#include <QOpenGLFunctions>

#include <QPainter>
#include <QPen>
#include <QFont>

class TrackWindow : public QOpenGLWindow,
	protected QOpenGLFunctions
{
Q_OBJECT

// OpenGL Events
public:
TrackWindow();
~TrackWindow();

void initializeGL();
void paintGL();
protected slots:
void teardownGL();
void update();

protected:
void keyPressEvent(QKeyEvent *event);
void keyReleaseEvent(QKeyEvent *event);

private:
//Car *car;
Car **cars;
Track ***tracks;
time_t startTime;
int num_gen = 0;
// Private Helpers
void printContextInformation();
};



#endif // YASD_TRACK_WINDOW_H
