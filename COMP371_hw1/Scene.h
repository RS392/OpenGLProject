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
<<<<<<< HEAD
#include "stdafx.h"
=======
#include "FileReader.h"
<<<<<<< HEAD
#include "RandomAttributeGenerator.h"
=======
>>>>>>> 056e9f22141f6419570fc81fb837f4e2779b5566
>>>>>>> b980d2b5d373896efba9002807568dc4eb66d181
using namespace std;

class Scene
{
private:
	RandomAttributeGenerator* generator;
	objects objects;

	bool initializeOpenGL();
	bool initializeProgram();
	bool cleanUp();
	GLuint loadShaders(string vertex_shader_path, string fragment_shader_path);

	void mouseCallBack(GLFWwindow* window, int xpos, int ypos);
	void makeSingleTree();
	void makeMultipleTrees();
	void drawObjects();
	void drawEverything();
	void applyTexture();
public:
	Scene();
	~Scene();
	int runEngine();
};

