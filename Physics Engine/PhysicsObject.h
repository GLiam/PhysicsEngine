#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class PhysicsObject
{
public:
	enum ShapeType {
		PLANE = 0,
		SPHERE,
		SHAPECOUNT
//		BOX
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