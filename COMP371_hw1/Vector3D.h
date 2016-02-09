// For whatever takes 3D points (like coordinates for drawing/rotation,etc)

#pragma once
class Vector3D
{

private:
	double x;
	double y;
	double z;

public:
	Vector3D();
	Vector3D(double x, double y, double z);
	double getX();
	double getY();
	double getZ();
	void setX(double a);
	void setY(double a);
	void setZ(double a);
	~Vector3D();
};

