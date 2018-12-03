#pragma once
#include <vector>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <list>
#include "PhysicsObject.h"

class PhysicsScene
{
public:
	struct CollisionData
	{
		bool		wasCollision = false;
		glm::vec2	normal = { 0, 0 };
		float		overlap = 0.0f;
	};

public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	void RemoveActor(PhysicsObject* actor);
	void update(float dt);
	void updateGizmos();

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	void handleCollision(PhysicsObject * object1, PhysicsObject* object2, const CollisionData& collision);

	void seperatCollisionObjects(class Rigidbody * rb1, class Rigidbody * rb2, const PhysicsScene::CollisionData & collision);

	void debugScene();

	void setupContinuousDemo(glm::vec2 startPos, float inclination,
		float speed, float gravity);

	void checkForCollisions();

	static CollisionData Plane2Sphere(const class PhysicsObject* object1,
		const class PhysicsObject* object2);

	static CollisionData Plane2Box(const class PhysicsObject* object1,
		const class PhysicsObject* object2);

	static CollisionData Sphere2Plane(const class PhysicsObject* object1,
		const class PhysicsObject* object2);

	static CollisionData Sphere2Sphere(const class PhysicsObject* object1,
		const class PhysicsObject* object2);
	
	static CollisionData Sphere2Box(const class PhysicsObject* object1,
		const class PhysicsObject* object2);

	static CollisionData Box2Plane(const class PhysicsObject* object1,
		const class PhysicsObject* object2);

	static CollisionData Box2Sphere(const class PhysicsObject* object1,
		const class PhysicsObject* object2);

	static CollisionData Box2Box(const class PhysicsObject* object1,
		const class PhysicsObject* object2);
protected:
		glm::vec2 m_gravity;
		float m_timeStep;
		std::vector<PhysicsObject*> m_actors;
};

