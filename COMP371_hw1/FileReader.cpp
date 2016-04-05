#include "stdafx.h"
#include "FileReader.h"




FileReader::FileReader()
{
}




void FileReader::loadTGAFile(char *filename, TGAFILE *tgaFile)
{
	FILE *filePtr;
	unsigned char ucharBad;
	short int sintBad;
	long imageSize;
	int colorMode;
	unsigned char colorSwap;

	// Open the TGA file.
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
	{
		cout << "couldnt open tga file: " << filename << endl;
		return;
	}

	// Read the two first bytes we don't need.
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	// Which type of image gets stored in imageTypeCode.
	fread(&tgaFile->imageTypeCode, sizeof(unsigned char), 1, filePtr);

	// For our purposes, the type code should be 2 (uncompressed RGB image)
	// or 3 (uncompressed black-and-white images).
	if (tgaFile->imageTypeCode != 2 && tgaFile->imageTypeCode != 3)
	{
		fclose(filePtr);
		return;
	}

	// Read 13 bytes of data we don't need.
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);

	// Read the image's width and height.
	fread(&tgaFile->imageWidth, sizeof(short int), 1, filePtr);
	fread(&tgaFile->imageHeight, sizeof(short int), 1, filePtr);

	// Read the bit depth.
	fread(&tgaFile->bitCount, sizeof(unsigned char), 1, filePtr);

	// Read one byte of data we don't need.
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	// Color mode -> 3 = BGR, 4 = BGRA.
	colorMode = tgaFile->bitCount / 8;
	imageSize = tgaFile->imageWidth * tgaFile->imageHeight * colorMode;

	// Allocate memory for the image data.
	tgaFile->imageData = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);

	// Read the image data.
	fread(tgaFile->imageData, sizeof(unsigned char), imageSize, filePtr);
	
	// Change from BGR to RGB so OpenGL can read the image data.
	for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
	{
		colorSwap = tgaFile->imageData[imageIdx];
		tgaFile->imageData[imageIdx] = tgaFile->imageData[imageIdx + 2];
		tgaFile->imageData[imageIdx + 2] = colorSwap;
	}
	
	fclose(filePtr);
	return;
}

bool FileReader::loadObj(const char * path, vector < vec3 > & out_vertices, vector < vec2 > & out_uvs, vector < vec3 > & out_normals, vector <vec3> out_tangents, vector <vec3> out_bitangents) {
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector< vec3 > temp_vertices;
	vector< vec2 > temp_uvs;
	vector< vec3 > temp_normals;
	FILE * file = fopen(path, "r");
	if (file == NULL) {
		cout << "couldnt open file: " << path << endl;
		return false;
	}

	while (true) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				 // else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;

			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);


			//-------------- process data
			
		}
	}
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		vec3 normal = temp_normals[normalIndex - 1];
		out_normals.push_back(normal);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		vec2 uv = temp_uvs[uvIndex - 1];
		out_uvs.push_back(uv);
	}
	//compute tangents and bitangents. 
	//http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
	for (unsigned int i = 0; i < out_vertices.size(); i+=3) {
		glm::vec3 & v0 = out_vertices[i];
		glm::vec3 & v1 = out_vertices[i+1];
		glm::vec3 & v2 = out_vertices[i+2];

		glm::vec2 & uv0 = out_uvs[i];
		glm::vec2 & uv1 = out_uvs[i+1];
		glm::vec2 & uv2 = out_uvs[i+2];

		//Vertices delta
		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;

		glm::vec2 deltauv1 = uv1 - uv0;
		glm::vec2 deltauv2 = uv2 - uv0;
		
		//compute tangent and bitangent

		float r = 1.0f / (deltauv1.x * deltauv2.y - deltauv1.y* deltauv2.x);
		glm::vec3 tan = (deltaPos1 * deltauv2.y - deltaPos2 * deltauv1.y)*r;
		glm::vec3 bitan = (deltaPos2*deltauv1.x - deltaPos1 * deltauv2.x) * r;

		//push one for each vertex
		out_tangents.push_back(tan);
		out_tangents.push_back(tan);
		out_tangents.push_back(tan);

		out_bitangents.push_back(bitan);
		out_bitangents.push_back(bitan);
		out_bitangents.push_back(bitan);

	}
}
FileReader::~FileReader()
{
}

/*
void Scene::loadObj(const char* filename, vector<glm::vec4> &vertices, vector<glm::vec3> &normals, vector<GLushort> &elements)
{
ifstream in(filename, ios::in);
if (!in)
{
cerr << "Cannot open " << filename << endl; exit(1);
}

string line;
while (getline(in, line))
{
if (line.substr(0, 2) == "v ")
{
istringstream s(line.substr(2));
glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
vertices.push_back(v);
}
else if (line.substr(0, 2) == "f ") // need to change this because it doesnt work properly with the format given
{
istringstream s(line.substr(2));
GLushort a, b, c;
s >> a; s >> b; s >> c;
a--; b--; c--;
elements.push_back(a); elements.push_back(b); elements.push_back(c);
}

else if (line[0] == '#')
{
// coment
}
else
{

}
}


// THIS PART DOES NOT WORK

normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
for (int i = 0; i < elements.size(); i += 3)
{
cout << "crash" << endl;
GLushort ia = elements[i];
GLushort ib = elements[i + 1];
GLushort ic = elements[i + 2];
cout << "ib: " << ic << endl;
glm::vec3 normal = glm::normalize(glm::cross(
glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));

normals[ia] = normals[ib] = normals[ic] = normal;
}
}
}
*/