// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Scene.cpp
// Description	: Scenes
// Author		: Liam Haliday
// Mail			: liamhaliday@gmail.com	

#include "Scene.h"
#include <iostream>



#define BUTTON_UP   0 
#define BUTTON_DOWN 1
#define UP 0;
#define DOWN 1;
#define LEFT 2;
#define RIGHT 3;

#define MOUSE_LEFT 0
#define MOUSE_MIDDLE 1
#define MOUSE_RIGHT 2

// Define the gravity vector.
b2Vec2 gravity(0.0f, -10.0f);

// Construct a world object, which will hold and simulate the rigid bodies.
b2World world(gravity);


void Scene::init()
{

	//star Scroll Point array (place where the fucking stars are bitch)
	starScrollPoint[0] = 0.0f;
	starScrollPoint[1] = -10.0f;

	starScrollPointBack[0] = 5.0f;
	starScrollPointBack[1] = -5.0f;

	starScrollPointBack2[0] = 5.0f;
	starScrollPointBack2[1] = -5.0f;


	FPS = new TextLabel("End score", "Assets/fonts/arial.ttf");
	FPS->setPosition(glm::vec2(1350.0f, 900.0f));
	FPS->setColor(glm::vec3(1.0f, 1.0f, 0.0f));


	//player creation
	player.object.setImage("Assets/images/GreenPlayer.png");
	Ground.object.setImage("Assets/images/greenGrass.png");

	player.xCoord = 0.5f;
	Ground.xCoord = -0.5f;

	player.yCoord = 1.5f;
	Ground.yCoord = 1.5f;

	player.zCoord = 0.05f;
	Ground.zCoord = 0.05f;

	Setsquare();	
	SetGround();
	


	for (int b = 0; b < 6; b++)
	{
		objectStruct * floor = new objectStruct;

		floor->direction = 0;
		floor->xCoord = 0;
		floor->yCoord = 0;
		starFloor.push_back(*floor);
		delete floor;
		if (starFloor.size() <= 2)
		{
			starFloor[starFloor.size() - 1].object.setImage("Assets/images/sky backGround.png");	// Back Layer
		}
		else if (starFloor.size() > 2 && starFloor.size() <= 4)
		{
			starFloor[starFloor.size() - 1].object.setImage("Assets/images/sky backGround.png");	// Middle Layer
		}
		else
		{
			starFloor[starFloor.size() - 1].object.setImage("Assets/images/Top_Stars - Copy.png");	// Front Layer
		}

		SetStarFloor();
	}

	// pink
	for (int i = 0; i < 6; i++)
	{
		objectStruct* enemy = new objectStruct();
		pinkEnemys.push_back(*enemy);
		delete enemy;
		pinkEnemys[pinkEnemys.size() - 1].object.setImage("Assets/images/BOX.png");
		Setenemy();
	}



	//floor.setImage("Assets/images/blueBOX.png");
	//SetFloor();

	camLoc.y = 5.59f;
	camLoc.x = 0.0f;
	camLoc.z = 0.0f;//-2.5f;



	GLfloat vertices[] = {
		//		//position				//color				//texture coord
		// Fill in the top face vertex data.
		-0.05f, 0.0f, -0.05f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.05f, 0.0f, 0.05f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.05f, 0.0f, 0.05f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.05f, 0.0f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	};

	GLuint indices[] = {
		// front
		0, 1, 2,
		0, 2, 3,

	};

	GLfloat * playerVert = vertices;
	GLuint * playerInd = indices;

	mouse.object.setImage("Assets/images/jumper.png");
	mouse.object.createObj(playerVert, sizeof(vertices), playerInd, sizeof(indices));

	// stick object

	GLfloat verticesstingStick[] = {
		//		//position				//color				//texture coord
		// Fill in the top face vertex data.
		-0.5f, 0.0f, -2.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.0f, -2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	};

	GLuint indicesstingStick[] = {
		// front
		0, 1, 2,
		0, 2, 3,
	};

	GLfloat * playerVertstick = verticesstingStick;
	GLuint * playerIndstick = indicesstingStick;

	stingStick.object.setImage("Assets/images/sling.png");
	stingStick.object.createObj(playerVertstick, sizeof(verticesstingStick), playerIndstick, sizeof(indicesstingStick));



	// windmill

	GLfloat verticesstingBlade[] = {
		//		//position				//color				//texture coord
		// Fill in the top face vertex data.
		-0.5f, 0.0f, -2.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.0f, -2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	};

	GLuint indicesstingBlade[] = {
		// front
		0, 1, 2,
		0, 2, 3,
	};

	GLfloat * playerVertBlade = verticesstingBlade;
	GLuint * playerIndBlade = indicesstingBlade;

	windmillBlade.object.setImage("Assets/images/BOX.png");
	windmillBlade.object.createObj(verticesstingBlade, sizeof(playerVertBlade), indicesstingBlade, sizeof(playerIndBlade));

	//  --------------- stand --------------- --------------- stand --------------- --------------- stand ---------------

	GLfloat verticesstingStand[] = {
		//		//position				//color				//texture coord
		// Fill in the top face vertex data.
		-0.25f, 0.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.25f, 0.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	};

	GLuint indicesstingStand[] = {
		// front
		0, 1, 2,
		0, 2, 3,
	};

	GLfloat * playerVertStand = verticesstingStand;
	GLuint * playerIndStand = indicesstingStand;

	windmillStand.object.setImage("Assets/images/BOX.png");
	windmillStand.object.createObj(playerVertStand, sizeof(verticesstingStand), playerIndStand, sizeof(indicesstingStand));

	

	Box2DInit();


}




void Scene::render()
{
	//glClearColor(0.050f, 0.050f, 0.050f, 1.0f);
	glClearColor(0.00f, 0.0f, 0.025f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 3D
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//floor.render(0.0, 0.0, -1.0, 0.0 , true);             // put back from thing

	// RGBA Alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//starFloor[0].object.render(0.0f, -0.03f, starScrollPoint[0], 0.0f, mainCam);
	//starFloor[1].object.render(0.0f, -0.03f, starScrollPoint[1], 0.0f, mainCam);
   
	starFloor[2].object.render(0.0f, -0.01f, starScrollPointBack[0], 0.0f, mainCam);
	starFloor[3].object.render(0.0f, -0.01f, starScrollPointBack[1], 0.0f, mainCam);

	starFloor[4].object.render(0.0f, -0.00f, starScrollPointBack2[0], 0.0f, mainCam);
	starFloor[5].object.render(0.0f, -0.00f, starScrollPointBack2[1], 0.0f, mainCam);



	//-----------------------------BOX2D-----------------------------BOX2D-----------------------------BOX2D

	camLook.y = 0.0f;
	camLook.x = 0.0f;
	camLook.z = -2.5001;

	// Now print the position and angle of the body.


	b2Vec2 position = groundBody->GetPosition();
	float32 angle = groundBody->GetAngle();

	Ground.object.render(position.x, 0.001f, position.y, angle, mainCam);

	for (unsigned int i = 0; i < pinkEnemys.size(); i++)
	{

		position = box[i]->GetPosition();
		angle = box[i]->GetAngle();

		pinkEnemys[i].object.render(position.x, player.zCoord, position.y, angle, mainCam);
	}

	position = slingPoint->GetPosition();
	angle = slingPoint->GetAngle();

	stingStick.object.render(position.x, 0.0001, position.y, 0.0f, mainCam);

	
	position = body->GetPosition();
	angle = body->GetAngle();

//	printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	std::cout << "playerX: " << position.x << ", playerY: " << position.y << ", angle: " << (angle * 180) / 3.14 << std::endl;

	player.object.render(position.x , player.zCoord, position.y , angle, mainCam);

	position = mouseBody->GetPosition();
	angle = mouseBody->GetAngle();

	mouse.object.render(position.x, player.zCoord, position.y, 0.0f, mainCam);

	//-----------------------------BOX2D-----------------------------BOX2D-----------------------------BOX2D


	position = windBlade->GetPosition();
	angle = windBlade->GetAngle();
	windmillBlade.object.render(position.x, 0.0002, position.y, 0.0f, mainCam);

	position = windStand->GetPosition();
	angle = windStand->GetAngle();
	windmillStand.object.render(position.x, 0.0001, position.y, 0.0f, mainCam);

	glDisable(GL_BLEND);

	FPS->Render();
	
	glutSwapBuffers();
}


void Scene::Box2DInit()
{
	//B2_NOT_USED(argc);
//	B2_NOT_USED(argv);


	groundBodyDef.position.Set(0.0f, -0.0f);

	groundBody = world.CreateBody(&groundBodyDef);

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(5.0f, 1.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);


	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(-3.0f, 1.5f);

	body = world.CreateBody(&bodyDef);

	b2CircleShape dynamicCircle;

	dynamicCircle.m_radius = 0.25f;
	fixtureDef.shape = &dynamicCircle;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 2.0f;
	// Override the default friction.
	fixtureDef.friction = 0.3f;
	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	//BOXES
	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;

	dynamicBox.SetAsBox(0.250f, 0.250f);
	boxDef.type = b2_dynamicBody;

	fixtureDefBOX.shape = &dynamicBox;
	fixtureDefBOX.friction = 0.3f;
	fixtureDefBOX.density = 2.0f;

	for (size_t i = 0; i < 6; i++)
	{	
		if (i >= 3)
		{
			boxDef.position.Set(3.0f, 1.25f + ((i - 3) * 0.5f));
		}
		else 
		{
			boxDef.position.Set(1.75f, 1.25f + (i * 0.5f) );
		}

		box[i] = world.CreateBody(&boxDef);
		box[i]->CreateFixture(&fixtureDefBOX);
	}

	camLoc.z = camLoc.z - 2.5;

	
	mouseBodyDef.type = b2_staticBody;
	mouseBodyDef.position.Set(inGameMouse.x, inGameMouse.y);
	mouseBody = world.CreateBody(&mouseBodyDef);

	mouseBodyDef.position.Set(-2.5f, 2.5f);
	slingPoint = world.CreateBody(&mouseBodyDef);

	sJ.bodyA = body;
	sJ.bodyB = slingPoint;

	sJ.length = 0.5f;
	sJ.frequencyHz = 2.5f;
	sJ.dampingRatio = 0.0;

	StringJoint = world.CreateJoint(&sJ);

	fireState = STARTING;	

	// windmill

	windmillDef.type = b2_dynamicBody; // was b2_dynamicBody
	windmillDef.position.Set(-3.0f, 2.5f);

	b2PolygonShape millShape;
	millShape.SetAsBox(1.0, 0.25);

	fixtureDefMill.shape = &millShape;
	fixtureDefMill.friction = 0.3f;
	fixtureDefMill.density = 2.0f;

	windBlade = world.CreateBody(&windmillDef);
	windBlade->CreateFixture(&fixtureDefMill);


	windmillDef.position.Set(-3.0f, 2.0f);

	windStand = world.CreateBody(&windmillDef);
	windStand->CreateFixture(&fixtureDefMill);


//	b2RevoluteJointDef rjd;
	
	//rjd.Initialize(windBlade, windStand, b2Vec2(0,0));

}


bool stringOn = true;


void Scene::Box2DUpdate(unsigned char *keyState, unsigned int *ArrowKeyState, unsigned char *mouseState, GLfloat lastX, GLfloat lastY)
{

	currentMouseX = lastX;
	currentMouseY = lastY;

	inGameMouse.x = (lastX / 100);
	inGameMouse.y = (lastY / 100);

	inGameMouse.x -= 5;
	inGameMouse.y -= 7.5;

	inGameMouse.y = -inGameMouse.y;
	//
	//inGameMouse.x = inGameMouse.x * 0.5;// (inGameMouse.x * 0.5);
	//inGameMouse.y = inGameMouse.y * 0.5;// (inGameMouse.y * 0.5)

		//if (inGameMouse.x > 5) { }
	//else if (inGameMouse.y > 5) {  }


	std::cout << "lastX: " << lastX << " lastY" << lastY << std::endl;
	std::cout << "in GameMouse X: " << inGameMouse.x << " in GameMouse Y:" << inGameMouse.y << std::endl;

	mouseBody->SetTransform(b2Vec2(inGameMouse.x, inGameMouse.y ), 0);

	// Now print the position and angle of the body.
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();

	if (mouseState[MOUSE_RIGHT])
	{
		//fireState = STARTING;	

		if (!stringOn)
		{
			body->SetTransform(b2Vec2(-3.0f, 1.5f), 0);
			
			sJ.bodyA = body;
			sJ.bodyB = slingPoint;
			
			sJ.length = 0.5f;
			sJ.frequencyHz = 2.5f;
			sJ.dampingRatio = 0.0;
			
			StringJoint = world.CreateJoint(&sJ);

			stringOn = true;
		}
	}

	if (keyState[(unsigned char)'R'] == BUTTON_DOWN || keyState[(unsigned char)'r'] == BUTTON_DOWN)
	{
		if (stringOn)
		{
			world.DestroyJoint(StringJoint);
		}

		body->SetTransform(b2Vec2(-3.0f, 1.5f), 0);

		sJ.bodyA = body;
		sJ.bodyB = slingPoint;

		sJ.length = 0.5f;
		sJ.frequencyHz = 2.5f;
		sJ.dampingRatio = 0.0;

		StringJoint = world.CreateJoint(&sJ);

		stringOn = true;

		for (size_t i = 0; i < 6; i++)
		{
			box[i]->SetAngularVelocity(0.0f);
			box[i]->SetLinearVelocity(b2Vec2(0.0f, 0.0f));


			if (i >= 3)
			{
				box[i]->SetTransform(b2Vec2(3.0f, 1.25f + ((i - 3) * 0.5f)), 0);
			}
			else
			{
				box[i]->SetTransform(b2Vec2(1.75f, 1.25f + (i * 0.5f)), 0);
			}
		}
	}


	switch (fireState)
	{
	case STARTING:
	{
		if (stringOn)
		{
			if (mouseState[MOUSE_LEFT]) {

				djd.bodyA = body;
				djd.bodyB = mouseBody;

				djd.length = 0.0f;
				djd.frequencyHz = 0.0f;
				djd.dampingRatio = 0.0;

				jj = world.CreateJoint(&djd);
				fireState = HOLDING;
				//holdingX = lastX; holdingY = lastY;
			}
		}
		// Joint



		break;
	}
	case HOLDING:
	{
		if (!mouseState[MOUSE_LEFT]) { fireState = FIRE; world.DestroyJoint(jj); }


		//body->ApplyForce(b2Vec2(0, 4), body->GetWorldCenter(), 0);


		break;
	}
	case FIRE:
	{
		//body->ApplyForce(b2Vec2(-((lastX - holdingX) / 2), ((lastY - holdingY) / 2)), body->GetWorldCenter(), 0);
		//startPHYX = true;
		//body->SetTransform(b2Vec2(position.x, position.y + 0.1f), 0);

		if (stringOn)
		{
			world.DestroyJoint(StringJoint);
			stringOn = false;
		}

		fireState = STARTING;

		break;
	}
	case MOVING:
	{
		if (body->GetLinearVelocity().x >= 0.1 || body->GetLinearVelocity().x <= -0.1 &&
			body->GetLinearVelocity().y >= 0.1 || body->GetLinearVelocity().y <= -0.1)
		{
			std::cout << "MOVING" << std::endl;
		}

		break;
	}
	default:
		break;
	}

		//body->SetLinearVelocity(b2Vec2(1, 0));
	//	b2Vec2 vel = body->GetLinearVelocity();
		std::cout << "body LinearVelocity x: " << body->GetLinearVelocity().x;
		std::cout << "body LinearVelocity y: " << body->GetLinearVelocity().y << std::endl;




//	printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

	position = groundBody->GetPosition();
	angle = groundBody->GetAngle();
	
//	printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

	world.DrawDebugData();
//	if (startPHYX)
	{
		world.Step(timeStep, velocityIterations, positionIterations);
	}


}




void Scene::update(unsigned char *keyState, unsigned int *ArrowKeyState, unsigned char *mouseState, GLfloat lastX, GLfloat lastY)
{
	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime / 1000;

	//delta time
	currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	CurrentFPS = ((1 / deltaTime) * 1000);
	//std::cout << currentTime << std::endl;

	Playerspeed = 0.003 * deltaTime;
	enemySpeed = changeableSpeed * deltaTime;


	std::string FPString = "FPS: ";
	FPString += std::to_string(int(CurrentFPS)).c_str();
	FPS->setText(FPString.c_str());

	if (keyState[(unsigned char)'i'] == BUTTON_DOWN) { camLoc.y -= Playerspeed; } //up
	if (keyState[(unsigned char)'k'] == BUTTON_DOWN) { camLoc.y += Playerspeed; } //down
	if (keyState[(unsigned char)'j'] == BUTTON_DOWN) { camLoc.x += Playerspeed; } //left
	if (keyState[(unsigned char)'l'] == BUTTON_DOWN) { camLoc.x -= Playerspeed; } //right 

	if (keyState[(unsigned char)'p'] == BUTTON_DOWN) { camLoc.z += Playerspeed; } //left
	if (keyState[(unsigned char)';'] == BUTTON_DOWN) { camLoc.z -= Playerspeed; } //right 


	for (size_t i = 0; i < 2; i++)
	{
		starScrollPoint[i] += 0.02f;
		if (starScrollPoint[i] > 10.0f)
		{
			starScrollPoint[i] = -10.0f;
		}
	}

	for (size_t i = 0; i < 2; i++)
	{
		starScrollPointBack[i] += 0.005f;
		if (starScrollPointBack[i] > 15.0f)
		{
			starScrollPointBack[i] = -5.0f;
		}
	}

	for (size_t i = 0; i < 2; i++)
	{
		starScrollPointBack2[i] += 0.015f;
		if (starScrollPointBack2[i] > 15.0f)
		{
			starScrollPointBack2[i] = -5.0f;
		}
	}


	Box2DUpdate(keyState, ArrowKeyState, mouseState, lastX, lastY);

	mainCam.movingCam(camLoc, camLook);
	
}

#pragma region objectstuff
void Scene::Setsquare()
{
	// square ver and ind
	GLfloat vertices[] = {
//		//position				//color				//texture coord
		// Fill in the top face vertex data.
		-0.25f, 0.0f, -0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.25f, 0.0f, 0.25f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.25f, 0.0f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.25f, 0.0f, -0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	};

	GLuint indices[] = {
		// front
		0, 1, 2,
		0, 2, 3,

	};


	GLfloat * playerVert = vertices;
	GLuint * playerInd = indices;
	
	player.object.createObj(playerVert, sizeof(vertices), playerInd, sizeof(indices));

}

void Scene::SetGround()
{
	// square ver and ind

	GLfloat vertices[] = {

		-5.0f, 0.0f, -1, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-5.0f, 0.0f, 1, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		5.0f, 0.0f, 1, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		5.0f, 0.0f, -1, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	};


	GLuint indices[] = {
		// front
		0, 1, 2,
		0, 2, 3,

	};

	GLfloat * ptrEnemyVert = vertices;
	GLuint * prtEnemyInd = indices;


	//	std::cout << "Object \n";
	Ground.object.createObj(ptrEnemyVert, sizeof(vertices), prtEnemyInd, sizeof(indices));

}

void Scene::SetFloor()
{

	//floor vec ands ind
	GLfloat floorVertices[] = {
			 
		// Fill 1n the t2p face vertex data.							 
		-0.10f,  0.0f, -0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,				 
		-0.10f,  0.0f,  0.10f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,				 
		 0.10f,   0.0f,  0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,				 
	 	 0.10f,   0.0f, -0.10f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,				 						 

	};


	GLuint floorIndices[] = {
		// front
		0, 1, 2,
		0, 2, 3,
	};


	GLfloat * testVert = floorVertices;
	GLuint * testInd = floorIndices;


	floor.createObj(testVert, sizeof(floorVertices), testInd, sizeof(floorIndices));
};

void Scene::SetStarFloor() 
{
	GLfloat vertices[] = {
		// Fill in the top face vertex data.							 
		-5.0f, 0.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-5.0f, 0.0f,  5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 5.0f, 0.0f,  5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 5.0f, 0.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	};

	GLuint indices[] = {
		// front
		0, 1, 2,
		0, 2, 3,

	};


	GLfloat * ptrEnemyVert = vertices;
	GLuint * prtEnemyInd = indices;


	starFloor[starFloor.size() - 1].object.createObj(ptrEnemyVert, sizeof(vertices), prtEnemyInd, sizeof(indices));

}

void Scene::Setenemy()
{
	// square ver and ind

	GLfloat vertices[192] = {

		-0.250f, 0.0f, -0.250f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.250f, 0.0f, 0.250f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.250f, 0.0f, 0.250f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.250f, 0.0f, -0.250f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	};


	GLuint indices[36] = {
		// front
		0, 1, 2,
		0, 2, 3,

	};

	GLfloat * ptrEnemyVert = vertices;
	GLuint * prtEnemyInd = indices;


	//	std::cout << "Object \n";
	pinkEnemys[pinkEnemys.size() - 1].object.createObj(ptrEnemyVert, sizeof(vertices), prtEnemyInd, sizeof(indices));

}

#pragma endregion 