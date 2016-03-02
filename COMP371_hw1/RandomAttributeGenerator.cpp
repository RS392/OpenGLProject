#include "stdafx.h"
#include "RandomAttributeGenerator.h"


RandomAttributeGenerator::RandomAttributeGenerator()
{
	srand(time(NULL));
}


RandomAttributeGenerator::~RandomAttributeGenerator()
{
}

object RandomAttributeGenerator::generateObjectAtDiffLocations(object original, char type) {
	object obj = original;
	// generates a number between [-500,500]
	int xTranslation = rand() % 1000 - 500;

	
	int zTranslation = rand() % 800 - 200;
	for (size_t i = 0; i < original.size(); i++) {	
		obj[i][0] += (float)xTranslation;
		obj[i][2] += (float)zTranslation;
	}

	return obj;
}