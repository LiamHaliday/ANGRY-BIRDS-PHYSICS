// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: object.cpp
// Description	: object class
// Author		: Liam Haliday
// Mail			: liamhaliday@gmail.com	

#include "object.h"


object::object()
{
	GLuint vao = NULL;
	GLuint vbo = NULL;
	GLuint ebo = NULL;
};

/****************************************************/
// Filename: object.cpp
// Created: Liam Haliday
// Description: set up the object
/****************************************************/
void object::createObj(GLfloat *vert, int vertSize, GLuint *ind, int indSize)
{
	ShaderLoader ShadLoader;
	program = ShadLoader.CreateProgram("Assets/shaders/Main.vs", "Assets/shaders/Main.fs");

	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height;
	unsigned char* image =
		SOIL_load_image(imageLoc, // file name 
		&width, //width of the image 
		&height, // height of the image
		0, // number of channels 
		SOIL_LOAD_RGBA);// load RGB values only

	//std::cout << image;
	if (!image)
	{
		std::cout << "no image";
	}

	glTexImage2D(GL_TEXTURE_2D, // type of texture 
		0, //mipmap level 
		GL_RGBA,// format of RGB values to be stored 5225
		width, // width of resulting texture 
		height, //height of resulting texture 
		0, //value must be 0 
		GL_RGBA,// format of the pixel data 
		GL_UNSIGNED_BYTE,// type of data passed in 
		image);//pointer to image data in memory




	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenVertexArrays(1, &this->vao);
	//glGenBuffers(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenVertexArrays(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, vertSize, vert, GL_STATIC_DRAW);

	glGenVertexArrays(1, &this->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, ind, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0, //Layout Location on vertex shader
		3, //3 vertices
		GL_FLOAT, // type of data
		GL_FALSE, //data Normalized?
		8 * sizeof(GLfloat), // stide
		(GLvoid*)0); // offset

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat), // size of data
		(GLvoid*)(3 * sizeof(GLfloat))); // stride

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat), // size of data
		(GLvoid*)(6 * sizeof(GLfloat))); // stride

	glEnableVertexAttribArray(2);

	
};

/****************************************************/
// Filename: object.cpp
// Created: Liam Haliday
// Description: renders the object
/****************************************************/
void object::render(float one, float two, float three, bool moving, camera tryingCamera)
{
	//leak test

	//leak test
	glUseProgram(program);

	if (moving)
	{
//main-cam-----------------------------------------------------------------------------------------------------------------
		tryingCamera.draw(program, 0.0f, false, one, two, three);
//main-cam-----------------------------------------------------------------------------------------------------------------
	}
	else
	{
		tryingCamera.drawflat(program, 0.0f, false, one, two, three);
	}


	glBindTexture(GL_TEXTURE_2D, this->texture);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE); // anti-aliasing


	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
};

/****************************************************/
// Filename: object.cpp
// Created: Liam Haliday
// Description: sets the texture 
/****************************************************/
void object::setImage(const char* image)
{
	imageLoc = image; 
}

/****************************************************/
// Filename: object.cpp
// Created: Liam Haliday
// Description: gets the Vertices
/****************************************************/
void object::setVert(GLfloat vertices)
{
	vec_vertices.push_back(vertices);
}

/****************************************************/
// Filename: object.cpp
// Created: Liam Haliday
// Description: gets the indices
/****************************************************/
void object::setInd(GLuint indices)
{
	vec_indices.push_back(indices);
}