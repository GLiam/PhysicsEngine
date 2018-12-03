#pragma once
#include <glm/glm.hpp>
#include <Gizmos.h>
#include "PhysicsObject.h"


class Plane : public PhysicsObject
{
public:
	Plane();
	Plane(glm::vec2 normal, float distance);
	~Plane();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug();
	virtual void makeGizmo() override;
	virtual void resetPosition();

	glm::vec2 getNormal() const { return m_normal; }
	float getDistance() const { return m_distanceToOrigan; }

protected:
	glm::vec2 m_normal;
	float m_distanceToOrigan;
};

