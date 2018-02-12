#include "PhysicsScene.h"
#include <iostream>
#include "Rigidbody.h"
#include "Sphere.h"

typedef bool(*collisionFnc)(const PhysicsObject*, const PhysicsObject*);

static collisionFnc collisionFunctionArray[] =
{
	nullptr,					PhysicsScene::Plane2Sphere,
	PhysicsScene::Sphere2Plane,	PhysicsScene::Sphere2Sphere,
};

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::addActor(PhysicsObject * actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::RemoveActor(PhysicsObject * actor)
{
}

void PhysicsScene::update(float deltatime)
{
	static std::list<PhysicsObject*> dirty;

	static float accumulatedTime = 0.0f;
	accumulatedTime += deltatime;

	while (accumulatedTime >= m_timeStep)	
	{
		for (auto pActor : m_actors)	
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;

		for (auto pActor : m_actors)
		{
			for (auto pOther : m_actors)
			{
				if (pActor == pOther)
				{
					continue;
				}
				//if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
				//	std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
				//{
				//	continue;
				//}

				Rigidbody* pRigid = dynamic_cast<Rigidbody*>(pActor);
				if (pRigid->checkCollision(pOther) == true) 
				{
					pRigid->applyForceToActor(
						dynamic_cast<Rigidbody*>(pOther),
						pRigid->getVelocity() * pRigid->getMass());
						dirty.push_back(pRigid);
						dirty.push_back(pOther);
				}
			}
		}
		dirty.clear();
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors) 
{
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{
	int count = 0;
	for (auto pActor : m_actors)
	{
		std::cout << count << " : ";
		pActor->debug();
		count++;
	}
}

void PhysicsScene::setupContinuousDemo(glm::vec2 startPos, float inclination,
	float speed, float gravity)
{
	float t = 0;																	// time 
	float tStep = 0.5f;																// timer
	float radius = 1.0f;															// radius of balls
	int segments = 12;																// number of balls
	glm::vec4 colour = glm::vec4(1, 0, 0, 1);										// coulor of the balls

	float xPos;																		// current X position
	float yPos;																		// current Y position

	float degToRadians = glm::pi<float>() / 180.0f;									// converts the degrees input to radiuns
	inclination *= degToRadians;													// multiplys the inclination but the radiuns 
	glm::vec2 velocity = glm::vec2(sin(inclination), cos(inclination)) * speed;		// sin and cos the inclination and multiplys them by the speed

	while (t <= 5)
	{
		xPos = startPos.x + velocity.x * t;											// get the current X position by adding the starting X position 
																					// by the velocity and multiplying them by the time
		yPos = startPos.y + velocity.y * t + 0.5f * gravity * t * t;				// get the current Y position by adding the starting Y position by the velocity and then multiplying by time		
																					// and adding 0.5f and again multiplying the by gravity and time sqaured   
		aie::Gizmos::add2DCircle(glm::vec2(xPos, yPos), radius, segments, colour);	// draws the circle at the current X position and current Y position
		t += tStep;																	// and using the preset Radius, segments and color
	}
}

void PhysicsScene::checkForCollisions()
{
	int actorCount = m_actors.size();

	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			auto object1 = m_actors[outer];
			auto object2 = m_actors[inner];

			int ShapeID1 = object1->getShapeID();
			int ShapeID2 = object2->getShapeID();

			int Index = (ShapeID1 * PhysicsObject::PLANE) + ShapeID2;

			collisionFnc fnc = collisionFunctionArray[inner];
			if (fnc != nullptr)
			{
				bool wasCollision = fnc(object1, object2);
			}
 		}
	}
}

bool PhysicsScene::Plane2Sphere(const PhysicsObject * object1, const PhysicsObject * object2)
{
	return false;
}

bool PhysicsScene::Sphere2Plane(const PhysicsObject * object1, const PhysicsObject * object2)
{
	return false;
}

bool PhysicsScene::Sphere2Sphere(PhysicsObject * object1, PhysicsObject * object2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(object1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(object2);

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		float distanceBtween = glm::length(sphere2->getPosition() - sphere1->getPosition());

		float minDistanceBetween = sphere1->getRadius() + sphere2->getRadius();

		if (distanceBtween < minDistanceBetween)
		{
			sphere1->setVelocity(glm::normalize(sphere1->getPosition() - sphere2->getPosition()) * glm::length(sphere1->getVelocity()) * 0.5f);
			sphere2->setVelocity(glm::normalize(sphere2->getPosition() - sphere1->getPosition()) * glm::length(sphere2->getVelocity()) * 0.5f);
			return true;
		}
	}
}

