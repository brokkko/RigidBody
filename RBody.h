#pragma once
#include <vector>
#include "Vector.h"
#include "VarState.h"

class RBody {
public:
	std::vector<Vector> localVertex;
	std::vector<Vector>::iterator it;

	double mass = 1;
	const int countVertex = 5;
	const double g = 9.81;
	Vector centerOfMass;
	VarState state;

public:
	RBody();
	void initialization(RBody* body);
	Vector getParticleVelocity(Vector partical);
	Vector localToGlobal(Vector localVerte);
	Vector getTheLowestVertex();
	std::vector<Vector> findAllContactVertices(RBody* body);
	void checkCollision(RBody* body, double h, double t);
	void collision(RBody* body);

	VarState function(VarState body, double t);
	VarState rungeKutta(RBody body, double h, double t);
	VarState oneFrame(RBody body, double h, double t);
};