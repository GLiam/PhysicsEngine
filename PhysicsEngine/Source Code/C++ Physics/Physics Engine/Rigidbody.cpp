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
	m_position += m_velocity * timeStep;
	m_velocity += m_acceleration * timeStep;

	m_rotation += m_angularVelocity * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;

	if (glm::abs(m_angularVelocity) < m_rotation)
	{
		m_angularVelocity = 0;
	}

	m_acceleration = { 0,0 };
}

void Rigidbody::debug()
{
}

void Rigidbody::applyForce(glm::vec2 force/*, glm::vec2 pos*/)
{
	m_acceleration += force / m_mass;
	//m_angularVelocity += (force /*.y * pos.x - force.x * pos.y) / (m_moment)*/;
}

void Rigidbody::resolveCollision(Rigidbody * actor2, glm::vec2 contact, 
								glm::vec2 * collisionNormal)
{
	glm::vec2 normal = collisionNormal ? *collisionNormal : glm::normalize(
		actor2->m_position - m_position);

	glm::vec2 perp(normal.y, -normal.x);

	float r1 = glm::dot(contact - m_position, -perp);
	float r2 = glm::dot(contact - actor2->m_position, perp);

	float v1 = glm::dot(m_velocity, normal) - r1 * m_rotation;
	float v2 = glm::dot(actor2->m_velocity, normal) + r2 * actor2->m_rotation;

	if (v1 > v2)
	{
		float mass1 = 1.0f / (1.0f / m_mass + (r1*r1) / actor2->m_moment);
		float mass2 = 1.0f / (1.0f / actor2->m_mass + (r2*r2) / actor2->m_moment);

		float elasticity = (m_elacticity + actor2->getElacticity()) / 2.0f;

		glm::vec2 force = (1.0f + elasticity)*mass1*mass2 /
			(mass1 + mass2)*(v1 - v2)*normal;

		applyForce(-force) /*, contact - m_position)*/;
		actor2->applyForce(force) /*,contact - actor2->m_position)*/;
	}
}

void Rigidbody::applyForceToActor(Rigidbody * actor2, glm::vec2 force)
{
	applyForce(force);
	actor2->applyForce(force);
}

