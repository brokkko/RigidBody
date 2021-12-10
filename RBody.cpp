#include "RBody.h"

RBody::RBody()
{
	centerOfMass = { 0 };
	mass = 1;
}

void RBody::initialization(RBody* body)
{
	body->localVertex.push_back({ 0 + body->state.a / 2, 0, 0 + body->state.b / 2 });
	body->localVertex.push_back({ 0 - body->state.a / 2, 0, 0 + body->state.b / 2 });
	body->localVertex.push_back({ 0 - body->state.a / 2, 0, 0 - body->state.b / 2 });
	body->localVertex.push_back({ 0 + body->state.a / 2, 0, 0 - body->state.b / 2 });
	body->localVertex.push_back({ 0, body->state.h, 0 });

	for (int i = 0; i < body->localVertex.size(); i++) {
		body->centerOfMass = body->centerOfMass + body->localVertex[i];
	}
	body->centerOfMass.x = body->centerOfMass.x / 4;
	body->centerOfMass.y = body->centerOfMass.y / 4;
	body->centerOfMass.z = body->centerOfMass.z / 4 + 1 / 4 * body->state.h;
	body->state.initialisation();
	body->state.particlePos = body->centerOfMass;
}

Vector RBody::getParticleVelocity(Vector partical)
{
	Vector omega = state.tensorInertia * state.angularMomentum;
	Vector r = partical - centerOfMass;
	return state.R * state.E.vectorProduct(omega, r) + state.particleImpulse / mass;
}

Vector RBody::localToGlobal(Vector localVertex)
{
	return state.particlePos + (state.R * (localVertex - centerOfMass));
}

Vector RBody::getTheLowestVertex()
{
	Vector lowestVertex = this->centerOfMass;
	for (auto i : this->localVertex) {
		if (this->localToGlobal(i).y < this->localToGlobal(lowestVertex).y) {
			lowestVertex = i;
		}
	}
	return lowestVertex;
}

std::vector<Vector> RBody::findAllContactVertices(RBody* body) {
	std::vector<Vector> vertices;
	Vector vec = { 0, 1, 0 };
	for (int i = 0; i < body->localVertex.size(); i++) {
		double currentGlobalPos = body->localToGlobal(body->localVertex[i]).y;
		double relativeVel = state.E.scalarProduct(vec, body->getParticleVelocity(body->localVertex[i]));
		if (relativeVel < 0 && currentGlobalPos < 0.01) {
			vertices.push_back(body->localVertex[i]);
		}
	}
	return vertices;
}

void RBody::checkCollision(RBody* body, double h, double t)
{
	collision(body);
}

void RBody::collision(RBody* body)
{
	std::vector<Vector> touchVertex = body->findAllContactVertices(body);
	if (touchVertex.size()) {
		Vector middle = { 0, 0, 0 };
		for (int i = 0; i < touchVertex.size(); i++) {
			middle = middle + touchVertex[i];
		}
		middle = middle / touchVertex.size();
		Vector normal = { 0, 1, 0 };
		Vector r = body->localToGlobal(middle) - body->localToGlobal(centerOfMass);
		double relativeVel = body->getParticleVelocity(middle).y;

		Vector omega = state.R * state.tensorInertia * state.R.TransponateMatrix(state.R) * state.angularMomentum;
		double numerator = -(1 + 1) * relativeVel;
		double term1 = 1 / mass;
		Matrix Iinv = body->state.R * body->state.tensorInertia * body->state.R.TransponateMatrix(body->state.R);
		double term2 = state.E.scalarProduct(normal, state.E.vectorProduct((Iinv * state.E.vectorProduct(r, normal)), r));
		double j = numerator / (term1 + term2);
		Vector force = j * normal;
		body->state.particleImpulse = body->state.particleImpulse + force;
		body->state.angularMomentum = body->state.angularMomentum + state.R.TransponateMatrix(body->state.R) * body->state.E.vectorProduct(r, force);
	}
}

VarState RBody::function(VarState body, double t)
{
	VarState dbody;
	dbody.particlePos = body.particleImpulse / mass;
	dbody.particleImpulse.x = 0;
	dbody.particleImpulse.y = -g * mass;
	dbody.particleImpulse.z = 0;

	Vector omega = body.tensorInertia * body.angularMomentum;
	dbody.R = dbody.R.skewMatrix(omega);

	return dbody;
}

VarState RBody::rungeKutta(RBody body, double h, double t)
{
	VarState k1, k2, k3, k4;
	k1 = function(body.state, t);
	k2 = function(body.state + 0.5 * h * k1, t + 0.5 * h);
	k3 = function(body.state + 0.5 * h * k2, t + 0.5 * h);
	k4 = function(body.state + h * k3, t + h);
	body.state = body.state + (h / 6) * k1;
	body.state = body.state + (h / 3) * k2;
	body.state = body.state + (h / 3) * k3;
	body.state = body.state + (h / 6) * k4;

	body.state.R = body.state.R.ortGramSchmidt(body.state.R);

	return body.state;
}

VarState RBody::oneFrame(RBody body, double h, double t)
{
	double saved_h = h;
	RBody current = body;
	current.state = current.rungeKutta(current, h, t);
	Vector lowest = current.localToGlobal(current.getTheLowestVertex());
	// 1
	if (lowest.y > 0.01) {
		body.state = current.state;
		return body.state;
	}
	// 2
	else if (lowest.y <= 0.01) {
		while (std::abs(lowest.y) > 0.01)
		{
			h = h / 2;
			current.state = body.state;
			lowest = current.localToGlobal(current.getTheLowestVertex());
			current.state = current.rungeKutta(current, h, t);
			lowest = current.localToGlobal(current.getTheLowestVertex());
			if (lowest.y > 0) {
				body.state = current.state;
				h = saved_h;
			}
		}
 		lowest = current.localToGlobal(current.getTheLowestVertex());
		if (lowest.y > 0.01) {
			body.state = current.state;
			return body.state;
		}
		else if (lowest.y < 0.01 && lowest.y >= -0.01) {
			current.checkCollision(&current, h, t);
			lowest = current.localToGlobal(current.getTheLowestVertex());
			body.state = current.state;
			return body.state;
		}
	}

	return body.state;
}