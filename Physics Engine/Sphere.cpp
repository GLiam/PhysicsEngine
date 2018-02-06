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
	aie::Gizmos::add2DCircle(glm::vec2(getPosition().x, getPosition().y), 3.0f, 32, glm::vec4(1, 0.5f, 0, 1));
}

bool Sphere::checkCollision(PhysicsObject * pOther)
{
	return false;
}
