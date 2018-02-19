#pragma once
#include "Rigidbody.h"
class Box : public Rigidbody
{
public:
	Box();
	Box(const glm::vec2 position, const glm::vec2 velocity, const float mass,
		glm::vec2 Extense, const glm::vec4 colour);

	virtual void makeGizmo() override;
	virtual bool checkCollision(PhysicsObject* pOther);

	void setExtense(const glm::vec2 extense) { m_Extense = extense; }
	void setColour(const glm::vec4 colour) { m_colour = colour; }

	const float getExtenseX() const { return m_Extense.x; }
	const float getExtenseY() const { return m_Extense.y; }
	const glm::vec2 getExtense() const {return m_Extense; }
	glm::vec4 getColour() const { return m_colour; }


private:
	glm::vec2 m_Extense = { 1, 1 };
	glm::vec4 m_colour;
};

