#include "Sphere.h"

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, 
	float mass, float radius, glm::vec4 colour) : Rigidbody(SPHERE, position, velocity, 0, mass)
{
	m_radius = radius;
	m_colour = colour;
}

Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(glm::vec2(getPosition().x, getPosition().y), getRadius(), 32, m_colour);
}

bool Sphere::checkCollision(PhysicsObject * pOther)
{
	return false;
}
