#include "VarState.h"

VarState operator+(VarState a, VarState b)
{
	a.particleImpulse.x += b.particleImpulse.x;
	a.particleImpulse.y += b.particleImpulse.y;
	a.particleImpulse.z += b.particleImpulse.z;

	a.particlePos.x += b.particlePos.x;
	a.particlePos.y += b.particlePos.y;
	a.particlePos.z += b.particlePos.z;

	a.R = b.R * a.R;

	return a;
}

VarState operator-(VarState a, VarState b)
{
	a.particleImpulse.x -= b.particleImpulse.x;
	a.particleImpulse.y -= b.particleImpulse.y;
	a.particleImpulse.z -= b.particleImpulse.z;

	a.particlePos.x -= b.particlePos.x;
	a.particlePos.y -= b.particlePos.y;
	a.particlePos.z -= b.particlePos.z;

	return a;
}

VarState operator*(float k, VarState b)
{
	b.particleImpulse.x = k * b.particleImpulse.x;
	b.particleImpulse.y = k * b.particleImpulse.y;
	b.particleImpulse.z = k * b.particleImpulse.z;

	b.particlePos.x = k * b.particlePos.x;
	b.particlePos.y = k * b.particlePos.y;
	b.particlePos.z = k * b.particlePos.z;

	b.R = b.R * k + b.E;      
	return b;
}

VarState::VarState()
{
	particlePos = { 0, 0, 0 };
	particleImpulse = { 0 , 0 , 0 };
	initTensorInertia();
	tensorInertia = tensorInertia.BackMatrix(tensorInertia);
	initEMatrix();
}

void VarState::initR()
{
	Rx.matrix[0][0] = 1;
	Rx.matrix[0][1] = 0;
	Rx.matrix[0][2] = 0;
	Rx.matrix[1][0] = 0;
	Rx.matrix[1][1] = cos(alpha1);
	Rx.matrix[1][2] = -sin(alpha1);
	Rx.matrix[2][0] = 0;
	Rx.matrix[2][1] = sin(alpha1);
	Rx.matrix[2][2] = cos(alpha1);

	Ry.matrix[0][0] = cos(alpha2);
	Ry.matrix[0][1] = 0;
	Ry.matrix[0][2] = sin(alpha2);
	Ry.matrix[1][0] = 0;
	Ry.matrix[1][1] = 1;
	Ry.matrix[1][2] = 0;
	Ry.matrix[2][0] = -sin(alpha2);
	Ry.matrix[2][1] = 0;
	Ry.matrix[2][2] = cos(alpha2);

	Rz.matrix[0][0] = cos(alpha3);
	Rz.matrix[0][1] = -sin(alpha3);
	Rz.matrix[0][2] = 0;
	Rz.matrix[1][0] = sin(alpha3);
	Rz.matrix[1][1] = sin(alpha3);
	Rz.matrix[1][2] = 0;
	Rz.matrix[2][0] = 0;
	Rz.matrix[2][1] = 0;
	Rz.matrix[2][2] = 1;

	R = Rx * Ry * Rz;
}

void VarState::initialisation()
{
	VarState();
	alpha1 = (2 * 3.14) / 180;
	alpha2 = (2 * 3.14) / 180;
	alpha3 = (1 * 3.14) / 180;
	initR();
	angularMomentum = { 0.1, 0.13, 0.036 };
	tensorInertia = tensorInertia;
}

void VarState::initTensorInertia()
{
	tensorInertia.matrix[0][0] = mass * (double(3.0 / 80) * h * h + (b * b) / 20);
	tensorInertia.matrix[0][1] = 0;
	tensorInertia.matrix[0][2] = 0;

	tensorInertia.matrix[1][0] = 0;
	tensorInertia.matrix[1][1] = double(mass / 20) * (a * a + b * b);
	tensorInertia.matrix[1][2] = 0;

	tensorInertia.matrix[2][0] = 0;
	tensorInertia.matrix[2][1] = 0;
	tensorInertia.matrix[2][2] = mass * (double(3.0 / 80) * h * h + (a * a) / 20);
}

void VarState::initEMatrix()
{
	E.matrix[0][0] = 1;
	E.matrix[0][1] = 0;
	E.matrix[0][2] = 0;

	E.matrix[1][0] = 0;
	E.matrix[1][1] = 1;
	E.matrix[1][2] = 0;

	E.matrix[2][0] = 0;
	E.matrix[2][1] = 0;
	E.matrix[2][2] = 1;
}

VarState& VarState::operator=(const VarState& other)
{
	this->angularMomentum = other.angularMomentum;
	this->particleImpulse = other.particleImpulse;
	this->particlePos = other.particlePos;
	this->R = other.R;
	return *this;
}
