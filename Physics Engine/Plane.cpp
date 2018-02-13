#include "Plane.h"



Plane::Plane() : PhysicsObject(PhysicsObject::ShapeType::PLANE)
{
	m_distanceToOrigan = 0;
	m_normal = glm::vec2(0, 1);
}

Plane::Plane(glm::vec2 normal, float distance) : PhysicsObject(PhysicsObject::ShapeType::PLANE)
{
	m_normal = normal;
	m_distanceToOrigan = distance;
}


Plane::~Plane()
{
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{
}

void Plane::debug()
{
}

void Plane::makeGizmo()
{
	const float lineSegmentLength = 300;
	glm::vec2 center = m_normal * -m_distanceToOrigan;

	glm::vec2 Parallel(m_normal.y, -m_normal.x);
	glm::vec4 colour(1, 1, 1, 1);
	glm::vec2 start = center + (Parallel * lineSegmentLength);
	glm::vec2 end = center - (Parallel * lineSegmentLength);
	aie::Gizmos::add2DLine(start, end, colour);
}

void Plane::resetPosition()
{
}
