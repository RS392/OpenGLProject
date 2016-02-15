// For coordinates that are in 4 dimension (like red green blue alpha)

#pragma once
#include "Vector3D.h"

class Vector4D : public Vector3D
{

private:
	double w;
public:
	Vector4D();
	Vector4D(double a, double b, double c, double d);
	~Vector4D();
	double getW();
	void setW(double a);
};

