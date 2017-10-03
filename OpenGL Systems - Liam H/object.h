// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: object.h
// Description	: object class
// Author		: Liam Haliday
// Mail			: liamhaliday@gmail.com	

#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include "Dependencies\FMOD\fmod.hpp"

#include "ShaderLoader.h"
#include "camera.h"

#include <vector>
#include <string>

#include <stdlib.h>    
#include <time.h>  



class object
{
public:

	object();
	//~object();

	void render(float one, float two, float three, float angle, camera tryingCamera);
	void createObj(GLfloat *vert, int vertSize, GLuint *ind, int indSize); //GLfloat vertices, GLuint indices

	void CreateModel();
	void RenderModel();



	void setVert(GLfloat vertices);
	void setInd(GLuint indices);
	void setImage(const char* image);


private:

	GLuint program;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint texture;

	float lootatX = 0;
	float lootatY = 0;
	float lootatZ = 0;
	float camerafront = 0.01f;
	float speed = 0.01f;

	const char* imageLoc;

	std::vector<GLfloat> vec_vertices;
	std::vector<GLint> vec_indices;

	GLfloat m_vertices;
	GLuint m_indices;

	GLfloat vertices[500];
	GLuint indices[100];

	camera Cam;
	camera *CamPoint;

};

#endif