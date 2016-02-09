#include "stdafx.h"
#include "Vector3D.h"


Vector3D::Vector3D()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vector3D::Vector3D(double a, double b, double c) {

	x = a;
	y = b;
	z = c;
}


Vector3D::~Vector3D()
{
}

double Vector3D::getX() {
	return x;
}

double Vector3D::getY() {
	return y;
}

double Vector3D::getZ() {
	return z;
}

void Vector3D::setX(double a) {
	x = a;
}

void Vector3D::setY(double a) {
	y = a;
}

void Vector3D::setZ(double a) {
	z = a;
}