#pragma once

#include "../glm/glm.hpp"
#include <vector>
#include <random>
#include <iostream>
#include <time.h> 
#include "Object.h"
#include <Windows.h>
#include <mmsystem.h>
#include "CustomThread.h"
#include <mutex>
#include <future>
using namespace std;
using namespace glm;
#define RADIUS 5000
#define ENVIRONMENTREFRESHRATE 5
//typedef vector<vec3> object;
typedef vector<Object> objects;
class RandomAttributeGenerator
{
private:
	mutex m;
	
	void alterObj(Object &obj, objects &copies);
	unsigned int generateRandomInt(unsigned long a, unsigned long b, unsigned long c);
	void changeObjectSize(Object &obj);
	void changeObjectLocation(Object &obj);
	int radius;
	vec3 playerPos;
	vec3 oldPlayerPos;
	vec3 distanceTraveled;
	
public:
	bool generatedOnce;
	int maxDist;
	vec3 forward;
	void setOldPlayerPos(vec3 pos);
	void setRadius(int rad);
	void setPlayerPos(vec3 pos);
	RandomAttributeGenerator();
	~RandomAttributeGenerator();
	void randomizeObject(Object original, char type, objects &copies);
};

