#include "Rigidbody.h"

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position,
	glm::vec2 velocity, float rotation, float mass) : PhysicsObject(shapeID)
	, m_position(position)
	, m_rotation(0)
	, m_velocity(0, 0)
	, m_mass(mass)
	, m_acceleration(0)
{
	

}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	//m_velocity += gravity * m_mass;

	//applyForce(gravity * m_mass * timeStep);
	
	m_velocity += gravity * timeStep;
	m_velocity += m_acceleration * timeStep;
	m_position += m_velocity * timeStep;

	m_acceleration = { 0,0 };
}

void Rigidbody::debug()
{
}

void Rigidbody::applyForce(glm::vec2 force)
{
	m_acceleration += force / m_mass;
}

void Rigidbody::applyForceToActor(Rigidbody * actor2, glm::vec2 force)
{
	applyForce(force);
	actor2->applyForce(force);
}
