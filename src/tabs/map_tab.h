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

class MapTab : public QWidget {
Q_OBJECT

public:
MapTab(QWidget *parent = 0);

private:
void addTrack(QGraphicsScene *scene, QColor *material, int crossroads);
void lissajous(int a, int b);
QColor *grass;
QColor *asphalt;
QPointF curve[points];
};

#endif // YASD_MAP_TAB_H
