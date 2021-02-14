#include "src/windows/track_window.h"

#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QKeyEvent>

// These variables set the dimensions of the rectanglar region we wish to view.
const double Xmin = 0.0, Xmax = 3.0;
const double Ymin = 0.0, Ymax = 3.0;

TrackWindow::TrackWindow()
{
	int matrix[3][3] = { { 12, 14, 6 }, { 13, 15, 7 }, { 9, 11, 3 } };
	QPointF *start = new QPointF(CHUNKSIZE / 2, CHUNKSIZE / 2);

	cars = new Car *[3];
	for (int i = 0; i < 3; i++) {
		QPointF *point = new QPointF(CHUNKSIZE / 2 + i * 100, CHUNKSIZE / 2 + i * 100);
		cars[i] = new Car(i, point, 0);
	}

	//car = new Car(start, 0);
	tracks = new Track * *[3];

	for (int i = 0; i < 3; i++) {
		tracks[i] = new Track *[3];
		for (int j = 0; j < 3; j++)
			tracks[i][j] = new Track(matrix[i][j], 1);
	}
}

TrackWindow::~TrackWindow()
{
	makeCurrent();
	teardownGL();
}

/*******************************************************************************
 * OpenGL Events
 ******************************************************************************/
void TrackWindow::initializeGL()
{
	// Initialize OpenGL Backend
	initializeOpenGLFunctions();
	connect(this, &QOpenGLWindow::frameSwapped, this, &TrackWindow::update);
	printContextInformation();
}

void TrackWindow::paintGL()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// painter.setPen(QPen(Qt::white, 5, Qt::SolidLine, Qt::RoundCap));
	//
	// //Stampa della posizione della macchina
	// painter.drawPoint(*car->getPosition());
	//
	// //Stampa dei sensori
	// painter.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap));
	// QLineF **sensors = car->getSensors();
	//
	// for (int i = 0; i < 5; i++)
	// 	painter.drawLine(*sensors[i]);

	for (int i = 0; i < 3; i++)
		cars[i]->print(this);

	QPainter painter;

	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.setPen(QPen(Qt::yellow, 5, Qt::SolidLine, Qt::RoundCap));
	//Stampa della strada
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < tracks[i][j]->numLines; k++)
				painter.drawLine(tracks[i][j]->lines[k]->translated(QPointF(i * CHUNKSIZE, j * CHUNKSIZE)));

			//painter.drawLines(*tracks[i][j]->lines, tracks[i][j]->numLines);
			//painter.save();
		}
	}

	painter.end();

	// Flush the pipeline.  (Not usually necessary.)
	//glFlush();
}

void TrackWindow::teardownGL()
{
	// Actually destroy our OpenGL information

	//foo.destroy();
	//delete bar;
}

void TrackWindow::update()
{
	// Update input
	Input::update();

	// if (Input::keyPressed(Qt::Key_Up))
	// 	car->move(5, 0);
	// else if (Input::keyPressed(Qt::Key_Down))
	// 	car->move(-5, 0);
	// else if (Input::keyPressed(Qt::Key_Left))
	// 	car->move(0, 1);
	// else if (Input::keyPressed(Qt::Key_Right))
	// 	car->move(0, -1);
	// //Ricacolare intersezioni e distanze
	// QLineF **sensors = car->getSensors();

	for (int i = 0; i < 3; i++) {
		if (Input::keyPressed(Qt::Key_Up))
			cars[i]->move(5, 0);
		else if (Input::keyPressed(Qt::Key_Down))
			cars[i]->move(-5, 0);
		else if (Input::keyPressed(Qt::Key_Left))
			cars[i]->move(0, 1);
		else if (Input::keyPressed(Qt::Key_Right))
			cars[i]->move(0, -1);
	}

	for (int a = 0; a < 3; a++) {
		QLineF **sensors = cars[a]->getSensors();
		int x = cars[a]->getPosition()->x() / CHUNKSIZE;
		int y = cars[a]->getPosition()->y() / CHUNKSIZE;

		for (int i = x - 1; i <= x + 1; i++)
			if (i >= 0 && i < 3) {
				for (int j = y - 1; j <= y + 1; j++)
					if (j >= 0 && j < 3) {
						for (int k = 0; k < tracks[i][j]->numLines; k++)
							for (int l = 0; l < 5; l++) {
								QPointF *intersection = new QPointF();
								if (sensors[l]->intersects(tracks[i][j]->lines[k]->translated(QPointF(i * CHUNKSIZE, j * CHUNKSIZE)), intersection) == QLineF::BoundedIntersection)
									sensors[l]->setP2(*intersection);
							}
					}
			}
	}

	// Schedule a redraw
	QOpenGLWindow::update();
}

void TrackWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->isAutoRepeat())
		event->ignore();
	else
		Input::registerKeyPress(event->key());
}

void TrackWindow::keyReleaseEvent(QKeyEvent *event)
{
	if (event->isAutoRepeat())
		event->ignore();
	else
		Input::registerKeyRelease(event->key());
}

/*******************************************************************************
 * Private Helpers
 ******************************************************************************/
void TrackWindow::printContextInformation()
{
	QString glType;
	QString glVersion;
	QString glProfile;

	// Get Version Information
	glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
	glVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));

	// Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
	switch (format().profile()) {
		CASE(NoProfile);
		CASE(CoreProfile);
		CASE(CompatibilityProfile);
	}
#undef CASE

	// qPrintable() will print our QString w/o quotes around it.
	qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}
