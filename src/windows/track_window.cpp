#include "src/windows/track_window.h"
#include "src/genetic_algorithm/genetic_algorithm_methods.h"
#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QKeyEvent>
#include <ctime>
#include <vector>


// These variables set the dimensions of the rectanglar region we wish to view.
const double Xmin = 0.0, Xmax = 3.0;
const double Ymin = 0.0, Ymax = 3.0;

TrackWindow::TrackWindow()
{
	srand((unsigned int)time(NULL));
	this->startTime = time(0);
	int matrix[3][3] = { { 12, 14, 6 }, { 13, 15, 7 }, { 9, 11, 3 } };

	cars = new Car *[12];
	for (int i = 0; i < 12; i++) {
		QPointF point = QPointF(CHUNKSIZE / 3, CHUNKSIZE / 3);
		cars[i] = new Car(i % 3, i, point, 0);
	}

	tracks = new Track **[3];

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

	for (int i = 0; i < 12; i++)
		cars[i]->print(this);

	//Stampa della strada
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			tracks[i][j]->print(this, i, j);

	// Flush the pipeline.  (Not usually necessary.)
	//glFlush();
}

void TrackWindow::teardownGL()
{
	// Actually destroy our OpenGL information

	//foo.destroy();
	//delete bar;

	delete cars;
	delete tracks;
}

void TrackWindow::update()
{
	// Update input
	Input::update();

	// if(time(0) - this->startTime > 10) {
	if (Input::keyPressed(Qt::Key_Up)) {
		vector<DNA> DNAs;
		for (int a = 0; a < 12; a++) {
			if (cars[a]->isAlive())
				cars[a]->die();
			// cars[a]->movement = 0;
			cars[a]->getDNA().setFitnessScore(fitnessFunction(cars[a]->getAliveTime(), cars[a]->getMovement()));
			DNAs.push_back(cars[a]->getDNA());
		}

		vector<DNA> bestOfThisGen = pickBestDNAs(DNAs);
		DNA newGenBaseDNA = crossover(bestOfThisGen);
		vector<DNA> newGenerationDNAs = mutation(newGenBaseDNA, 12);

		QPointF point = QPointF(CHUNKSIZE / 3, CHUNKSIZE / 3);

		for (int i = 0; i < 12; i++) {
			delete cars[i];
			cars[i] = new Car(i % 3, i, QPointF(CHUNKSIZE / 3 + (i * 5), CHUNKSIZE / 3 + (i * 5)), 0, 1, newGenerationDNAs[i]);
		}
		num_gen++;
		cout << "\n\nGeneration: " << num_gen << "\n\n";
	}

	for (int a = 0; a < 12; a++) {
		QPointF oldp = QPointF(cars[a]->getPosition());
		cars[a]->move();

		QPointF newp = QPointF(cars[a]->getPosition());
		int x = newp.x() / CHUNKSIZE;
		int y = newp.y() / CHUNKSIZE;




		if (newp != oldp) {
			QLineF movement = QLineF(oldp, newp);
			for (int i = x - 1; i <= x + 1; i++) {
				if (i >= 0 && i < 3) {
					for (int j = y - 1; j <= y + 1; j++) {
						if (j >= 0 && j < 3) {
							for (int k = 0; k < tracks[i][j]->numLines; k++) {
								QPointF *intersection = new QPointF();
								if (movement.intersects(tracks[i][j]->lines[k]->translated(QPointF(i * CHUNKSIZE, j * CHUNKSIZE)), intersection) == QLineF::BoundedIntersection) {
									cars[a]->die();
									cars[a]->setPosition(*intersection);
								}
								delete intersection;
							}
						}
					}
				}
			}
		}
		QLineF **sensors = cars[a]->getSensors();
		for (int i = x - 1; i <= x + 1; i++) {
			for (int i = x - 1; i <= x + 1; i++) {
				if (i >= 0 && i < 3) {
					for (int j = y - 1; j <= y + 1; j++) {
						if (j >= 0 && j < 3) {
							for (int k = 0; k < tracks[i][j]->numLines; k++) {
								for (int l = 0; l < 5; l++) {
									QPointF *intersection = new QPointF();
									if (sensors[l]->intersects(tracks[i][j]->lines[k]->translated(QPointF(i * CHUNKSIZE, j * CHUNKSIZE)), intersection) == QLineF::BoundedIntersection)
										sensors[l]->setP2(*intersection);
									delete intersection;
								}
							}
						}
					}
				}
			}
		}
	}


	// for (int a = 0; a < 3; a++) {
	// QLineF **sensors = cars[a]->getSensors();
	// int x = cars[a]->getPosition()->x() / CHUNKSIZE;
	// int y = cars[a]->getPosition()->y() / CHUNKSIZE;

	// for (int i = x - 1; i <= x + 1; i++)
	// 	if (i >= 0 && i < 3) {
	// 		for (int j = y - 1; j <= y + 1; j++)
	// 			if (j >= 0 && j < 3) {
	// 				for (int k = 0; k < tracks[i][j]->numLines; k++)
	// 					for (int l = 0; l < 5; l++) {
	// 						QPointF *intersection = new QPointF();
	// 						if (sensors[l]->intersects(tracks[i][j]->lines[k]->translated(QPointF(i * CHUNKSIZE, j * CHUNKSIZE)), intersection) == QLineF::BoundedIntersection)
	// 							sensors[l]->setP2(*intersection);
	// 		}
	// 	}
	// }
	// }

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
