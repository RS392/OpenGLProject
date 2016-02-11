/*
Every feature( like a tree or a rock), will be an object therefore will have to inherit from this class.


*/

#pragma once
#include <vector>
#include "Vector3D.h"
using namespace std;

class Object
{

private:
	vector<Vector3D> position;
	

public:
	Object();
	~Object();
};

