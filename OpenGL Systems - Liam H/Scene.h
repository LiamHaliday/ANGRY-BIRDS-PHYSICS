#pragma once

#ifndef SCENE_H
#define SCENE_H


#include "object.h"
#include "Text.h"
#include "Box2D/Box2D.h"

enum Scenes
{
	MAINMENU,
	GAMESCENE
};

struct objectStruct
{
	object object;
	float xCoord;
	float yCoord;
	float zCoord;
	float mag;
	float dir;

	int direction;
};


class Scene
{
public:

//	Scene();

	
	enum fireControll
	{
		STARTING,
		HOLDING,
		FIRE
	};
	int fireState;

	float holdingX;
	float holdingY;


	void Setsquare();
	void SetFloor();


	FMOD::System* audioMgr;
	FMOD::Sound* hitSound;
	FMOD::Sound* bgMusic;

	float adjacent;
	float opposite;

	void init(int argc, char** argv);
	void render();

	void Box2DInit(int argc, char ** argv);
	void Box2DUpdate(unsigned char *keyState, unsigned int *ArrowKeyState, unsigned char *mouseState, GLfloat lastX, GLfloat lastY);

	void SetStarFloor();

	void update(unsigned char *keyState, unsigned int *ArrowKeyState, unsigned char *mouseState, GLfloat lastX, GLfloat lastY);

	void Setenemy();

	void SetGround();

	camera mainCam;

	// Define the ground body.
	b2BodyDef groundBodyDef;

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody;

	// Define the ground box shape.
	b2PolygonShape groundBox;


	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;

	b2Body* body;

	b2BodyDef boxDef;
	b2Body* box[4];

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;


private:

	// star wall scroll
	float starScrollPoint[2];
	float starScrollPointBack[2];
	float starScrollPointBack2[2];

	//object* enemy = new object();
	float bulletsPlace = 4.0f;
	bool startPHYX = false;

	float fireTime = 0.1;
	float fireDifference = 0.0;
	float fireDifferencep2 = 0.0;
	float BulletX;
	bool IsLeft = false;

	//text
	TextLabel* label;
	TextLabel* endlabel;
	TextLabel* EnterToRestart;
	TextLabel* FPS;

	objectStruct player;
	objectStruct Ground;
	objectStruct mainMenuObject;

	std::vector<objectStruct> starFloor;

	object floor;
	object end;
	bool lost = false;

	bool buletStart = false;

	//bullets 
	std::vector<objectStruct> bullets;
	int bulletsInUse;

	std::vector<objectStruct> bullets2;
	int bulletsInUse2;


	std::vector<objectStruct> pinkEnemys;
	std::vector<objectStruct> greenEnemys;

	std::vector<objectStruct> Stars;

	glm::vec2 whiteBoxVec;

	//keyboard bits
	unsigned char keyState[255];
	float Playerspeed;
	float enemySpeed;
	float changeableSpeed = 0.0005f;

	float CamLookX = 0.0f;
	float CamLookY = 0.0f;
	float CamLookZ = 0.0f;

	glm::vec3 camLoc{ 0.0, 5.0, 0.0 };
	glm::vec3 camLook{ 0, 0, 0};

	// deltaTime
	float deltaTime;
	float currentFrame;
	float lastFrame;

	float CurrentFPS;
};

#endif