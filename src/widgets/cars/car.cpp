#include "src/widgets/cars/car.h"

Car::Car(int type, int id, QPointF position, double angle, int firstTime, DNA dna)
{
	this->alive = true;
	aliveTime = 0;
	this->distance = 0;

	this->type = type;
	this->position = position;
	this->angle = angle;
	this->speed = this->acceleration = 0;

	this->sensors = new QLineF *[NUMSENSORS];
	for (int i = 0; i < NUMSENSORS; i++)
		this->sensors[i] = new QLineF();

	this->setSensors();
	this->setHitbox();

	this->id = id;

	if (firstTime == 0)
		this->dna = DNA(id);
	else
		this->dna = dna;

	this->nn = initNeuralNetwork();
}

void Car::move()
{
	// Note: QLineF::length() returns double
	double *distances = new double[NUMSENSORS];

	for (int i = 0; i < NUMSENSORS; i++)
		distances[i] = this->sensors[i]->length();
	// outputs[0]: acceleration percentage
	// outputs[1]: rotation percentage
	double *outputs = nn.feedForward(distances);

	delete[] distances;

	// TODO se una macchina rimane ferma per un tempo preso in input(per i test 1 min) distruggerla e darle una penalità

	this->speed += outputs[0] * SPEEDOFFSET;
	this->angle -= outputs[1] * ANGLEOFFSET;

	// upper bound
	if (this->speed > 100.0) this->speed = 100.0;

	// lower bound
	if (this->speed < 0.0) this->speed = abs(this->speed);

	// 1000ms/60 (= 60fps) --> default time span between frames
	// we take 60fps as "standard"
	double time_span = 1.0 / 60;
	QPointF x = QPointF(this->speed * time_span * cos(-this->angle * M_PI / 180), this->speed * time_span * sin(-this->angle * M_PI / 180));

	aliveTime += time_span;

	this->position += x;
	this->distance += QLineF(QPointF(0, 0), x).length();

	this->setSensors();
	this->setHitbox();
}

void Car::die()
{
	this->alive = false;
	cout << "Car " << id << " lasted " << this->aliveTime << "s and traveled " << this->distance << "m" << endl;
}

void Car::print(QPaintDevice *device)
{
	QPainter painter;

	painter.begin(device);
	painter.setRenderHint(QPainter::Antialiasing);

	// Draw sensors
	painter.setPen(QPen(Qt::magenta, 5, Qt::DashDotLine, Qt::RoundCap));
	for (int i = 0; i < NUMSENSORS; i++)
		painter.drawLine(*this->sensors[i]);

	QColor outline_color;
	QColor infill_color;

	switch (this->type) {
	case REDTYPE:
		infill_color = QColor(Qt::red);
		outline_color = QColor(Qt::darkRed);
		break;
	case GREENTYPE:
		infill_color = QColor(Qt::green);
		outline_color = QColor(Qt::darkGreen);
		break;
	case BLUETYPE:
	default:
		infill_color = QColor(Qt::blue);
		outline_color = QColor(Qt::darkBlue);
		break;
	}
	QBrush infill = QBrush(infill_color, Qt::SolidPattern);
	QBrush outline = QBrush(outline_color, Qt::SolidPattern);

	// Draw car outline
	QPainterPath path;

	path.moveTo(this->hitbox[0].p1());
	for (int i = 0; i < 3; i++) {
		path.lineTo(this->hitbox[i].p2());
		path.lineTo(this->hitbox[i + 1].p1());
	}
	path.lineTo(this->hitbox[3].p2());
	path.closeSubpath();

	painter.setPen(QPen(outline, 5, Qt::SolidLine, Qt::RoundCap));
	painter.drawPath(path);

	// Fill car outline with color
	painter.fillPath(path, infill);

	painter.end();
}

void Car::setSensors()
{
	for (int i = 0; i < NUMSENSORS; i++) {
		this->sensors[i]->setP1(this->position);
		this->sensors[i]->setAngle(this->angle - 90 + i * 45);
		this->sensors[i]->setLength(MINSENSORS + (SENSORSOFFSET * this->type));
	}
}

void Car::setHitbox()
{
	double x = this->position.x();
	double y = this->position.y();

	double half_lenght = CAR_LENGTH / 2;
	double half_width = CAR_WIDTH / 2;

	double c = cos(this->angle * (M_PI / 180));
	double s = sin(this->angle * (M_PI / 180));

	double r1x = -half_lenght * c - half_width * s;
	double r1y = -half_lenght * s + half_width * c;
	double r2x = half_lenght * c - half_width * s;
	double r2y = half_lenght * s + half_width * c;

	QPointF top_left = QPointF(x - r2x, y + r2y);
	QPointF top_right = QPointF(x - r1x, y + r1y);
	QPointF bottom_right = QPointF(x + r2x, y - r2y);
	QPointF bottom_left = QPointF(x + r1x, y - r1y);

	this->hitbox[0] = QLineF(top_right, bottom_right);
	this->hitbox[1] = QLineF(bottom_right, bottom_left);
	this->hitbox[2] = QLineF(bottom_left, top_left);
	this->hitbox[3] = QLineF(top_left, top_right);
}

QPointF Car::getPosition()
{
	return position;
}

QLineF **Car::getSensors()
{
	return this->sensors;
}

QLineF *Car::getHitbox()
{
	return this->hitbox;
}

void Car::setPosition(QPointF position)
{
	this->position = position;
	this->setSensors();
}

bool Car::isAlive()
{
	return this->alive;
}

int Car::getId()
{
	return this->id;
}

DNA Car::getDNA()
{
	return this->dna;
}

double Car::getDistance()
{
	return this->distance;
}

double Car::getAliveTime()
{
	return this->aliveTime / 1000;
}

NeuralNetwork Car::initNeuralNetwork()
{
	NeuralNetwork nn = NeuralNetwork(5, 7, 2);

	double **inputs_to_hidden_weights = nn.getMatrixWithWeights(7, 5, getArrayPortion(this->dna.genes, 0, 35));
	double **hidden_to_output_weights = nn.getMatrixWithWeights(2, 7, getArrayPortion(this->dna.genes, 35, 49));
	double *inputs_to_hidden_bias = getArrayPortion(this->dna.genes, 49, 56);
	double *hidden_to_output_bias = getArrayPortion(this->dna.genes, 56, 58);

	nn.initNNParams(inputs_to_hidden_weights, hidden_to_output_weights, inputs_to_hidden_bias, hidden_to_output_bias);

	return nn;
}
