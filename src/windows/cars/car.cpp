#include "src/windows/cars/car.h"

Car::Car(int type, int id, QPointF position, int angle, int firstTime, DNA dna)
{
	printf("%d type: ",type);
	this->alive = true;
	this->start = this->current = high_resolution_clock::now();
	this->movement = 0;

	this->type = type;
	this->position = position;
	this->angle = angle;
	this->speed = this->acceleration = 0;
	this->sensors = new QLineF *[NUMSENSORS];
	for (int i = 0; i < NUMSENSORS; i++)
		this->sensors[i] = new QLineF();
	this->setSensors();
	
	this->id = id;
	
	if(firstTime == 0) {
		this->dna = DNA(id);
	}
	
	else {
		this->dna = dna;
	}



	this->nn = initNeuralNetwork();

	// float a[5] = {11,7,23,2,22};
	// float* outputs = nn.feedForward(a, dna.genes);
	
	// printf("\n");
	// printf("%f",outputs[0]);
	// printf("\n");
	// printf("%f",outputs[1]);
	// printf("\n");

}

void Car::move()
{
	//this->acceleration = 0.1 + accelerationPercentage * this->speed;
	//this->speed = this->speed + this->acceleration;
	//this->angle = this->angle + 360 * rotationPercentage;
	if(!alive) return;

	QLineF ** sensors = this->getSensors();
	float *distances = new float();
	for(int i = 0; i<NUMSENSORS; i++){
		distances[i] = sensors[i]->length();
		// printf("%f", sensors[i]->length());
		// printf("\n");
	}


	float* outputs = nn.feedForward(distances, dna.genes);
	
	double accelerationPercentage = outputs[0];
	double rotationPercentage = outputs[1];

	// printf("\n");
	// printf("Output[0]: %f",outputs[0]);
	// printf("\n");
	// printf("Output[1]: %f",outputs[1]);
	// printf("\n");
 
	// TODO se una macchina rimane ferma per un tempo preso in input(per i test 1 min) distruggerla e darle una penalità
	
	// this->speed += (this->speed < 0.001) ? outputs[0] * 10 : this->speed * outputs[0];
	// this->angle += (this->angle < 0.001) ? outputs[1] * 10 : this->angle *outputs[1];
	
	this->speed += outputs[0] * SPEEDOFFSET;
	this->angle += outputs[1] * ANGLEOFFSET;

	// printf("old speed: %f", this->speed);
	// printf("\n");

	// printf("old angle: %f", this->angle);
	// printf("\n");

	//upper bound
	if(this->speed > 100.0) this->speed = 100.0; 
	this->angle = fmod(this->angle, 360.0);
	
	//lower bound
	if(this->speed < 0.0) this->speed = abs(this->speed); 
	// if(this->angle < 0.0) this->angle = 0.0; 


	// printf("new speed: %f", this->speed);
	// printf("\n");

	// printf("new angle: %f", this->angle);
	// printf("\n");

	high_resolution_clock::time_point prev = this->current;
	this->current = high_resolution_clock::now();
	duration<double, std::milli> time_span = this->current - prev;

	double t = time_span.count() / 1000;
	QPointF x = QPointF(this->speed * t * cos(this->angle * M_PI / 100), -this->speed * t * sin(this->angle * M_PI / 100));

	this->position += x;
	this->movement += QLineF(QPointF(0,0),x).length();
	// this->speed += (this->speed * outputs[0]);
	// this->angle += (this->angle *outputs[1]);


	// this->speed = accelerationPercentage;
	// this->angle += rotationPercentage;

	// *this->position += QPointF(speed * cos(this->angle * M_PI / 180), -speed * sin(this->angle * M_PI / 180));

	this->setSensors();
}

void Car::die(){
	this->alive = false;
	// duration<double, std::milli> time_span = this->current - this->start;
	this->aliveTime = this->current - this->start;
	cout << "La macchina è rimasta in vita per " << this->aliveTime.count() << " milli e ha percorso " << this->movement << " metri \n";
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
	painter.drawPoint(this->getPosition());

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

QPointF Car::getPosition()
{
	return position;
}

QLineF **Car::getSensors()
{
	return this->sensors;
}

void Car::setPosition(QPointF position){
	this->position = position;
	this->setSensors();
}

bool Car::isAlive(){
	return this->alive;
}

DNA Car::getDNA(){
	return this->dna;
}

double Car::getMovement(){
	return this->movement;
}

double Car::getAliveTime(){
	return (double)this->aliveTime.count();
}


// float * Car::arrayPortion(float *array, int start, int end){
//     float* portion = new float[(end-start)];

//     for (int i = start; i < end ;i++) {
// 		portion[i - start] = array[i];
//     }
//     return portion;
// }

NeuralNetwork Car::initNeuralNetwork(){
	NeuralNetwork nn = NeuralNetwork(5,7,2);

	float  **inputs_to_hidden_weights = nn.getMatrixWithWeights(7,5, getArrayPortion(this->dna.genes,0 ,35));
    float **hidden_to_output_weights = nn.getMatrixWithWeights(2,7, getArrayPortion(this->dna.genes,35 ,49));
    float *inputs_to_hidden_bias = getArrayPortion(this->dna.genes,49,56);
    float *hidden_to_output_bias = getArrayPortion(this->dna.genes,56,58);
	
    nn.initNNParams(inputs_to_hidden_weights, hidden_to_output_weights, inputs_to_hidden_bias, hidden_to_output_bias);
	
	return nn;
}