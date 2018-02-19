#include "Box.h"
#include <glm/glm.hpp>
#include <Gizmos.h>

Box::Box(const glm::vec2 position, const glm::vec2 velocity, const float mass, 
		glm::vec2 Extense, const glm::vec4 colour) 
											: Rigidbody(BOX, position, velocity, 0, mass)
{
	m_colour = colour;
	m_Extense = Extense;
}

void Box::makeGizmo()
{
	aie::Gizmos::add2DAABB(glm::vec2(m_position.x, m_position.y), m_Extense, m_colour);
}

bool Box::checkCollision(PhysicsObject * pOther)
{
	return false;
}