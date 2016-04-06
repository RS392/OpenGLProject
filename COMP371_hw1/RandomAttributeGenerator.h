#pragma once

#include "../glm/glm.hpp"
#include <vector>
#include <random>
#include <iostream>
#include <time.h> 
#include "Object.h"
#include <Windows.h>
#include <mmsystem.h>
#include "UserInput.h"
#include <mutex>
#include <future>
using namespace std;
using namespace glm;

// the forest is actually a square of length 5000 in each direction
#define RADIUS 5000
typedef vector<Object*> objects;
class RandomAttributeGenerator
{
private:


	mutex m;
	UserInput* title;
	// this method just calls 3 other methods, namely change size, location and attributes
	void alterObj(Object &obj, objects &copies);
	unsigned int generateRandomInt(unsigned long a, unsigned long b, unsigned long c); // not used anymore
	void changeObjectSize(Object &obj);
	void changeObjectLocation(Object &obj);
	int radius;
	vec3 playerPos;
	vec3 oldPlayerPos;
	vec3 distanceTraveled;
	// changes the bounding box mainly
	void changeObjectAttributes(Object& obj);
public:
	bool generatedOnce;
	int maxDist;
	vec3 forward;
	void setOldPlayerPos(vec3 pos);
	void setRadius(int rad);
	void setPlayerPos(vec3 pos);
	RandomAttributeGenerator();
	~RandomAttributeGenerator();

	// makes multiple(random) copies of an original object to store it into copies. This method also calls almost every other
	// private method in this class to modify the object, mostly in a random way
	void randomizeObject(Object original, objects &copies);
	void setTitle(UserInput* t);
};

