#include "common.h"

float getRndFloat(float min, float max)	{
	return (max-min+1.0)*((float)rand() / RAND_MAX) + min;
}

int getRndInt(int min, int max) {
	return (rand() % (max-min)) + min;
}

float fabs(float number) {
	if(number<0) return -number; else return number;
}
