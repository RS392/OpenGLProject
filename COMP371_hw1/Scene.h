#pragma once



#include "../glew/glew.h"		// include GL Extension Wrangler

#include "../glfw/glfw3.h"  // include GLFW helper library

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtc/constants.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <sstream>
#include "stdafx.h"
#include "FileReader.h"
#include "RandomAttributeGenerator.h"
#include "Terrain.h"
#include "ctime"
#include "Camera.h"
#include "UserInput.h"
using namespace std;
struct Light {
	glm::vec3 position;
	glm::vec3 intensities; //a.k.a. the color of the light
};

// ...


class Scene
{
private:
	
	RandomAttributeGenerator* generator;
	objects originalObjects; // as read from the file
	objects objectsInMemory; // total objects in the scene
	objects objectsToDraw; // objects that are considered by opengl to be drawn
	objects objectsInTransit; // objects that are moving between the inMemory and toDraw
	clock_t time;
	int numberOfOriginalObjects;
	Terrain *terrain;
	vec3 oldPlayerPos;
	vec3 lastFrameCamPos;
	vector<vec3> treeNormals;
	vector<mat4> terrainTranslationMatrices;
	vector<mat4> boundaryTransformationMatrices;
	

	GLfloat boundaries[60];
	// puts the new objects that should be considered into the objects that need to be drawn by opengl
	void renewObjectsToDraw();
	void handleCollisionWithCamera();
	// very cool algorithm: Using a thread to do it along with a mutex, this method checks through all the objects once in a while
	// to see if each object is inside the (SEERADIUS times a contant) of the player( hwo far he can see). If it is, it will go
	// inside the inTransit array which will then go inside the toDraw array when it is done computing.
	void optimizeVBO();
	void constructEnvironment();
	vec3 getCameraPos();
	bool initializeOpenGL();
	bool cleanUp();
	GLuint loadShaders(string vertex_shader_path, string fragment_shader_path);
	void test();
	// reads the .obj files to put them into originalObjects array
	void makeOriginalObjects();
	void drawObjects(); // not used anymore
	void drawTexturizedObjects();
	void drawEverything();
	void drawTerrain();
	void setBoundaries();
	void drawBoundaries();
	void boundariesCollision();
	GLuint testTexture(char*);
	GLuint testObjectsTextures(TGAFILE);
	void applyTexture();
	void setTerrainTranslationMatrices();
	void moveTiles();
	void createStars();
	void drawStars();
public:
	Scene();
	~Scene();
	// starts up the machineeeeeeeeeeeeeee
	int runEngine();
};

