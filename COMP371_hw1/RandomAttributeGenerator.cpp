#include "stdafx.h"
#include "RandomAttributeGenerator.h"

RandomAttributeGenerator::RandomAttributeGenerator()
{
	srand(time(NULL));
}


RandomAttributeGenerator::~RandomAttributeGenerator()
{
}

void RandomAttributeGenerator::randomizeObject(object original, char type, objects &copies) {
	int min, max, nbOfCopies;

	if (type == 't') {
		min = 10;
		max = 40;
	}
	else if (type == 'p') {
		min = 60;
		max = 100;
	}
	else if (type == 'f') {
		min = 1000;
		max = 5000;
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
	int xTranslation = rand() % 5000 - 2500;
	int zTranslation = rand() % 8000 - 2000;
	for (size_t i = 0; i < obj.size(); i++) {
		obj[i][0] += (float)xTranslation;
		obj[i][2] += (float)zTranslation;
	}

}
void RandomAttributeGenerator::changeObjectSize(object &obj) {

}