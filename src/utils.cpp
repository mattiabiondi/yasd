#include <iostream>
#include <cmath>

using namespace std;

float getNumberWithOneDecimalDigit(float number){
    int tmpInt = int((number*10 - (floor(number))*10));
    float tmpFloat = 0.0 + (float)tmpInt/10;
    return tmpFloat;
}

float getRandomFloat(float max, float min){
    return ((float)rand() / RAND_MAX) * (max - min) + min;
}

int choose(){
    int coin = rand() % 100;
    return coin % 2;
}

float *getArrayPortion(float *array, int start, int end){
    float* portion = new float[(end-start)];
    for (int i = start; i < end ;i++) {
        portion[i - start] = array[i];
    }
    return portion;
}

