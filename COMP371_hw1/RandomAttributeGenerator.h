#pragma once

#include "../glm/glm.hpp"
#include <vector>
#include <random>
#include <iostream>
#include <time.h> 
using namespace std;
using namespace glm;

typedef vector<vec3> object;
typedef vector<object> objects;
class RandomAttributeGenerator
{
private:
	void changeObjectSize(object &obj);
	void changeObjectLocation(object &obj);
	int radius;
	vec3 playerPos;
public:
	void setRadius(int rad);
	void setPlayerPos(vec3 pos);
	RandomAttributeGenerator();
	~RandomAttributeGenerator();
	void randomizeObject(object original, char type, objects &copies);
};

