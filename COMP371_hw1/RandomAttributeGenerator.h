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
public:
	RandomAttributeGenerator();
	~RandomAttributeGenerator();
	object generateObjectAtDiffLocations(object original, char type);
};

