#ifndef YASD_MAP_TAB_H
#define YASD_MAP_TAB_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QtMath>

#include "src/application.h"

const int points = 2 * M_PI * 100; // 2 * 3.14 = 6.28 * 100 = 628

class TrackTab : public QWidget {
Q_OBJECT

public:
TrackTab(QWidget *parent = 0);

public slots:
void update();

protected slots:
void wheelEvent(QWheelEvent *event);

private:
void addTrack(QGraphicsScene *scene, QColor *material, int crossroads);
void lissajous(int a, int b);
QVBoxLayout *vBoxLayout;
QGraphicsScene *scene;
QGraphicsView *view;
QGraphicsPathItem *track;
QColor *grass;
QColor *asphalt;
QPointF curve[points];
};

#endif // YASD_MAP_TAB_H
