#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Sphere.h"
#include "Plane.h"
#include "AABB.h"

class Physics_EngineApp : public aie::Application {
public:

	Physics_EngineApp();
	virtual ~Physics_EngineApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	PhysicsScene*		m_PhysicsScene;
	//Rigidbody*			m_Rigibody;
	Sphere*				m_pShere;

private:
	PhysicsObject * m_pObject;

};