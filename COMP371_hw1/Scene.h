#pragma once



#include "glew.h"		// include GL Extension Wrangler

#include "glfw3.h"  // include GLFW helper library

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"

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
using namespace std;

class Scene
{
private:
	bool initialize();
	bool cleanUp();
	GLuint loadShaders(string vertex_shader_path, string fragment_shader_path);
public:
	Scene();
	~Scene();
	int runEngine();
};

