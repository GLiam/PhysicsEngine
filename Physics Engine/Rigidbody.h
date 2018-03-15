#pragma once
#include "PhysicsScene.h"

class Rigidbody : public PhysicsObject {
public:
	Rigidbody(ShapeType shapeID, glm::vec2 position,
				glm::vec2 velocity, float rotation, float mass);
	~Rigidbody();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) override;
	virtual void debug() override;
	void applyForce(glm::vec2 force /*, glm::vec2 pos*/);
	void applyForceToActor(Rigidbody* actor2, glm::vec2 force);
	void resolveCollision(Rigidbody* actor2, glm::vec2 contact,
		glm::vec2* collisionNormal = nullptr);

	virtual bool checkCollision(PhysicsObject* pOther) = 0;

	glm::vec2 getPosition() const { return m_position; }
	float getRotation() const { return m_rotation; }
	glm::vec2 getVelocity() const { return m_velocity; }
	float getMass() const { return m_mass; }
	float getElacticity() const { return m_elacticity; }

	void setVelocity(glm::vec2 velocity) { m_velocity = velocity; }
	void setPosition(glm::vec2 position) { m_position = position; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;
	float m_mass;
	float m_rotation;
	float m_angularVelocity;
	float m_angularDrag;
	float m_moment;
	float m_elacticity;
};

