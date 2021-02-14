#include "src/windows/cars/car.h"

Car::Car(int type, QPointF *position, int angle)
{
	this->type = type;
	this->position = position;
	this->angle = angle;
	this->speed = this->acceleration = 0;

	this->sensors = new QLineF *[NUMSENSORS];
	for (int i = 0; i < NUMSENSORS; i++)
		this->sensors[i] = new QLineF();
	this->setSensors();
}

void Car::move(double accelerationPercentage, double rotationPercentage)
{
	//this->acceleration = 0.1 + accelerationPercentage * this->speed;
	//this->speed = this->speed + this->acceleration;
	//this->angle = this->angle + 360 * rotationPercentage;
	this->speed = accelerationPercentage;
	this->angle += rotationPercentage;

	*this->position += QPointF(speed * cos(this->angle * M_PI / 180), -speed * sin(this->angle * M_PI / 180));

	this->setSensors();
}

void Car::print(QPaintDevice *device)
{
	QPainter painter;

	painter.begin(device);
	painter.setRenderHint(QPainter::Antialiasing);

	//Stampa dei sensori
	painter.setPen(QPen(Qt::magenta, 5, Qt::DashDotLine, Qt::RoundCap));

	for (int i = 0; i < 5; i++)
		painter.drawLine(*this->sensors[i]);

	QColor color;

	if (this->type == 0)
		color = QColor(Qt::red);
	else if (this->type == 1)
		color = QColor(Qt::green);
	else
		color = QColor(Qt::blue);

	QBrush brush = QBrush(color, Qt::SolidPattern);

	painter.setPen(QPen(brush, 35, Qt::SolidLine, Qt::RoundCap));

	//Stampa della posizione della macchina
	painter.drawPoint(*this->getPosition());

	painter.end();
}

void Car::setSensors()
{
	for (int i = 0; i < NUMSENSORS; i++) {
		this->sensors[i]->setP1(*this->position);
		this->sensors[i]->setAngle(this->angle - 90 + i * 45);
		this->sensors[i]->setLength(MINSENSORS + (SENSORSOFFSET * this->type));
	}
}

QPointF *Car::getPosition()
{
	return position;
}

QLineF **Car::getSensors()
{
	return this->sensors;
}
