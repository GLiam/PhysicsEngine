#pragma once
#include <vector>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <list>





class PhysicsObject
{
public:
	enum ShapeType {
		PLANE = 0,
		SPHERE,
		BOX
	};

	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}
	
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};
	
	
	ShapeType getShapeID() { return m_shapeID; }

protected:
	ShapeType m_shapeID;
};

class PhysicsScene
{
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

	void debugScene();

	void setupContinuousDemo(glm::vec2 startPos, float inclination,
		float speed, float gravity);

	void checkForCollisions();

	static bool Plane2Sphere(const class PhysicsObject* object1, 
		const class PhysicsObject* object2);

	static bool Sphere2Plane(const class PhysicsObject* object1,
		const class PhysicsObject* object2);

	static bool Sphere2Sphere(class PhysicsObject* object1,
		class PhysicsObject* object2);

protected:
		glm::vec2 m_gravity;
		float m_timeStep;
		std::vector<PhysicsObject*> m_actors;
};

