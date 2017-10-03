#include "Scene.h"

// this is a comment for testing stuffs
#define BUTTON_UP   0 
#define BUTTON_DOWN 1

unsigned char keyState[255];
unsigned int ArrowKeyState[4];

void keyboard(unsigned char key, int x, int y){
	keyState[key] = BUTTON_DOWN;
}
void keyboard_up(unsigned char key, int x, int y){
	keyState[key] = BUTTON_UP;
}

void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		ArrowKeyState[0] = BUTTON_DOWN;
		break;
	case GLUT_KEY_DOWN:
		ArrowKeyState[1] = BUTTON_DOWN;
		break;
	case GLUT_KEY_LEFT:
		ArrowKeyState[2] = BUTTON_DOWN;
		break;
	case GLUT_KEY_RIGHT:
		ArrowKeyState[3] = BUTTON_DOWN;
		break;
	}
}
void SpecialInput_up(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		ArrowKeyState[0] = BUTTON_UP;
		break;
	case GLUT_KEY_DOWN:
		ArrowKeyState[1] = BUTTON_UP;
		break;
	case GLUT_KEY_LEFT:
		ArrowKeyState[2] = BUTTON_UP;
		break;
	case GLUT_KEY_RIGHT:
		ArrowKeyState[3] = BUTTON_UP;
		break;
	}
}

//mouse
#define MOUSE_LEFT 0
#define MOUSE_MIDDLE 1
#define MOUSE_RIGHT 2

unsigned char mouseState[3];

GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
GLfloat lastX = 1600 / 2.0;
GLfloat lastY = 1000 / 2.0;
bool firstMouse = true;

void mouse(int button, int button_state, int x, int y) {
	
	#define state ( (button_state== GLUT_DOWN) ? BUTTON_DOWN : BUTTON_UP )
	
	switch (button) {
	
		case GLUT_LEFT_BUTTON:
			mouseState[MOUSE_LEFT] = state;break;

		case GLUT_MIDDLE_BUTTON:
			mouseState[MOUSE_MIDDLE] = state; break;

		case GLUT_RIGHT_BUTTON:
			mouseState[MOUSE_RIGHT] = state; break;
	}
}

void mousePassiveMove(int x, int y) {
	
	if (firstMouse) {
		lastX = x;
		lastY = y;
		firstMouse = false;
	}
	
	GLfloat xoffset = x - lastX;
	GLfloat yoffset = lastY - y; // Reversed since y-coordinates go from bottom to left
	lastX = x;
	lastY = y;
	GLfloat sensitivity = 0.5;//
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	yaw += xoffset;
	pitch += yoffset;
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	//camera->setCameraFront(glm::normalize(front));
}


int sceneSwitch;

Scene* MainScene = new Scene;

bool mainMenu = true;
bool gameInit = false;

//int argcSet;
//char* argvSet;

/****************************************************/
// Filename: main.cpp
// Created: Liam Haliday
// Description: sets up the menu
/****************************************************/
void init(int argc, char** argv)
{
//	Example* example = new Example();


//	glutFullScreen();

	
	MainScene->init();

}

/****************************************************/
// Filename: main.cpp
// Created: Liam Haliday
// Description: render the Scenes 
/****************************************************/
void render(void)
{

	MainScene->render();


}

/****************************************************/
// Filename: main.cpp
// Created: Liam Haliday
// Description: updates the Scenes 
/****************************************************/
bool fullScreen = false;
bool fullscreenButton = true;

void update() {
	// update game information.
	glutPostRedisplay();
	glutSetCursor(GLUT_CURSOR_NONE);
	
	glutMouseFunc(mouse);
	glutMotionFunc(mousePassiveMove);
	glutPassiveMotionFunc(mousePassiveMove);


	MainScene->update(keyState, ArrowKeyState, mouseState, lastX, lastY);

	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);

	if (keyState[27] == BUTTON_DOWN) { exit(0); } //right 

	std::cout << std::endl;

	glutSpecialFunc(SpecialInput);
	glutSpecialUpFunc(SpecialInput_up);
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 5); glutInitWindowSize(1600, 1000);
	glutCreateWindow("ANGRY BIRDS");
	glewInit();
	init(argc, argv);
	glutDisplayFunc(render);
	glutIdleFunc(update);
	//mouse parts

	glutMainLoop();
	return 0;
}

