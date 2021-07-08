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


//base
//int matrix[3][3] = { { 12, 14, 6 }, { 13, 15, 7 }, { 9, 11, 3 } };
//4
//int matrix[4][4] = { { 12, 6, 12, 6 }, { 9, 15, 15, 3}, { 12, 15, 15, 6 }, {9, 3, 9, 3}};
//1
//int matrix[3][3] = { { 12, 6, 0 }, { 9, 15, 6}, { 0, 9, 3 }};
//8
// int matrix[4][4] = { { 12, 14, 10, 6 }, { 5, 13, 14, 7}, { 13, 11, 7, 5 }, {9, 10, 11, 3}};


/*
3 -> 3
5 -> 10
6 -> 9
7 -> 11
9 -> 6
10 -> 5
11 -> 7
12 -> 12
13 -> 14 
14 -> 13
15 -> 15

*/


//base
//int matrix[3][3] = { { 12, 13, 9 }, { 14, 15, 11 }, { 6, 7, 3 } };
//4
//int matrix[4][4] = { { 12, 9, 12, 9 }, { 6, 15, 15, 3}, { 12, 15, 15, 9 }, {6, 3, 6, 3}};
//1
//int matrix[3][3] = { { 12, 9, 0 }, { 6, 15, 9}, { 0, 6, 3 }};
//8
int matrix[4][4] = { { 12, 13, 5, 9 }, { 10, 14, 13, 11}, { 14, 7, 11, 10 }, {6, 5, 7, 3}};



int rows = sizeof(matrix) / sizeof(matrix[0]);
int columns = sizeof(matrix[0]) / sizeof(int); 


TrackWidget::TrackWidget(QWidget *parent)
	: session(Appl()->getSession())
{
	srand((unsigned int)time(NULL));
	this->startTime = time(0);

	initTrack();
	initCars();

	session->setSpeed(Appl()->getConfig()->getSpeed());

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
	//int matrix[3][3] = { { 12, 14, 6 }, { 13, 15, 7 }, { 9, 11, 3 } };
	//4
	//int matrix[4][4] = { { 12, 6, 12, 6 }, { 9, 15, 15, 3}, { 12, 15, 15, 6 }, {9, 3, 9, 3}};
	//1
	//int matrix[3][3] = { { 12, 6, 0 }, { 9, 15, 6}, { 0, 9, 3 }};
	//8
	//int matrix[4][4] = { { 12, 14, 10, 6 }, { 5, 13, 14, 7}, { 13, 11, 7, 5 }, {9, 10, 11, 3}};
	
	tracks = new Track * *[rows];

	for (int i = 0; i < rows; i++) {
		tracks[i] = new Track *[columns];
		for (int j = 0; j < columns; j++)
			tracks[i][j] = new Track(matrix[i][j], 1);
	}

	series = new QLineSeries();
}

void TrackWidget::spawnCars(vector<DNA *> DNAs)
{
	int i, empty;
	
	if (DNAs.empty()) {
		for (i = 0; i < n_cars; i++)
			DNAs.push_back(new DNA(i));
	}

	for (i = 0, empty = 0; i < n_red; i++) {
		if(matrix[(i + empty)/ rows][(i + empty) % rows] == 0)
			empty++;
		QPointF spawn_point = QPointF(CHUNKSIZE * ((i + empty) / rows) + CHUNKSIZE / 2, CHUNKSIZE * ((i + empty) % rows) + CHUNKSIZE / 2);
		cars[i] = new Car(REDTYPE, i, spawn_point, 0, DNAs[i]);
	}

	for (; i < n_red + n_green; i++) {
		if(matrix[(i + empty) / rows][(i + empty) % rows] == 0)
			empty++;

		QPointF spawn_point = QPointF(CHUNKSIZE * ((i + empty) / rows) + CHUNKSIZE / 2, CHUNKSIZE * ((i + empty) % rows) + CHUNKSIZE / 2);
		cars[i] = new Car(GREENTYPE, i, spawn_point, 0, DNAs[i]);
	}

	for (; i < n_cars; i++) {
		if(matrix[(i + empty) / rows][(i + empty) % rows] == 0)
			empty++;

		QPointF spawn_point = QPointF(CHUNKSIZE * ((i + empty) / rows) + CHUNKSIZE / 2, CHUNKSIZE * ((i + empty) % rows) + CHUNKSIZE / 2);
		cars[i] = new Car(BLUETYPE, i, spawn_point, 0, DNAs[i]);
	}
}

void TrackWidget::initCars()
{
	config = Appl()->getConfig();
	n_red = config->getRed();
	n_green = config->getGreen();
	n_blue = config->getBlue();
	n_cars = n_red + n_green + n_blue;

	cars = new Car *[n_cars];
	vector<DNA *> vect;

	this->spawnCars(vect);
}

void TrackWidget::printTrack()
{
	
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			// tracks[i][j]->print(this, i, j);
			QPainter painter;
			painter.begin(this);
			// string filename = "/home/vincenzo/Documents/yasd/assets/";
			// strcat(filename,std::toString(matrix[i]));
			// strcat(filename,".png");
			painter.drawImage(QRect(CHUNKSIZE*j , CHUNKSIZE*i , CHUNKSIZE, CHUNKSIZE), QImage(QString ("../assets/%1.png").arg(matrix[i][j])));
			tracks[i][j]->print(this, i, j);
			// std::i << ": "<<QString ("/home/vincenzo/Documents/yasd/assets/%1.png").arg(matrix[i][j])<<"\n";
		}
	}

		// for (int i = 0; i < rows; i++){
		// 	for (int j = 0; j < columns; j++){
		// 		tracks[i][j]->print(this, i, j);
		// 	}
		// }
			
	
}

void TrackWidget::printCar(Car *car)
{
	car->print(this);
}

void TrackWidget::moveCars()
{
	if (session->isRunning())
		for (int i = 0; i < n_cars; i++)
			moveCar(cars[i]);
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
		if (i >= 0 && i < rows) {
			for (int j = y - 1; j <= y + 1; j++) {
				if (j >= 0 && j < columns) {
					for (int k = 0; k < tracks[i][j]->numLines; k++) {
						// Die if collision with track borders
						QPointF *intersection = new QPointF();
						if (distance.intersects(tracks[i][j]->lines[k]->translated(QPointF(j * CHUNKSIZE, i * CHUNKSIZE)), intersection) == QLineF::BoundedIntersection) {
							car->die();
							car->setPosition(*intersection);
						}
						delete intersection;

						// Update sensors lenght (do not cross track borders)
						for (int l = 0; l < 5; l++) {
							QPointF *intersection = new QPointF();
							if (sensors[l]->intersects(tracks[i][j]->lines[k]->translated(QPointF(j * CHUNKSIZE, i * CHUNKSIZE)), intersection) == QLineF::BoundedIntersection)
								sensors[l]->setP2(*intersection);
							delete intersection;
						}
					}
				}
			}
		}
	}

	// Check collision with other cars
	for (int l = 0; l < NUMSENSORS && car->isAlive(); l++) {
		for (int i = 0; i < n_cars && car->isAlive(); i++) {
			if (cars[i]->getId() != car->getId()) {
				for (int h = 0; h < 4 && car->isAlive(); h++) {
					QPointF *intersection = new QPointF();
					if (sensors[l]->intersects(cars[i]->getHitbox()[h], intersection) == QLineF::BoundedIntersection) {
						sensors[l]->setP2(*intersection);
						for (int j = 0; j < 4 && car->isAlive(); j++)
							if (car->getHitbox()[j].intersects(cars[i]->getHitbox()[h], intersection) == QLineF::BoundedIntersection)
								car->die();
					}
					delete intersection;
				}
			}
		}
	}
}

void TrackWidget::nextGeneration()
{
	vector<DNA *> DNAs;

	for (int i = 0; i < n_cars; i++) {
		if (cars[i]->isAlive())
			cars[i]->die();
		cars[i]->getDNA()->setFitnessScore(fitnessFunction(cars[i]->getAliveTime(), cars[i]->getDistance()));
		DNAs.push_back(cars[i]->getDNA());
	}

	vector<DNA *> bestOfThisGen = pickBestDNAs(DNAs);
	DNA *newGenBaseDNA = crossover(bestOfThisGen);
	vector<DNA *> newGenerationDNAs = mutation(newGenBaseDNA, n_cars);

	for (int i = 0; i < n_cars; i++)
		delete cars[i];

	spawnCars(newGenerationDNAs);

	config->setGeneration(config->getGeneration() + 1);
	dynamic_cast<MainWindow *>(parent())->configDialog->update();

	cout << "Generation: " << config->getGeneration() << endl;

	bool isDialogVisible = (dynamic_cast<MainWindow *>(parent())->chartsDialog == NULL) ? false : true;
	double score = bestOfThisGen[0]->getFitnessScore() + bestOfThisGen[1]->getFitnessScore();

	series->append(config->getGeneration(), score);
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
	connect(session, &Session::iterationDone, this, &TrackWidget::moveCars);
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

	printTrack();

	for (int i = 0; i < n_cars; i++)
		printCar(cars[i]);


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

	if (Input::keyTriggered(Qt::Key_Up))
		nextGeneration();

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
