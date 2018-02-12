#pragma once
#include "Rigidbody.h"

class Sphere : public Rigidbody
{
public:
	Sphere(glm::vec2 position, glm::vec2 velocity, 
			float mass, float radius, glm::vec4 colour);
	~Sphere();

	virtual void makeGizmo() override;
	virtual bool checkCollision(PhysicsObject* pOther); 

	float getRadius() { return m_radius; }
	glm::vec4 getColour() { return m_colour; }

	glm::vec2 setVelocity(glm::vec2 velocity) { m_velocity = velocity; }

protected:
	float m_radius;
	glm::vec4 m_colour;
};

