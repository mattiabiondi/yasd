#ifndef YASD_SESSION_H
#define YASD_SESSION_H

#include <QObject>
#include <QAction>
#include <QTimer>

#include "src/application.h"
#include "src/const.h"

enum Status {
	RUNNING,
	STOPPED
};

class QAction;
class QTimer;

class Session : public QObject {
Q_OBJECT

public:
Session();
~Session();

Status getStatus() const
{
	return status;
}

bool isStopped() const
{
	return status == STOPPED;
}

bool isRunning() const
{
	return status == RUNNING;
}

QAction *startAct;
QAction *stopAct;
QAction *toggleAct;
QAction *incSpeedAct;
QAction *decSpeedAct;

public slots:
void setSpeed(int speed);
void stop();

signals:
void statusChanged();
void speedChanged();
void sessionStarted();
void sessionStopped();
void iterationDone();

private:
void createActions();
void setStatus(Status status);
Status status;
QThread *thread;
QTimer *timer;

private slots:
void configurationChanged();
void timeout();
void start();
void toggle();
void increaseSpeed();
void decreaseSpeed();
void updateActions();
};

#endif // YASD_SESSION_H
