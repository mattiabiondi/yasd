#include "src/widgets/track/track.h"

#include <QPointF>
#include <iostream>
using namespace std;

Track::Track()
{
	this->friction = 0;
	this->numLines = 0;
	this->lines = nullptr;
}

Track::Track(int type, double friction)
{
	this->friction = friction;

	if (type == 0) {
		this->numLines = 0;
		this->lines = nullptr;
		return;
	}

	this->numLines = 0;
	this->lines = new QLineF * [8];

	QPointF *points[4] = {
		new QPointF(0,				 (CHUNKSIZE - TRACKSIZE) / 2),
		new QPointF((CHUNKSIZE - TRACKSIZE) / 2, (CHUNKSIZE - TRACKSIZE) / 2),
		new QPointF(0,				 CHUNKSIZE - (CHUNKSIZE - TRACKSIZE) / 2),
		new QPointF((CHUNKSIZE - TRACKSIZE) / 2, CHUNKSIZE - (CHUNKSIZE - TRACKSIZE) / 2)
	};

	for (int i = 0; i < 4; i++) {
		if (type >> (i) & 1) {
			this->lines[this->numLines++] = new QLineF(*points[0], *points[1]);
			this->lines[this->numLines++] = new QLineF(*points[2], *points[3]);
		} else {
			this->lines[this->numLines++] = new QLineF(*points[1], *points[3]);
		}

		//Funzione di rotazione
		QPointF *center = new QPointF(CHUNKSIZE / 2, CHUNKSIZE / 2);
		for (int j = 0; j < 4; j++) {
			*points[j] -= *center;

			double temp = points[j]->x();
			points[j]->setX(-1 * points[j]->y());
			points[j]->setY(temp);

			*points[j] += *center;
		}
	}
}

void Track::print(QPaintDevice *device, int x, int y)
{
	QPainter painter;

	painter.begin(device);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.setPen(QPen(Qt::yellow, 5, Qt::SolidLine, Qt::RoundCap));

	for (int k = 0; k < this->numLines; k++)
		painter.drawLine(this->lines[k]->translated(QPointF(x * CHUNKSIZE, y * CHUNKSIZE)));

	painter.end();
}
