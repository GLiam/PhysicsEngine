#define _USE_MATH_DEFINES

#include "Physics_EngineApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <math.h>


Physics_EngineApp::Physics_EngineApp() {

}

Physics_EngineApp::~Physics_EngineApp() {

}

bool Physics_EngineApp::startup() {

	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_PhysicsScene = new PhysicsScene();
	m_PhysicsScene->setGravity(glm::vec2(0, -98.07f));
	m_PhysicsScene->setTimeStep(0.01f);

	//float radius = 1.0f;
	//float speed = 30;
	//glm::vec2 starpos(-40, 0);
	//float inclination = (float)M_PI / 4.0f;
	//m_PhysicsScene->addActor(new Sphere(starpos, inclination, speed, 1, radius, glm::vec4(1, 0, 0, 1)));

	//Sphere* ball = new Sphere(glm::vec2(40, 0), 
	//	glm::vec2(0, 0), 3.0f, 1, glm::vec4(1, 0, 0, 1));
	//Sphere* ball2 = new Sphere(glm::vec2(-40, 0),
	//	glm::vec2(0, 0), 3.0f, 1, glm::vec4(1, 0, 1, 1));
	//m_PhysicsScene->addActor(ball);
	//m_PhysicsScene->addActor(ball2);
	//ball->applyForceToActor(ball, glm::vec2(-2000, 0));
	//ball2->applyForceToActor(ball2, glm::vec2(2000, 0));

	Sphere* ball1 = new Sphere({ 0.0f, 20.0f }, { 0.0f, 0.0f }, 3, 4.0f, { 0.5f, 1, 0, 1 });
	Sphere* ball2 = new Sphere({ 0.0f, 0.0f }, { 0.0f, 0.0f }, 3, 4.0f, { 1.0f, 0.5f, 0, 1 });
	Sphere* ball3 = new Sphere({ -40.0f, 0.0f }, { 0.0f, 0.0f }, 3, 4.0f, { 1.0f, 1, 0, 1 });

	AABB* aabb1 = new AABB({ 0.0f, 10.0f }, { 0.0f, 0.0f }, 3, { 4.0f, 3.0f }, { 1, 1, 0, 1 });
	AABB* aabb2 = new AABB({ 0.0f, 30.0f }, { 0.0f, 0.0f }, 3, { 4.0f, 3.0f }, { 1, 0, 0, 1 });
	AABB* aabb3 = new AABB({ 40.0f, 0.0f }, { 0.0f, 0.0f }, 3, { 4.0f, 3.0f }, { 1, 1, 1, 1 });

	Plane* line = new Plane({ 0, 1 }, 40);
	Plane* line1 = new Plane({ 1, 0 }, 60);
	//Plane* line2 = new Plane({ 0, -1 }, 40);
	Plane* line3 = new Plane({ -1, 0 }, 60);

	m_PhysicsScene->addActor(ball1);
	m_PhysicsScene->addActor(ball2);
	m_PhysicsScene->addActor(ball3);
	ball3->setVelocity({ -30.0f, 100.0f });

	m_PhysicsScene->addActor(aabb1);
	m_PhysicsScene->addActor(aabb2);
	m_PhysicsScene->addActor(aabb3);

	m_PhysicsScene->addActor(line);
	m_PhysicsScene->addActor(line1);
	//m_PhysicsScene->addActor(line2);
	m_PhysicsScene->addActor(line3);




	return true;
}

void Physics_EngineApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void Physics_EngineApp::update(float deltaTime) {
	
	aie::Gizmos::clear();

	// input example
	aie::Input* input = aie::Input::getInstance();

	m_PhysicsScene->update(deltaTime);
	m_PhysicsScene->updateGizmos();

	//static float xPos = 0;
	//xPos += 1.0 * deltaTime;

	static const glm::vec4 colours[] = {
		glm::vec4(1,0,0,1), glm::vec4(0,1,0,1),
		glm::vec4(0,0,1,1), glm::vec4(0.8f,0,0,5.0f),
		glm::vec4(0,1,1,1)
	};

	//static const int rows = 5;
	//static const int columns = 10;
	//static const int hSpace = 1;
	//static const int vSpace = 1;

	//static const glm::vec2 scrExtents(100, 50);
	//static const glm::vec2 boxExtents(7, 3);
	//static const glm::vec2 startPos(
	//	-(columns / 2)*((boxExtents.x * 2) + vSpace) + boxExtents.x + (vSpace / 2.0f),
	//	scrExtents.y - ((boxExtents.y * 2) + hSpace));

	//glm::vec2 pos;
	//for (int y = 0; y < rows; y++) {
	//	pos = glm::vec2(startPos.x, startPos.y - (y* ((boxExtents.y * 2) + hSpace)));
	//	for (int x = 0; x < columns; x++) {
	//		aie::Gizmos::add2DAABBFilled(pos, boxExtents, colours[y]);
	//		pos.x += (boxExtents.x * 2) + vSpace;
	//	}
	//}

	

	//aie::Gizmos::add2DAABBFilled(glm::vec2(0, -40), glm::vec2(12, 2),
	//							 glm::vec4(1, 0, 1, 1));
	
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Physics_EngineApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	
	//static float aspectRatio = 16 / 9.0f;

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	float aspectRatio = (float)getWindowWidth() / getWindowHeight();
	aie::Gizmos::draw2D(glm::ortho<float> 
								(-100, 100, 
								 -100 / aspectRatio, 100 / aspectRatio, 
								 -1.0f, 1.0f));



	// done drawing sprites
	m_2dRenderer->end();
}

//void Physics_EngineApp::setupContinuousDemo(glm::vec2 startPos, float inclination,
//	float speed, float gravity)
//{
//	float t = 0;
//	float tStep = 0.5f;
//	float radius = 1.0f;
//	int segments = 12;
//	glm::vec4 colour = glm::vec4(1, 0, 0, 1);
//
//	float xPos;
//	float yPos;
//
//	//float degToRadians = glm::pi<float>() / 180.0f;
//	//inclination *= degToRadians;
//
//	glm::vec2 velocity = glm::vec2(sin(inclination), cos(inclination)) * speed;
//
//	while (t <= 5)
//	{
//		xPos = startPos.x + velocity.x * t;
//		yPos = startPos.y + velocity.y * t + 0.5f * gravity * t * t;
//
//		aie::Gizmos::add2DCircle(glm::vec2(xPos, yPos), radius, segments, colour);
//		t += tStep;
//	}
//}