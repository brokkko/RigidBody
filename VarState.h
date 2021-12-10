#pragma once
#include "Vector.h"
#include "Matrix.h"
#include <iostream>

struct VarState {
	Vector particlePos;
	Vector particleImpulse;
	Matrix Rx, Ry, Rz;
	Matrix R;
	Matrix tensorInertia;
	Vector angularMomentum;
	double alpha1, alpha2, alpha3;
	Matrix E;
	double mass = 1;
	double a = 1.0, b = 1.0, h = 2.0;

	VarState();
	void initR();
	void initialisation();
	void initTensorInertia();
	void initEMatrix();
	friend VarState operator +(VarState a, VarState b);
	friend VarState operator -(VarState a, VarState b);
	friend VarState operator *(double a, VarState b);
	VarState& operator=(const VarState& other);
};