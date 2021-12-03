#include "Vector.h"

Vector operator+(Vector a, Vector b)
{
	Vector c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}

Vector operator-(Vector a, Vector b)
{
	Vector c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return c;
}

Vector operator*(double a, Vector b)
{
	Vector c;
	c.x = a * b.x;
	c.y = a * b.y;
	c.z = a * b.z;
	return c;
}

Vector operator/(Vector a, double b)
{
	Vector c;
	c.x = a.x / b;
	c.y = a.y / b;
	c.z = a.z / b;
	return c;
}

Vector operator*(Vector a, Vector b)
{
	Vector c;
	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	return c;
}


