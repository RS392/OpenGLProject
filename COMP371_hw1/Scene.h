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
using namespace std;

class Scene
{
private:
	RandomAttributeGenerator* generator;
	objects originalObjects;
	objects objects;
	int numberOfOriginalObjects;
	
	vector<vec3> treeNormals;
	vector<vec2> treeUvs;
	
	
	
	bool initializeOpenGL();
	bool initializeProgram();
	bool cleanUp();
	GLuint loadShaders(string vertex_shader_path, string fragment_shader_path);

	void mouseCallBack(GLFWwindow* window, int xpos, int ypos);
	void makeOriginalObjects();
	void makeMultipleObjects();
	void drawObjects();
	void drawEverything();
	void applyTexture();
public:
	Scene();
	~Scene();
	int runEngine();
};

