#pragma once
#include <vector>

struct Vector {
	double x;
	double y;
	double z;

	friend Vector operator +(Vector a, Vector b);
	friend Vector operator -(Vector a, Vector b);
	friend Vector operator *(double a, Vector b);
	friend Vector operator /(Vector a, double b);
	friend Vector operator *(Vector a, Vector b);
};

