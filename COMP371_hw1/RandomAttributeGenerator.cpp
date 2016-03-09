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
void RandomAttributeGenerator::setOldPlayerPos(vec3 pos) {
	oldPlayerPos = pos;
}
unsigned int RandomAttributeGenerator::generateRandomInt(unsigned long a, unsigned long b, unsigned long c) {
	
		a = a - b;  a = a - c;  a = a ^ (c >> 13);
		b = b - c;  b = b - a;  b = b ^ (a << 8);
		c = c - a;  c = c - b;  c = c ^ (b >> 13);
		a = a - b;  a = a - c;  a = a ^ (c >> 12);
		b = b - c;  b = b - a;  b = b ^ (a << 16);
		c = c - a;  c = c - b;  c = c ^ (b >> 5);
		a = a - b;  a = a - c;  a = a ^ (c >> 3);
		b = b - c;  b = b - a;  b = b ^ (a << 10);
		c = c - a;  c = c - b;  c = c ^ (b >> 15);
		return c;

}
void RandomAttributeGenerator::randomizeObject(Object original, char type, objects &copies) {
	
	
	srand(generateRandomInt(clock(), time(NULL), GetCurrentProcessId()));
	int min, max, nbOfCopies;
	vec3 distanceTraveled = playerPos - oldPlayerPos;
	//cout << distanceTraveled[2] << endl;
	double multiplier = 5;
	if (type == 't') {
		min = 1;
		max = 2;
	}
	else if (type == 'p') {
		min = 50;
		max = 100;
	}
	else if (type == 'f') {
		min = 50;
		max = 100;
	}
	else if (type == 'g') {
		min = 100;
		max = 150;
	}

	nbOfCopies = rand() % max + min;
	for (int i = 0; i < nbOfCopies; ++i) {
		Object obj = original;
		//thread t(&RandomAttributeGenerator::alterObj, this, ref(obj), ref(copies));
		//t.detach();
		alterObj(obj, copies);
		//changeObjectLocation(obj);
		//if (type != 'g')
		//	changeObjectSize(obj);

	//	cout << obj.verts[2][2] << endl;
		
		//copies.push_back(obj);
	}
}
void RandomAttributeGenerator::alterObj(Object &obj, objects &copies) {
//	cout << "trying to do one object" << endl;
	m.lock();
//	cout << "doing one object" << endl;
	
	//cout << obj.verts[2][2] << endl;
	changeObjectLocation(obj);
	//cout << obj.verts[2][2] << endl;
	changeObjectSize(obj);
	//cout << "modifying arrary..." << endl;
	copies.push_back(obj);
	m.unlock();
}
void RandomAttributeGenerator::changeObjectLocation(Object &obj) {

	int xTranslation = (rand() % (radius*2) - radius) + playerPos.x;
	int zTranslation = (rand() % (radius)) + radius + playerPos.z;

	for (int i = 0; i < obj.verts.size(); i++) {
		obj.verts[i][0] += (float)xTranslation;
		obj.verts[i][2] += (float)zTranslation;
	}

}
void RandomAttributeGenerator::changeObjectSize(Object &obj) {
	int xScale = (rand() % 5 + 1) / 10 + 1;
	int yScale = (rand() % 10 + 1) / 10 + 1;
	int zScale = (rand() % 5 + 1) / 10 + 1;
	for (int i = 0; i < obj.verts.size(); i++) {
		obj.verts[i][0] *= (float)xScale;
		obj.verts[i][1] *= (float)yScale;
		obj.verts[i][2] *= (float)zScale;
	}
}