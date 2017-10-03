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
		FIRE,
		MOVING
	};

	int fireState;

	// mouse XYs
	float holdingX;
	float holdingY;

	float currentMouseX;
	float currentMouseY;


	void Setsquare();
	void SetFloor();

	FMOD::System* audioMgr;
	FMOD::Sound* hitSound;
	FMOD::Sound* bgMusic;

	float adjacent;
	float opposite;

	void init();
	void render();

	void Box2DInit();
	void Box2DUpdate(unsigned char *keyState, unsigned int *ArrowKeyState, unsigned char *mouseState, GLfloat lastX, GLfloat lastY);

	void SetStarFloor();

	void update(unsigned char *keyState, unsigned int *ArrowKeyState, unsigned char *mouseState, GLfloat lastX, GLfloat lastY);

	void Setenemy();

	void SetGround();

	camera mainCam;

	
	b2BodyDef groundBodyDef;
	b2Body* groundBody;
	b2PolygonShape groundBox;


	b2BodyDef bodyDef;
	b2Body* body;

	b2BodyDef boxDef;
	b2Body* box[6];

	b2BodyDef mouseBodyDef;
	b2Body *mouseBody;

	//windmill

	b2BodyDef windmillDef;
	b2Body* windBlade;
	b2Body* windStand;

	b2Body *slingPoint;
	b2DistanceJointDef sJ;
	b2Joint *StringJoint;

	b2DistanceJointDef djd;
	b2Joint *jj;

	b2FixtureDef fixtureDef;
	b2FixtureDef fixtureDefBOX;
	b2FixtureDef fixtureDefMill;

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// Mouse Joint
	b2Vec2 inGameMouse;


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
	objectStruct mouse;
	objectStruct stingStick;


	objectStruct windmillBlade;
	objectStruct windmillStand;


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