#include "src/widgets/track_widget.h"
#include "src/genetic_algorithm/genetic_algorithm_methods.h"

#include <QDebug>
#include <QString>
#include <QKeyEvent>
#include <ctime>
#include <vector>


using namespace std;

// These variables set the dimensions of the rectanglar region we wish to view.
const double Xmin = 0.0, Xmax = 3.0;
const double Ymin = 0.0, Ymax = 3.0;

TrackWidget::TrackWidget(QWidget *parent)
{
	srand((unsigned int)time(NULL));
	this->startTime = time(0);

	initTrack();
	initCars();

	// Accepts keyboard focus
	setFocusPolicy(Qt::StrongFocus);
}

TrackWidget::~TrackWidget()
{
	makeCurrent();
	teardownGL();
}

void TrackWidget::initTrack()
{
	int matrix[3][3] = { { 12, 14, 6 }, { 13, 15, 7 }, { 9, 11, 3 } };

	tracks = new Track * *[3];

	for (int i = 0; i < 3; i++) {
		tracks[i] = new Track *[3];
		for (int j = 0; j < 3; j++)
			tracks[i][j] = new Track(matrix[i][j], 1);
	}

	series = new QLineSeries();

}

void TrackWidget::initCars()
{
	config = Appl()->getConfig();
	n_red = config->getRed();
	n_green = config->getGreen();
	n_blue = config->getBlue();
	n_cars = n_red + n_green + n_blue;
	config->setGeneration(0);

	cars = new Car *[n_cars];

	QPointF spawn_point = QPointF(CHUNKSIZE / 3, CHUNKSIZE / 3);
	int i;

	for (i = 0; i < n_red; i++) {
		QPointF spawn_point = QPointF(CHUNKSIZE * (i / 3) + CHUNKSIZE / 2, CHUNKSIZE * (i % 3) + CHUNKSIZE / 2);
		cars[i] = new Car(REDTYPE, i, spawn_point, 0);
	}
	for (i = n_red; i < n_red + n_green; i++)
		cars[i] = new Car(GREENTYPE, i, spawn_point, 0);

	for (i = n_red + n_green; i < n_cars; i++)
		cars[i] = new Car(BLUETYPE, i, spawn_point, 0);
}

void TrackWidget::printTrack()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			tracks[i][j]->print(this, i, j);
}

void TrackWidget::printCar(Car *car)
{
	car->print(this);
}

void TrackWidget::moveCar(Car *car)
{
	if (car->isAlive()) {
		QPointF oldp = QPointF(car->getPosition());
		car->move();
		QPointF newp = QPointF(car->getPosition());

		checkCollisions(car, &oldp, &newp);
	}
}

void TrackWidget::checkCollisions(Car *car, QPointF *oldp, QPointF *newp)
{
	int x = newp->x() / CHUNKSIZE;
	int y = newp->y() / CHUNKSIZE;

	QLineF distance = QLineF(*oldp, *newp);
	QLineF **sensors = car->getSensors();

	// Check if collision with track borders
	for (int i = x - 1; i <= x + 1; i++) {
		if (i >= 0 && i < 3) {
			for (int j = y - 1; j <= y + 1; j++) {
				if (j >= 0 && j < 3) {
					for (int k = 0; k < tracks[i][j]->numLines; k++) {
						// Die if collision with track borders
						QPointF *intersection = new QPointF();
						if (distance.intersects(tracks[i][j]->lines[k]->translated(QPointF(i * CHUNKSIZE, j * CHUNKSIZE)), intersection) == QLineF::BoundedIntersection) {
							car->die();
							car->setPosition(*intersection);
						}
						delete intersection;

						// Update sensors lenght (do not cross track borders)
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

	// Check collision with other cars
	for (int l = 0; l < 5; l++) {
		for (int i = 0; i < n_cars; i++) {
			if (cars[i]->getId() != car->getId()) {
				for (int h = 0; h < 4; h++) {
					QPointF *intersection = new QPointF();
					if (sensors[l]->intersects(cars[i]->getHitbox()[h], intersection) == QLineF::BoundedIntersection) {
						sensors[l]->setP2(*intersection);
						for (int j = 0; j < 4; j++)
							if (car->getHitbox()[j].intersects(cars[i]->getHitbox()[h], intersection) == QLineF::BoundedIntersection) {
								car->die();
								cars[i]->die();
							}
					}
					delete intersection;
				}
			}
		}
	}
}

void TrackWidget::nextGeneration()
{
	vector<DNA*> DNAs;
	cout<< "\n next generation \n";

	for (int i = 0; i < n_cars; i++) {
		if (cars[i]->isAlive())
			cars[i]->die();
		cars[i]->getDNA()->setFitnessScore(fitnessFunction(cars[i]->getAliveTime(), cars[i]->getDistance()));
		DNAs.push_back(cars[i]->getDNA());
	}

	vector<DNA*> bestOfThisGen = pickBestDNAs(DNAs);
	DNA *newGenBaseDNA = crossover(bestOfThisGen);
	vector<DNA*> newGenerationDNAs = mutation(newGenBaseDNA, n_cars);

	for (int i = 0; i < n_cars; i++)
		delete cars[i];

	for (int i = 0; i < n_red; i++)
		cars[i] = new Car(REDTYPE, i, QPointF(CHUNKSIZE / 3 + (i * 20), CHUNKSIZE / 3 + (i * 20)), 0, 1, newGenerationDNAs[i]);

	for (int i = n_red; i < n_red + n_green; i++)
		cars[i] = new Car(GREENTYPE, i, QPointF(CHUNKSIZE / 3 + (i * 20), CHUNKSIZE / 3 + (i * 20)), 0, 1, newGenerationDNAs[i]);

	for (int i = n_red + n_green; i < n_cars; i++)
		cars[i] = new Car(BLUETYPE, i, QPointF(CHUNKSIZE / 3 + (i * 20), CHUNKSIZE / 3 + (i * 20)), 0, 1, newGenerationDNAs[i]);

	config->setGeneration(config->getGeneration() + 1);
	dynamic_cast<MainWindow *>(parent())->configDialog->update();
	
	bool isDialogVisible = (dynamic_cast<MainWindow *>(parent())->chartsDialog == NULL) ? false : true; 
	double score = bestOfThisGen[0]->getFitnessScore() + bestOfThisGen[1]->getFitnessScore();
	series->append(++this->currentGeneration,score);
	dynamic_cast<MainWindow *>(parent())->chartsDialog->update(series, isDialogVisible);
}

/*******************************************************************************
 * OpenGL Events
 ******************************************************************************/
void TrackWidget::initializeGL()
{
	// Initialize OpenGL Backend
	initializeOpenGLFunctions();
	connect(this, &QOpenGLWidget::frameSwapped, this, &TrackWidget::update);
	printContextInformation();
}

void TrackWidget::paintGL()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	grass = new QColor("#a3be8c");
	asphalt = new QColor("#4c566a");

	glClearColor(
		asphalt->redF(),
		asphalt->greenF(),
		asphalt->blueF(),
		asphalt->alphaF()
		);

	for (int i = 0; i < n_cars; i++)
		printCar(cars[i]);

	printTrack();

	// Flush the pipeline.  (Not usually necessary.)
	//glFlush();
}

void TrackWidget::teardownGL()
{
	// Actually destroy our OpenGL information

	//foo.destroy();
	//delete bar;

	delete cars;
	delete tracks;
}

void TrackWidget::update()
{
	// Update input
	Input::update();

	if (Input::keyPressed(Qt::Key_Up))
		nextGeneration();

	for (int i = 0; i < n_cars; i++)
		moveCar(cars[i]);

	// Schedule a redraw
	QOpenGLWidget::update();
}

void TrackWidget::keyPressEvent(QKeyEvent *event)
{
	if (event->isAutoRepeat())
		event->ignore();
	else
		Input::registerKeyPress(event->key());
}

void TrackWidget::keyReleaseEvent(QKeyEvent *event)
{
	if (event->isAutoRepeat())
		event->ignore();
	else
		Input::registerKeyRelease(event->key());
}

/*******************************************************************************
 * Private Helpers
 ******************************************************************************/
void TrackWidget::printContextInformation()
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
