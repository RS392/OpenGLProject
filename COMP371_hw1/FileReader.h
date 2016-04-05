#pragma once
#include <vector>
#include "../glew/glew.h"		// include GL Extension Wrangler

#include "../glfw/glfw3.h"  // include GLFW helper library

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtc/constants.hpp"


using namespace std;
using namespace glm;
typedef struct
{
	unsigned char imageTypeCode;
	short int imageWidth;
	short int imageHeight;
	unsigned char bitCount;
	unsigned char *imageData;
} TGAFILE;
class FileReader
{

public:
	void loadTGAFile(char *filename, TGAFILE *tgaFile);
	//GLuint loadTGA(const char * imagepath);
	bool loadObj(const char * path, vector < vec3 > & out_vertices, vector < vec2 > & out_uvs, vector < vec3 > & out_normals, vector <vec3> &  out_tangents, vector <vec3> & out_bitangents);
	FileReader();
	~FileReader();
};

