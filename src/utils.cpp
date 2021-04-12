#include <iostream>
#include <cmath>

using namespace std;

double getNumberWithOneDecimalDigit(double number)
{
	int tmpInt = int((number * 10 - (floor(number)) * 10));
	double tmpFloat = 0.0 + (double)tmpInt / 10;

	return tmpFloat;
}

double getRandomDouble(double max, double min)
{
	return ((double)rand() / RAND_MAX) * (max - min) + min;
}

int choose()
{
	int coin = rand() % 100;

	return coin % 2;
}

double *getArrayPortion(double *array, int start, int end)
{
	double *portion = new double[(end - start)];

	for (int i = start; i < end; i++)
		portion[i - start] = array[i];
	return portion;
}

