#include "PhysicsScene.h"
#include <iostream>
#include "Rigidbody.h"
#include "Sphere.h"
#include "Plane.h"
#include "AABB.h"

typedef PhysicsScene::CollisionData(*collisionFnc)(const PhysicsObject*, const PhysicsObject*);

static collisionFnc collisionFunctionArray[] =
{
	nullptr,					PhysicsScene::Plane2Sphere,		PhysicsScene::Plane2Box,
	PhysicsScene::Sphere2Plane,	PhysicsScene::Sphere2Sphere,	PhysicsScene::Sphere2Box,
	PhysicsScene::Box2Plane,	PhysicsScene::Box2Sphere,		PhysicsScene::Box2Box,
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

				//Rigidbody* pRigid = dynamic_cast<Rigidbody*>(pActor);
				//if (pRigid->checkCollision(pOther) == true) 
				//{
				//	pRigid->applyForceToActor(
				//		dynamic_cast<Rigidbody*>(pOther),
				//		pRigid->getVelocity() * pRigid->getMass());
				//		dirty.push_back(pRigid);
				//		dirty.push_back(pOther);
				//}

				checkForCollisions();
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

void PhysicsScene::handleCollision(PhysicsObject * object1,
	PhysicsObject * object2, const CollisionData & collision)
{
	auto rb1 = dynamic_cast<Rigidbody*>(object1);
	auto rb2 = dynamic_cast<Rigidbody*>(object2);

	seperatCollisionObjects(rb1, rb2, collision);

	glm::vec2 relativeVelocity = { 0, 0 };
	if (rb1) relativeVelocity = rb1->getVelocity();
	if (rb2) relativeVelocity -= rb2->getVelocity();

	float elasticaty = 1;
	float invMass1 = (rb1) ? 1.0f / rb1->getMass() : 0.0f;
	float invMass2 = (rb2) ? 1.0f / rb2->getMass() : 0.0f;

	float jTop = -(1 + elasticaty) * glm::dot(relativeVelocity, collision.normal);
	float jBottom = glm::dot(collision.normal, collision.normal) * (invMass1 + invMass2);

	float j = jTop / jBottom;

	if (rb1)
	{
		glm::vec2 newVelocity = rb1->getVelocity() + (j / rb1->getMass()) * collision.normal;

		rb1->setVelocity(newVelocity);
	}

	if (rb2)
	{
		glm::vec2 newVelocity = rb2->getVelocity() - (j / rb2->getMass()) * collision.normal;

		rb2->setVelocity(newVelocity);
	}
}

void PhysicsScene::seperatCollisionObjects(Rigidbody * rb1, 
					Rigidbody * rb2, const PhysicsScene::CollisionData & collision)
{

	if (rb1 == nullptr && rb2 == nullptr)
	{
		return;
	}

	float object1MoveRatio = 0;
	float object2MoveRatio = 0;

	if (rb1 && rb2)
	{
		float totalMass = rb1->getMass() + rb2->getMass();
		object1MoveRatio = 1 - (rb1->getMass() / totalMass);
		object2MoveRatio = 1 - (rb2->getMass() / totalMass);
	}
	else if (rb1)
	{
		object1MoveRatio = 1.0f;
	}
	else if (rb2)
	{
		object2MoveRatio = 1.0f;
	}

	if (rb1)
	{
		rb1->setPosition(rb1->getPosition() + (object1MoveRatio * collision.overlap * collision.normal));
	}
	if (rb2)
	{
		rb2->setPosition(rb2->getPosition() - (object2MoveRatio * collision.overlap * collision.normal));
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

	CollisionData collisionData;
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];

			int ShapeID1 = object1->getShapeID();
			int ShapeID2 = object2->getShapeID();
			int Index = (ShapeID1 * PhysicsObject::SHAPECOUNT) + ShapeID2;

			collisionFnc fnc = collisionFunctionArray[Index];
			if (fnc != nullptr)
			{
				CollisionData collisionData = fnc(object1, object2);
				if (collisionData.wasCollision == true)
				{
					handleCollision(object1, object2, collisionData);
				}
			}
 		}
	}
}

PhysicsScene::CollisionData PhysicsScene::Plane2Sphere(const PhysicsObject * object1, 
									const PhysicsObject * object2)
{
	const Plane* plane = dynamic_cast<const Plane*>(object1);
	const Sphere* sphere = dynamic_cast<const Sphere*>(object2);

	CollisionData collData;
	collData.wasCollision = false;

	//glm::vec2 contact = sphere->getPosition() + (collData.normal * -sphere->getRadius());
	
	if (sphere != nullptr && plane != nullptr)
	{
		float distanceBetween = glm::dot(sphere->getPosition(), 
				plane->getNormal()) + plane->getDistance() - sphere->getRadius();

		if (distanceBetween < 0)
		{
			collData.wasCollision = true;
			collData.normal = plane->getNormal();
			collData.overlap = distanceBetween * -1;
		}
	}
	return collData;
}

PhysicsScene::CollisionData PhysicsScene::Plane2Box(const PhysicsObject * object1,
									const PhysicsObject * object2)
{
	const Plane* plane = dynamic_cast<const Plane*>(object1);
	const AABB* box = dynamic_cast <const AABB*>(object2);
	CollisionData collData;
	collData.wasCollision = false;

	if (box != nullptr && plane != nullptr)
	{
		//glm::vec2 tL = glm::vec2(box->getPosition().x - box->getExtenseX(), 
		//									box->getPosition().y + box->getExtenseY());
		//glm::vec2 tR = glm::vec2(box->getPosition().x + box->getExtenseX(), 
		//									box->getPosition().y + box->getExtenseY());
		//glm::vec2 bL = glm::vec2(box->getPosition().x - box->getExtenseX(), 
		//									box->getPosition().y - box->getExtenseY());
		//glm::vec2 bR = glm::vec2(box->getPosition().x + box->getExtenseX(), 
		//									box->getPosition().y - box->getExtenseY());

		//auto OffSetTL = glm::dot(tL, plane->getNormal()) + plane->getDistance();
		//auto OffSetTR = glm::dot(tR, plane->getNormal()) + plane->getDistance();
		//auto OffSetBL = glm::dot(bL, plane->getNormal()) + plane->getDistance();
		//auto OffSetBR = glm::dot(bR, plane->getNormal()) + plane->getDistance();

		//float Smallest = OffSetTL;
		//if(Smallest < OffSetTR)
		//	Smallest = OffSetTR;
		//if(Smallest < OffSetBL)
		//	Smallest = OffSetBL;
		//if(Smallest < OffSetBR)
		//	Smallest = OffSetBR;

		float distanceBetween = glm::dot(box->getPosition(), plane->getNormal()) + plane->getDistance();

		float d = distanceBetween - glm::length(box->getExtense() * plane->getNormal());

		if(d < 0)
		{
			collData.wasCollision = true;
			collData.normal = plane->getNormal();
			collData.overlap = -d;
		}
	}
	return collData;
}

PhysicsScene::CollisionData PhysicsScene::Sphere2Plane(const PhysicsObject * object1, 
									const PhysicsObject * object2)
{

	//const Sphere* sphere = dynamic_cast<const Sphere*>(object1);
	//const Plane* plane = dynamic_cast<const Plane*>(object2);

	return Plane2Sphere(object2, object1);
}

PhysicsScene::CollisionData PhysicsScene::Sphere2Sphere(const PhysicsObject * object1,
									const PhysicsObject * object2)
{
	const Sphere* sphere1 = dynamic_cast<const Sphere*>(object1);
	const Sphere* sphere2 = dynamic_cast<const Sphere*>(object2);

	CollisionData CollData;

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
//		float distanceBetween = glm::length(sphere2->getPosition() - sphere1->getPosition());

//		float minDistanceBetween = sphere1->getRadius() + sphere2->getRadius();

		glm::vec2 offset = sphere2->getPosition() - sphere1->getPosition();
		float distanceBetween = glm::length(offset);

		float minDistanceBetween = (sphere1->getRadius() + sphere2->getRadius());
		//minDistanceBetween *= minDistanceBetween;

		if (distanceBetween < minDistanceBetween)
		{
			CollData.wasCollision = true;
			CollData.normal = glm::normalize(sphere1->getPosition() - sphere2->getPosition());
			CollData.overlap = minDistanceBetween - distanceBetween;
			return CollData;
		}
	}
	return CollData;
}

PhysicsScene::CollisionData PhysicsScene::Sphere2Box(const PhysicsObject * object1, 
									const PhysicsObject * object2)
{
	return Box2Sphere(object2, object1);
}

PhysicsScene::CollisionData PhysicsScene::Box2Plane(const PhysicsObject * object1,
									const PhysicsObject * object2)
{
	return Plane2Box(object2, object1);
}

PhysicsScene::CollisionData PhysicsScene::Box2Sphere(const PhysicsObject * object1,
									const PhysicsObject * object2)
{
	const AABB* box = dynamic_cast<const AABB*>(object1);
	const Sphere* sphere = dynamic_cast<const Sphere*>(object2);

	CollisionData collData;

	if (box != nullptr && sphere != nullptr)
	{
		glm::vec2 offset = sphere->getPosition() - box->getPosition();

		if(std::abs(offset.x) > box->getExtenseX())
		{
			offset.x = offset.x < 0 ? -box->getExtenseX() : box->getExtenseX();
		}
		if (std::abs(offset.y) > box->getExtenseY())
		{
			offset.y = offset.y < 0 ? -box->getExtenseY() : box->getExtenseY();
		}

		glm::vec2 closestPoint = box->getPosition() + offset;

		glm::vec2 distBetween = sphere->getPosition() - closestPoint;

		if (glm::length(distBetween) < sphere->getRadius())
		{
			collData.wasCollision = true;
			collData.normal = glm::normalize(distBetween);
			collData.overlap = sphere->getRadius() - glm::length(distBetween);
		}
	}
	return collData;
}

PhysicsScene::CollisionData PhysicsScene::Box2Box(const PhysicsObject * object1,
									const PhysicsObject * object2)
{
	const AABB* box1 = dynamic_cast<const AABB*>(object1);
	const AABB* box2 = dynamic_cast<const AABB*>(object2);

	CollisionData colldata;

	if (box1 != nullptr && box2 != nullptr)
	{
		glm::vec2 box1TR = glm::vec2(box1->getPosition().x + box1->getExtenseX(), 
											box1->getPosition().y + box1->getExtenseY());
		glm::vec2 box1BL = glm::vec2(box1->getPosition().x - box1->getExtenseX(), 
											box1->getPosition().y - box1->getExtenseY());

		glm::vec2 box2TR = glm::vec2(box2->getPosition().x + box2->getExtenseX(), 
											box2->getPosition().y + box2->getExtenseY());
		glm::vec2 box2BL = glm::vec2(box2->getPosition().x - box2->getExtenseX(), 
											box2->getPosition().y - box2->getExtenseY());

		if (box2BL.x < box1TR.x && box2BL.y < box1TR.y &&
			box1BL.x < box2TR.x && box1BL.y < box2TR.y)
		{
			float XDistBetweenBox1Box2 = box1BL.x - box2TR.x;
			float XDistBetweenBox2Box1 = box1TR.x - box2BL.x;
			float YDistBetweenBox1Box2 = box1BL.y - box2TR.y;
			float YDistBetweenBox2Box1 = box1TR.y - box2BL.y;
			float overlapX = std::fabsf(XDistBetweenBox1Box2) < std::fabsf(XDistBetweenBox2Box1) ? XDistBetweenBox1Box2 : XDistBetweenBox2Box1;
			float overlapY = std::fabsf(YDistBetweenBox1Box2) < std::fabsf(YDistBetweenBox2Box1) ? YDistBetweenBox1Box2 : YDistBetweenBox2Box1;

			glm::vec2 overlap = std::fabsf(overlapX) < std::fabsf(overlapY) ? glm::vec2(overlapX, 0) : glm::vec2(0, overlapY);
			colldata.wasCollision = true;
			colldata.normal = -glm::normalize(overlap);
			colldata.overlap = glm::length(overlap);
		}
	}
	return colldata;
}
