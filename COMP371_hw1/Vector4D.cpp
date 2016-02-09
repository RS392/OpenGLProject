#include "stdafx.h"
#include "Vector4D.h"


Vector4D::Vector4D()
{
	Vector3D();
	w = 0;
}

Vector4D::Vector4D(double a, double b, double c, double d) {
	Vector3D(a, b, c);
	w = d;
}


Vector4D::~Vector4D()
{
}

double Vector4D::getW() {
	return w;
}

void Vector4D::setW(double a) {
	w = a;
}
