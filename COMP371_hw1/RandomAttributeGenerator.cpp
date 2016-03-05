#include "stdafx.h"
#include "RandomAttributeGenerator.h"

RandomAttributeGenerator::RandomAttributeGenerator()
{
	srand(time(NULL));
}


RandomAttributeGenerator::~RandomAttributeGenerator()
{
}
void RandomAttributeGenerator::setRadius(int rad) {
	radius = rad;
}
void RandomAttributeGenerator::setPlayerPos(vec3 pos) {
	playerPos = pos;
}
void RandomAttributeGenerator::randomizeObject(object original, char type, objects &copies) {
	int min, max, nbOfCopies;

	if (type == 't') {
		min = 1;
		max = 2;
	}
	else if (type == 'p') {
		min = 10;
		max = 20;
	}
	else if (type == 'f') {
		min = 1;
		max = 2;
	}
	else if (type == 'g') {
		min = 1;
		max = 2;
	}

	nbOfCopies = rand() % max + min;
	for (int i = 0; i < nbOfCopies; ++i) {
		object obj = original;
		// generates a number between [-500,500]

		changeObjectLocation(obj);
		changeObjectSize(obj);
		
		
		copies.push_back(obj);
	}
}

void RandomAttributeGenerator::changeObjectLocation(object &obj) {

	int xTranslation = (rand() % (radius*2) - radius) + playerPos.x;
	int zTranslation = (rand() % (radius)) + playerPos.z + radius;
	for (size_t i = 0; i < obj.size(); i++) {
		obj[i][0] += (float)xTranslation;
		obj[i][2] += (float)zTranslation;
	}

}
void RandomAttributeGenerator::changeObjectSize(object &obj) {
	int xScale = (rand() % 10 + 1) / 10 + 1;
	int yScale = (rand() % 10 + 1) / 10 + 1;
	int zScale = (rand() % 10 + 1) / 10 + 1;
	for (size_t i = 0; i < obj.size(); i++) {
		obj[i][0] *= (float)xScale;
		obj[i][1] *= (float)yScale;
		obj[i][2] *= (float)zScale;
	}
}