#pragma once
#include <vector>
#include "Vector.h"
#include "VarState.h"

class RBody {
public:
	std::vector<Vector> localVertex;
	std::vector<Vector>::iterator it;

	float mass = 1;
	const int countVertex = 5;
	const float g = 9.81;
	Vector centerOfMass;
	VarState state;
	Vector lastLowest;

public:
	RBody();
	void initialization(RBody* body);
	Vector getParticleVelocity(Vector partical);
	Vector localToGlobal(Vector localVerte);
	Vector getTheLowestVertex();
	std::vector<Vector> findAllContactVertices(RBody* body);
	void checkCollision(RBody* body, Vector lastLowesr, float h, float t);
	void collision(RBody* body);

	VarState function(VarState body, float t);
	VarState rungeKutta(RBody body, float h, float t);
	VarState oneFrame(RBody body, float h, float t);
};