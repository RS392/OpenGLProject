#include "stdafx.h"
#include "Scene.h"
#include "CImg.h"
using namespace std;
using namespace glm;
using namespace cimg_library;
#define M_PI        3.14159265358979323846264338327950288   /* pi */
#define DEG_TO_RAD	M_PI/180.0f
#define SEEDISTANCE 1000

GLFWwindow* window = 0x00;
Object* pinet2;
GLuint shader_program = 0;
GLuint terrain_shader_program = 0;
GLuint feature_shader_program = 0;
bool terrainView = true;
GLuint view_matrix_id = 0;
GLuint model_matrix_id = 0;
GLuint proj_matrix_id = 0;
GLuint MVP_id = 0;
GLuint model_View_matrix_id = 0;
GLuint model_View_3x3_matrix_id = 0;
GLuint texture_location = 0;

GLuint textureID;

GLuint terr_textureID;
GLuint pinet1_textureID;
GLuint pinet2_textureID;
GLuint tree1_textureID;
GLuint tree2_textureID;
GLuint tree3_textureID;
GLuint tree4_textureID;
GLuint tree5_textureID;
GLuint tree6_textureID;
GLuint fern1_textureID;
GLuint fern2_textureID;
GLuint fern3_textureID;
GLuint flow2_textureID;
GLuint flow3_textureID;
GLuint shr1h_textureID;
GLuint shr2_textureID;
GLuint shr3_textureID;
GLuint shr4_textureID;
GLuint shr9_textureID;
GLuint shr15_textureID;
GLuint shr16_textureID;
GLuint shr17h_textureID;
GLuint weed1_textureID;
GLuint weed3_textureID;
GLuint weed4_textureID;
GLuint weed4a_textureID;
GLuint weed5_textureID;
GLuint weed6_textureID;
GLuint grass_textureID;

GLuint terr_texture_normalID;
GLuint pinet1_texture_normalID;
GLuint pinet2_texture_normalID;
GLuint tree1_texture_normalID;
GLuint tree2_texture_normalID;
GLuint tree3_texture_normalID;
GLuint tree4_texture_normalID;
GLuint tree5_texture_normalID;
GLuint tree6_texture_normalID;
GLuint fern1_texture_normalID;
GLuint fern2_texture_normalID;
GLuint fern3_texture_normalID;
GLuint flow2_texture_normalID;
GLuint flow3_texture_normalID;
GLuint shr1h_texture_normalID;
GLuint shr2_texture_normalID;
GLuint shr3_texture_normalID;
GLuint shr4_texture_normalID;
GLuint shr9_texture_normalID;
GLuint shr15_texture_normalID;
GLuint shr16_texture_normalID;
GLuint shr17h_texture_normalID;
GLuint weed1_texture_normalID;
GLuint weed3_texture_normalID;
GLuint weed4_texture_normalID;
GLuint weed4a_texture_normalID;
GLuint weed5_texture_normalID;
GLuint weed6_texture_normalID;
GLuint grass_texture_normalID;

TGAFILE tree1TGA;
TGAFILE tree2TGA;
TGAFILE tree3TGA;
TGAFILE tree4TGA;
TGAFILE tree5TGA;
TGAFILE tree6TGA;
TGAFILE pinet1TGA;
TGAFILE pinet2TGA;
TGAFILE fern1TGA;
TGAFILE fern2TGA;
TGAFILE fern3TGA;
TGAFILE flow2TGA;
TGAFILE flow3TGA;
TGAFILE shr1hTGA;
TGAFILE shr2TGA;
TGAFILE shr3TGA;
TGAFILE shr4TGA;
TGAFILE shr9TGA;
TGAFILE shr15TGA;
TGAFILE shr16TGA;
TGAFILE shr17hTGA;
TGAFILE weed1TGA;
TGAFILE weed3TGA;
TGAFILE weed4TGA;
TGAFILE weed4aTGA;
TGAFILE weed5TGA;
TGAFILE weed6TGA;
TGAFILE grassTGA;
TGAFILE terrainTGA;

TGAFILE tree1_normalTGA;
TGAFILE tree2_normalTGA;
TGAFILE tree3_normalTGA;
TGAFILE tree4_normalTGA;
TGAFILE tree5_normalTGA;
TGAFILE tree6_normalTGA;
TGAFILE pinet1_normalTGA;
TGAFILE pinet2_normalTGA;
TGAFILE fern1_normalTGA;
TGAFILE fern2_normalTGA;
TGAFILE fern3_normalTGA;
TGAFILE flow2_normalTGA;
TGAFILE flow3_normalTGA;
TGAFILE shr1h_normalTGA;
TGAFILE shr2_normalTGA;
TGAFILE shr3_normalTGA;
TGAFILE shr4_normalTGA;
TGAFILE shr9_normalTGA;
TGAFILE shr15_normalTGA;
TGAFILE shr16_normalTGA;
TGAFILE shr17h_normalTGA;
TGAFILE weed1_normalTGA;
TGAFILE weed3_normalTGA;
TGAFILE weed4a_normalTGA;
TGAFILE weed4_normalTGA;
TGAFILE weed5_normalTGA;
TGAFILE weed6_normalTGA;
TGAFILE grass_normalTGA;
TGAFILE terrain_normalTGA;

int height = 500, heightB = 600;
int width = 800, widthB = 800;

///Transformations
glm::mat4 proj_matrix;
glm::mat4 view_matrix;
glm::mat4 model_matrix(1.0f);
glm::mat4 model_View_matrix;
glm::mat3 model_View_3x3_matrix;
glm::mat4 MVP;

GLuint VBO, VAO, EBO, TBO, VBO2, VBO3, VBO4;

GLfloat point_size = 3.0f;



bool clicked;
double oldX = 0;
double oldY = 0;
GLfloat displacementz = 0.0f;
GLfloat displacementx = 0.0f;

bool threadDone;
tdogl::Camera gCamera;
Light light;
double gScrollY = 0.0;

bool lightOn = true;

//To leave enough space for the objects drawn at the very edge of the forest
GLfloat boundOffset = 50;

// update the scene based on the time elapsed since last update
void Update(float secondsElapsed) {

	//move position of camera based on WASD keys, and XZ keys for up and down
	const float moveSpeed = 1000.0f; //units per second
	bool moving = false;
	if (glfwGetKey(window, 'S')) {
		moving = true;
		gCamera.offsetPosition(secondsElapsed * moveSpeed * -gCamera.forward());
	}
	else if (glfwGetKey(window, 'W')) {
		//cout << "moving north" << endl;
		moving = true;
		gCamera.offsetPosition(secondsElapsed * moveSpeed * gCamera.forward());
	}
	if (glfwGetKey(window, 'A')) {
		moving = true;
		gCamera.offsetPosition(secondsElapsed * moveSpeed * -gCamera.right());
	}
	else if (glfwGetKey(window, 'D')) {
		moving = true;
		gCamera.offsetPosition(secondsElapsed * moveSpeed * gCamera.right());
	}
	if (glfwGetKey(window, 'Z')) {
		gCamera.offsetPosition(secondsElapsed * moveSpeed * -glm::vec3(0, 1, 0));
	}
	else if (glfwGetKey(window, 'X')) {
		gCamera.offsetPosition(secondsElapsed * moveSpeed * glm::vec3(0, 1, 0));
	}

	//rotate camera based on mouse movement
	const float mouseSensitivity = 0.1f;
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	gCamera.offsetOrientation(mouseSensitivity * (float)mouseY, mouseSensitivity * (float)mouseX);
	glfwSetCursorPos(window, 0, 0); //reset the mouse, so it doesn't go out of the window

									 //increase or decrease field of view based on mouse wheel
	
	const float zoomSensitivity = -0.2f;
	float fieldOfView = gCamera.fieldOfView() + zoomSensitivity * (float)gScrollY;
	if (fieldOfView < 5.0f) fieldOfView = 5.0f;
	if (fieldOfView > 130.0f) fieldOfView = 130.0f;
	gCamera.setFieldOfView(fieldOfView);
	if (lightOn == true) {
		light.position = gCamera.position();
		light.position.y -= 1.5;
	}
	else
		light.position = vec3(-10, -1000, -10);

	gScrollY = 0;
}
// records how far the y axis has been scrolled
void OnScroll(GLFWwindow* window, double deltaX, double deltaY) {
	gScrollY += deltaY;
}

void flashlightPressed(GLFWwindow *_window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_F) {
		if (action == GLFW_PRESS) {

			if (lightOn == true) {
				lightOn = false;
				//cout << "Light is off" << endl;
			}
			else if (!lightOn) {
				lightOn = true;
				//cout << "Light is on" << endl;
			}
		}
	}
}


Scene::Scene()
{
	UserInput* title = new UserInput();
	generator = new RandomAttributeGenerator();
	generator->setTitle(title);
	//cout << title->getMultiplier();

	numberOfOriginalObjects = 28;
	for (int i = 0; i < numberOfOriginalObjects; ++i) {
		Object* obj = new Object(); // empty place holder to allocate memory
		
		originalObjects.push_back(obj);
	}
	
	pinet2 = new Object();
	//pinet2->combineVXUvs();
	time = clock();
	glm::vec3 cameraPosition(0.0, 20, RADIUS);
//	gCamera.setNearAndFarPlanes(0.1f,5000.0f);
	gCamera.setNearAndFarPlanes(5.0f, SEEDISTANCE);

	gCamera.setPosition(cameraPosition);
	terrain = new Terrain(cameraPosition);//for testing
	setTerrainTranslationMatrices();
	//gCamera.setPosition(glm::vec3(0,0,0));//near terrain
	//gCamera.setViewportAspectRatio(width / height);

}

Scene::~Scene()
{
}
/*
	Creates a vector containing a set of matrices to be used in the vertex shader to tile the terrain.
	If the camera moves past a threshold where the terrain exists, more matrices should be pushed to this vector
*/
void Scene::setTerrainTranslationMatrices() 
{
	mat4 transform_matrix = mat4(1.0f);
	vec3 translateVector = vec3(terrain->getTranslateVector().getX(), terrain->getTranslateVector().getY(), terrain->getTranslateVector().getZ());
	for (double i = -1.0*getCameraPos().z; i < 2.0*getCameraPos().z; i += terrain->getTranslateVector().getZ())//from 0 to  2 *RADIUS in z direction, since camera starts at z = RADIUS
	{
		transform_matrix = glm::translate(transform_matrix, translateVector);
		terrainTranslationMatrices.push_back(transform_matrix);
	}
}
void Scene::makeOriginalObjects() {
	FileReader* fileReader = new FileReader();

	fileReader->loadObj("features/obj__pinet1.obj", originalObjects[0]->verts, originalObjects[0]->uvs, originalObjects[0]->normals, originalObjects[0]->tangents, originalObjects[0]->bitangents);
	fileReader->loadObj("features/obj__pinet2.obj", originalObjects[1]->verts, originalObjects[1]->uvs, originalObjects[1]->normals, originalObjects[1]->tangents, originalObjects[1]->bitangents);
	fileReader->loadObj("features/obj__tree1.obj", originalObjects[2]->verts, originalObjects[2]->uvs, originalObjects[2]->normals, originalObjects[2]->tangents, originalObjects[2]->bitangents);
	fileReader->loadObj("features/obj__tree2.obj", originalObjects[3]->verts, originalObjects[3]->uvs, originalObjects[3]->normals, originalObjects[3]->tangents, originalObjects[3]->bitangents);
	fileReader->loadObj("features/obj__tree3.obj", originalObjects[4]->verts, originalObjects[4]->uvs, originalObjects[4]->normals, originalObjects[4]->tangents, originalObjects[4]->bitangents);
	fileReader->loadObj("features/obj__tree4.obj", originalObjects[5]->verts, originalObjects[5]->uvs, originalObjects[5]->normals, originalObjects[5]->tangents, originalObjects[5]->bitangents);
	fileReader->loadObj("features/obj__tree5.obj", originalObjects[6]->verts, originalObjects[6]->uvs, originalObjects[6]->normals, originalObjects[6]->tangents, originalObjects[6]->bitangents);
	fileReader->loadObj("features/obj__tree6.obj", originalObjects[7]->verts, originalObjects[7]->uvs, originalObjects[7]->normals, originalObjects[7]->tangents, originalObjects[7]->bitangents);
	fileReader->loadObj("features/obj__fern1.obj", originalObjects[8]->verts, originalObjects[8]->uvs, originalObjects[8]->normals, originalObjects[8]->tangents, originalObjects[8]->bitangents);
	fileReader->loadObj("features/obj__fern2.obj", originalObjects[9]->verts, originalObjects[9]->uvs, originalObjects[9]->normals, originalObjects[9]->tangents, originalObjects[9]->bitangents);
	fileReader->loadObj("features/obj__fern3.obj", originalObjects[10]->verts, originalObjects[10]->uvs, originalObjects[10]->normals, originalObjects[10]->tangents, originalObjects[10]->bitangents);
	fileReader->loadObj("features/obj__flow2.obj", originalObjects[11]->verts, originalObjects[11]->uvs, originalObjects[11]->normals, originalObjects[11]->tangents, originalObjects[11]->bitangents);
	fileReader->loadObj("features/obj__flow3.obj", originalObjects[12]->verts, originalObjects[12]->uvs, originalObjects[12]->normals, originalObjects[12]->tangents, originalObjects[12]->bitangents);
	fileReader->loadObj("features/obj__weed1.obj", originalObjects[13]->verts, originalObjects[13]->uvs, originalObjects[13]->normals, originalObjects[13]->tangents, originalObjects[13]->bitangents);
	fileReader->loadObj("features/obj__weed3.obj", originalObjects[14]->verts, originalObjects[14]->uvs, originalObjects[14]->normals, originalObjects[14]->tangents, originalObjects[14]->bitangents);
	fileReader->loadObj("features/obj__weed4.obj", originalObjects[15]->verts, originalObjects[15]->uvs, originalObjects[15]->normals, originalObjects[15]->tangents, originalObjects[15]->bitangents);
	fileReader->loadObj("features/obj__weed4a.obj", originalObjects[16]->verts, originalObjects[16]->uvs, originalObjects[16]->normals, originalObjects[16]->tangents, originalObjects[16]->bitangents);
	fileReader->loadObj("features/obj__weed5.obj", originalObjects[17]->verts, originalObjects[17]->uvs, originalObjects[17]->normals, originalObjects[17]->tangents, originalObjects[17]->bitangents);
	fileReader->loadObj("features/obj__weed6.obj", originalObjects[18]->verts, originalObjects[18]->uvs, originalObjects[18]->normals, originalObjects[18]->tangents, originalObjects[18]->bitangents);
	fileReader->loadObj("features/obj__shr1h.obj", originalObjects[19]->verts, originalObjects[19]->uvs, originalObjects[19]->normals, originalObjects[19]->tangents, originalObjects[19]->bitangents);
	fileReader->loadObj("features/obj__shr2.obj", originalObjects[20]->verts, originalObjects[20]->uvs, originalObjects[20]->normals, originalObjects[20]->tangents, originalObjects[20]->bitangents);
	fileReader->loadObj("features/obj__shr3.obj", originalObjects[21]->verts, originalObjects[21]->uvs, originalObjects[21]->normals, originalObjects[21]->tangents, originalObjects[21]->bitangents);
	fileReader->loadObj("features/obj__shr4.obj", originalObjects[22]->verts, originalObjects[22]->uvs, originalObjects[22]->normals, originalObjects[22]->tangents, originalObjects[22]->bitangents);
	fileReader->loadObj("features/obj__shr9.obj", originalObjects[23]->verts, originalObjects[23]->uvs, originalObjects[23]->normals, originalObjects[23]->tangents, originalObjects[23]->bitangents);
	fileReader->loadObj("features/obj__shr15.obj", originalObjects[24]->verts, originalObjects[24]->uvs, originalObjects[24]->normals, originalObjects[24]->tangents, originalObjects[24]->bitangents);
	fileReader->loadObj("features/obj__shr16.obj", originalObjects[25]->verts, originalObjects[25]->uvs, originalObjects[25]->normals, originalObjects[25]->tangents, originalObjects[25]->bitangents);
	fileReader->loadObj("features/obj__shr17h.obj", originalObjects[26]->verts, originalObjects[26]->uvs, originalObjects[26]->normals, originalObjects[26]->tangents, originalObjects[26]->bitangents);
	fileReader->loadObj("features/obj__grass.obj", originalObjects[27]->verts, originalObjects[27]->uvs, originalObjects[27]->normals, originalObjects[27]->tangents, originalObjects[27]->bitangents);

	fileReader->loadTGAFile("features/texture_soil_edited.tga", &terrainTGA);//texture made in GIMP
	fileReader->loadTGAFile("features/pinet1.tga", &pinet1TGA);
	fileReader->loadTGAFile("features/pinet2.tga",&pinet2TGA);
	fileReader->loadTGAFile("features/tree1.tga", &tree1TGA);
	fileReader->loadTGAFile("features/tree2.tga", &tree2TGA);
	fileReader->loadTGAFile("features/tree3.tga", &tree3TGA);
	fileReader->loadTGAFile("features/tree4.tga", &tree4TGA);
	fileReader->loadTGAFile("features/tree5.tga", &tree5TGA);
	fileReader->loadTGAFile("features/tree6.tga", &tree6TGA);
	fileReader->loadTGAFile("features/fern1.tga", &fern1TGA);
	fileReader->loadTGAFile("features/fern2.tga", &fern2TGA);
	fileReader->loadTGAFile("features/fern3.tga", &fern3TGA);
	fileReader->loadTGAFile("features/flow2.tga", &flow2TGA);
	fileReader->loadTGAFile("features/flow3.tga", &flow3TGA);
	fileReader->loadTGAFile("features/weed1.tga", &weed1TGA);
	fileReader->loadTGAFile("features/weed3.tga", &weed3TGA);
	fileReader->loadTGAFile("features/weed4.tga", &weed4TGA);
	fileReader->loadTGAFile("features/weed4a.tga", &weed4aTGA);
	fileReader->loadTGAFile("features/weed5.tga", &weed5TGA);
	fileReader->loadTGAFile("features/weed6.tga", &weed6TGA);
	fileReader->loadTGAFile("features/shr1h.tga", &shr1hTGA);
	fileReader->loadTGAFile("features/shr2.tga", &shr2TGA);
	fileReader->loadTGAFile("features/shr3.tga", &shr3TGA);
	fileReader->loadTGAFile("features/shr4.tga", &shr4TGA);
	fileReader->loadTGAFile("features/shr9.tga", &shr9TGA);
	fileReader->loadTGAFile("features/shr15.tga", &shr15TGA);
	fileReader->loadTGAFile("features/shr16.tga", &shr16TGA);
	fileReader->loadTGAFile("features/shr17h.tga", &shr17hTGA);
	fileReader->loadTGAFile("features/grass.tga", &grassTGA);

	fileReader->loadTGAFile("features/texture_soil_edited_normal.tga", &terrain_normalTGA);//texture made in GIMP
	fileReader->loadTGAFile("features/pinet1_normal.tga", &pinet1_normalTGA);
	fileReader->loadTGAFile("features/pinet2_normal.tga", &pinet2_normalTGA);
	fileReader->loadTGAFile("features/tree1_normal2.tga", &tree1_normalTGA);
	fileReader->loadTGAFile("features/tree2_normal.tga", &tree2_normalTGA);
	fileReader->loadTGAFile("features/tree3_normal.tga", &tree3_normalTGA);
	fileReader->loadTGAFile("features/tree4_normal.tga", &tree4_normalTGA);
	fileReader->loadTGAFile("features/tree5_normal.tga", &tree5_normalTGA);
	fileReader->loadTGAFile("features/tree6_normal.tga", &tree6_normalTGA);
	fileReader->loadTGAFile("features/fern1_normal.tga", &fern1_normalTGA);
	fileReader->loadTGAFile("features/fern2_normal.tga", &fern2_normalTGA);
	fileReader->loadTGAFile("features/fern3_normal.tga", &fern3_normalTGA);
	fileReader->loadTGAFile("features/flow2_normal.tga", &flow2_normalTGA);
	fileReader->loadTGAFile("features/flow3_normal2.tga", &flow3_normalTGA);
	fileReader->loadTGAFile("features/weed1_normal.tga", &weed1_normalTGA);
	fileReader->loadTGAFile("features/weed3_normal.tga", &weed3_normalTGA);
    fileReader->loadTGAFile("features/weed4_normal.tga", &weed4_normalTGA);
	fileReader->loadTGAFile("features/weed4a_normal.tga", &weed4a_normalTGA);
	fileReader->loadTGAFile("features/weed5_normal.tga", &weed5_normalTGA);
	fileReader->loadTGAFile("features/weed6_normal.tga", &weed6_normalTGA);
	fileReader->loadTGAFile("features/shr1h_normal.tga", &shr1h_normalTGA);
	fileReader->loadTGAFile("features/shr2_normal.tga", &shr2_normalTGA);
	fileReader->loadTGAFile("features/shr3_normal.tga", &shr3_normalTGA);
	fileReader->loadTGAFile("features/shr4_normal.tga", &shr4_normalTGA);
	fileReader->loadTGAFile("features/shr9_normal.tga", &shr9_normalTGA);
	fileReader->loadTGAFile("features/shr15_normal.tga", &shr15_normalTGA);
	fileReader->loadTGAFile("features/shr16_normal.tga", &shr16_normalTGA);
	fileReader->loadTGAFile("features/shr17h_normal.tga", &shr17h_normalTGA);
	fileReader->loadTGAFile("features/grass_normal.tga", &grass_normalTGA);

	
	originalObjects[0]->type = "pinet1";
	originalObjects[1]->type = "pinet2";
	originalObjects[2]->type = "tree1";
	originalObjects[3]->type = "tree2";
	originalObjects[4]->type = "tree3";
	originalObjects[5]->type = "tree4";
	originalObjects[6]->type = "tree5";
	originalObjects[7]->type = "tree6";
	originalObjects[8]->type = "fern1";
	originalObjects[9]->type = "fern2";
	originalObjects[10]->type = "fern3";
	originalObjects[11]->type = "flow2";
	originalObjects[12]->type = "flow3";
	originalObjects[13]->type = "weed1";
	originalObjects[14]->type = "weed3";
	originalObjects[15]->type = "weed4";
	originalObjects[16]->type = "weed4a";
	originalObjects[17]->type = "weed5";
	originalObjects[18]->type = "weed6";
	originalObjects[19]->type = "shr1h";
	originalObjects[20]->type = "shr2";
	originalObjects[21]->type = "shr3";
	originalObjects[22]->type = "shr4";
	originalObjects[23]->type = "shr9";
	originalObjects[24]->type = "shr15";
	originalObjects[25]->type = "shr16";
	originalObjects[26]->type = "shr17h";
	originalObjects[27]->type = "grass";
}
bool once = true;
void Scene::drawTerrain()
{
	
	/*
		Texture vertices are of the form x, y, z, u, v
	*/
	//switch shader programs
	glUseProgram(terrain_shader_program);
	glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(view_matrix));//
	glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, glm::value_ptr(proj_matrix));
	//glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model_matrix));
		
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*terrain->getTextureVertices().size() + sizeof(vec3)*terrain->getNormals().size(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*terrain->getTextureVertices().size(), (&terrain->getTextureVertices()[0]));
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*terrain->getTextureVertices().size(), sizeof(vec3)*terrain->getNormals().size(), (&terrain->getNormals()[0]));
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*terrain->getTextureVertices().size(), (&terrain->getTextureVertices()[0]), GL_STATIC_DRAW);
	
	// connect the xyz vertex attribute of the vertex shader
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);

	// connect the uv coords to the texture coordinate attribute of the vertex shader
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)terrain->getTextureVertices().size());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, terr_textureID);
	
	glUniform1i(glGetUniformLocation(terrain_shader_program, "tex"), 0);// the second argument i must match the glActiveTexture(GL_TEXTUREi)
	glUniform3f(glGetUniformLocation(terrain_shader_program, "light.position"), light.position.x, light.position.y, light.position.z);
	glUniform3f(glGetUniformLocation(terrain_shader_program, "light.intensities"), light.intensities.x, light.intensities.y, light.intensities.z);

	for (int i = 0; i < terrainTranslationMatrices.size(); i++)
	{

		glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(terrainTranslationMatrices[i]));//use translated model matrix
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawArrays(GL_QUADS, 0, terrain->getTextureVertices().size() / 5);
		glDisable(GL_BLEND);
		
	}
	
	glBindTexture(GL_TEXTURE_2D, 0);
	//glUseProgram(shader_program);
	//glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model_matrix));//reset to normal model matrix
	/**/
}

GLuint Scene::testTexture(char* path) {
	
	CImg<unsigned char> image(path);
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glEnable(GL_TEXTURE_2D);
	
	glGenerateMipmap(GL_TEXTURE_2D); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);//target, pname, param
	
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;

}
/*  Loading of texture works */
GLuint testObjectTextures(TGAFILE image)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		(GLsizei)image.imageWidth,
		(GLsizei)image.imageHeight,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image.imageData);

	glEnable(GL_TEXTURE_2D);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;

}

void Scene::drawObjects() {
	
	for (size_t i = 0; i < objectsToDraw.size(); ++i) {
		if (objectsToDraw[i] != NULL) {
		
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			//cout << "about to draw..." << endl;
			glBufferData(GL_ARRAY_BUFFER, objectsToDraw[i]->verts.size() * sizeof(vec3), &objectsToDraw[i]->verts[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
				);

			glDrawArrays(GL_LINES, 0, objectsToDraw[i]->verts.size());
		}
	}
}
//bool once = true;
bool sortByFirstVertex(const Object* lhs, const Object* rhs) // objects = vector<Object*>
{
	return lhs->verts[0].z < rhs->verts[0].z;
}

	void Scene::drawTexturizedObjects() {

		//switch shader programs
		glUseProgram(feature_shader_program);
		glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(view_matrix));//
		glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model_matrix));//
		glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, glm::value_ptr(proj_matrix));//

		for (size_t i = 0; i < objectsToDraw.size(); ++i) {
			if (objectsToDraw[i] != NULL) {


				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				//cout << "about to draw..." << endl;
				glBufferData(GL_ARRAY_BUFFER, (
					objectsToDraw[i]->verts.size()*sizeof(vec3) +
					objectsToDraw[i]->uvs.size()*sizeof(vec2) +
					objectsToDraw[i]->normals.size()*sizeof(vec3) +
					objectsToDraw[i]->tangents.size()*sizeof(vec3) +
					objectsToDraw[i]->bitangents.size()*sizeof(vec3)), NULL, GL_STATIC_DRAW);//allocate space for both chunks
				glBufferSubData(GL_ARRAY_BUFFER, 0, objectsToDraw[i]->verts.size()*sizeof(vec3), &objectsToDraw[i]->verts[0]);//chunk of vertices
				glBufferSubData(GL_ARRAY_BUFFER, objectsToDraw[i]->verts.size()*sizeof(vec3), objectsToDraw[i]->uvs.size()*sizeof(vec2), &objectsToDraw[i]->uvs[0]);//chunk of UV coordinates
				glBufferSubData(GL_ARRAY_BUFFER, objectsToDraw[i]->verts.size()*sizeof(vec3) + objectsToDraw[i]->uvs.size()*sizeof(vec2), objectsToDraw[i]->normals.size()*sizeof(vec3), &objectsToDraw[i]->normals[0]);//chunk of normals
				glBufferSubData(GL_ARRAY_BUFFER, objectsToDraw[i]->verts.size()*sizeof(vec3) + objectsToDraw[i]->uvs.size()*sizeof(vec2)+ objectsToDraw[i]->normals.size()*sizeof(vec3), objectsToDraw[i]->tangents.size()*sizeof(vec3), &objectsToDraw[i]->tangents[0]);//chunk tangents
				glBufferSubData(GL_ARRAY_BUFFER, objectsToDraw[i]->verts.size()*sizeof(vec3) + objectsToDraw[i]->uvs.size()*sizeof(vec2) + objectsToDraw[i]->normals.size()*sizeof(vec3) + objectsToDraw[i]->tangents.size()*sizeof(vec3),
					objectsToDraw[i]->bitangents.size()*sizeof(vec3), &objectsToDraw[i]->bitangents[0]);//chunk of bitangents
				// vertices*
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(
					0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
					3,                  // size
					GL_FLOAT,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(const GLvoid *)0            // array buffer offset
					);
				// uvs
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(
					1,								//to match layout in the shader
					2,								//size
					GL_FLOAT,						// type
					GL_FALSE,						// normalized?
					0,								// stride
					(const GLvoid *)(objectsToDraw[i]->verts.size() * sizeof(vec3))//offset
					);
				//normals
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(
					2,								//to match layout in the shader
					3,								//size
					GL_FLOAT,						// type
					GL_FALSE,						// normalized?
					0,								// stride
					(const GLvoid *)(objectsToDraw[i]->verts.size() * sizeof(vec3) + objectsToDraw[i]->uvs.size() * sizeof(vec2))//offset
					);
				// tangents
				glEnableVertexAttribArray(3);
				glVertexAttribPointer(
					3,								//to match layout in the shader
					3,								//size
					GL_FLOAT,						// type
					GL_FALSE,						// normalized?
					0,								// stride
					(const GLvoid *)(objectsToDraw[i]->verts.size() * sizeof(vec3) + objectsToDraw[i]->uvs.size() * sizeof(vec2) + objectsToDraw[i]->normals.size()*sizeof(vec3))//offset
					);
				//bitangents
				glEnableVertexAttribArray(4);
				glVertexAttribPointer(
					4,								//to match layout in the shader
					3,								//size
					GL_FLOAT,						// type
					GL_FALSE,						// normalized?
					0,								// stride
					(const GLvoid *)(objectsToDraw[i]->verts.size() * sizeof(vec3) + objectsToDraw[i]->uvs.size() * sizeof(vec2) + objectsToDraw[i]->normals.size()*sizeof(vec3)+ objectsToDraw[i]->tangents.size()*sizeof(vec3))//offset
					);
				glActiveTexture(GL_TEXTURE0);
				GLuint normalTexture = 0;
				if (objectsToDraw[i]->type.compare("pinet1") == 0)//bind pine tree texture
				{
					glBindTexture(GL_TEXTURE_2D, pinet1_textureID);
					normalTexture = pinet1_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("pinet2") == 0)//bind pine tree texture
				{
					glBindTexture(GL_TEXTURE_2D, pinet2_textureID);
					normalTexture = pinet2_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("tree1") == 0)//bind regular tree texture
				{
					glBindTexture(GL_TEXTURE_2D, tree1_textureID);
					normalTexture = tree1_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("tree2") == 0)//bind regular tree texture
				{
					glBindTexture(GL_TEXTURE_2D, tree2_textureID);
					normalTexture = tree2_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("tree3") == 0)//bind regular tree texture
				{
					glBindTexture(GL_TEXTURE_2D, tree3_textureID);
					normalTexture = tree3_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("tree4") == 0)//bind regular tree texture
				{
					glBindTexture(GL_TEXTURE_2D, tree4_textureID);
					normalTexture = tree4_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("tree5") == 0)//bind regular tree texture
				{
					glBindTexture(GL_TEXTURE_2D, tree5_textureID);
					normalTexture = tree5_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("tree6") == 0)//bind regular tree texture
				{
					glBindTexture(GL_TEXTURE_2D, tree6_textureID);
					normalTexture = tree6_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("fern1") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, fern1_textureID);
					normalTexture = fern1_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("fern2") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, fern2_textureID);
					normalTexture = fern2_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("fern3") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, fern3_textureID);
					normalTexture = fern3_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("flow2") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, flow2_textureID);
					normalTexture = flow2_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("flow3") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, flow3_textureID);
					normalTexture = flow3_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("weed1") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, weed1_textureID);
					normalTexture = weed1_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("weed3") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, weed3_textureID);
					normalTexture = weed3_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("weed4") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, weed4_textureID);
					normalTexture = weed4_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("weed4a") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, weed4a_textureID);
					normalTexture = weed4a_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("weed5") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, weed5_textureID);
					normalTexture = weed5_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("weed6") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, weed6_textureID);
					normalTexture = weed6_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("shr1h") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, shr1h_textureID);
					normalTexture = shr1h_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("shr2") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, shr2_textureID);
					normalTexture = shr2_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("shr3") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, shr3_textureID);
					normalTexture = shr3_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("shr4") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, shr4_textureID);
					normalTexture = shr4_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("shr9") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, shr9_textureID);
					normalTexture = shr9_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("shr15") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, shr15_textureID);
					normalTexture = shr15_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("shr16") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, shr16_textureID);
					normalTexture = shr16_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("shr17h") == 0)//bind fern texture
				{
					glBindTexture(GL_TEXTURE_2D, shr17h_textureID);
					normalTexture = shr17h_texture_normalID;
				}
				if (objectsToDraw[i]->type.compare("grass") == 0)//bind grass texture
				{
					glBindTexture(GL_TEXTURE_2D, grass_textureID);
					normalTexture = grass_texture_normalID;
				}

				glUniform1i(glGetUniformLocation(feature_shader_program, "tex"), 0);// the second argument i must match the glActiveTexture(GL_TEXTUREi)
				glUniform3f(glGetUniformLocation(feature_shader_program, "light.position"), light.position.x, light.position.y, light.position.z);
				glUniform3f(glGetUniformLocation(feature_shader_program, "light.intensities"), light.intensities.x, light.intensities.y, light.intensities.z);

				glActiveTexture(GL_TEXTURE1);
				glUniform1i(glGetUniformLocation(feature_shader_program, "normal_texture"), 1);// the second argument i must match the glActiveTexture(GL_TEXTUREi)
				glBindTexture(GL_TEXTURE_2D, normalTexture);

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glDrawArrays(GL_TRIANGLES, 0, objectsToDraw[i]->verts.size());
				glDisable(GL_BLEND);

				glBindTexture(GL_TEXTURE_2D, 0);
			}

	}

	}

void Scene::drawEverything() {
	
	//drawObjects();
	drawTerrain();
	//drawBoundaries();
	drawTexturizedObjects();
	
}

/*
void Scene::applyTexture() {
	glGenTextures(1, &TBO);
	glBindTexture(GL_TEXTURE_2D, TBO);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGB,
		(GLsizei)pinetTGA.imageWidth,
		(GLsizei)pinetTGA.imageHeight,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		pinetTGA.imageData);
	glBindTexture(GL_TEXTURE_2D, 0);
}*/

void Scene::setBoundaries() {
	
	GLfloat height = 300;

	//FAR
	boundaries[0] = RADIUS + boundOffset;
	boundaries[1] = 0;
	boundaries[2] = -boundOffset;
	boundaries[3] = -RADIUS - boundOffset;
	boundaries[4] = 0;
	boundaries[5] = -boundOffset;
	boundaries[6] = -RADIUS - boundOffset;
	boundaries[7] = height;
	boundaries[8] = -boundOffset;
	boundaries[9] = RADIUS + boundOffset;
	boundaries[10] = height;
	boundaries[11] = -boundOffset;
	boundaries[12] = RADIUS + boundOffset;
	boundaries[13] = 0;
	boundaries[14] = -boundOffset;
	boundaries[15] = -RADIUS - boundOffset;
	boundaries[16] = 0;
	boundaries[17] = -boundOffset;

	//LEFT
	boundaries[18] = -RADIUS - boundOffset;
	boundaries[19] = 0;
	boundaries[20] = 2 * RADIUS + boundOffset;
	boundaries[21] = -RADIUS - boundOffset;
	boundaries[22] = height;
	boundaries[23] = 2 * RADIUS + boundOffset;
	boundaries[24] = -RADIUS - boundOffset;
	boundaries[25] = height;
	boundaries[26] = -boundOffset;
	boundaries[27] = -RADIUS - boundOffset;
	boundaries[28] = 0;
	boundaries[29] = -boundOffset;
	boundaries[30] = -RADIUS - boundOffset;
	boundaries[31] = 0;
	boundaries[32] = 2 * RADIUS + boundOffset;

	//NEAR
	boundaries[33] = RADIUS + boundOffset;
	boundaries[34] = 0;
	boundaries[35] = 2 * RADIUS + boundOffset;
	boundaries[36] = RADIUS + boundOffset;
	boundaries[37] = height;
	boundaries[38] = 2 * RADIUS + boundOffset;
	boundaries[39] = -RADIUS + boundOffset;
	boundaries[40] = height;
	boundaries[41] = 2 * RADIUS + boundOffset;
	boundaries[42] = -RADIUS + boundOffset;
	boundaries[43] = 0;
	boundaries[44] = 2 * RADIUS + boundOffset;
	boundaries[45] = RADIUS + boundOffset;
	boundaries[46] = 0;
	boundaries[47] = 2 * RADIUS + boundOffset;

	//RIGHT
	boundaries[48] = RADIUS + boundOffset;
	boundaries[49] = 0;
	boundaries[50] = -boundOffset;
	boundaries[51] = RADIUS + boundOffset;
	boundaries[52] = height;
	boundaries[53] = -boundOffset;
	boundaries[54] = RADIUS + boundOffset;
	boundaries[55] = height;
	boundaries[56] = 2 * RADIUS + boundOffset;
	boundaries[57] = RADIUS + boundOffset;
	boundaries[58] = 0;
	boundaries[59] = 2 * RADIUS + boundOffset;
}

void Scene::drawBoundaries() {
	
	glGenBuffers(1, &VBO4);
	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boundaries), &boundaries[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_LINE_STRIP, 0, sizeof(boundaries) / 12);
}

void Scene::boundariesCollision() {

	glm::vec3 pos = gCamera.position();

	if (pos.x >= RADIUS + boundOffset) {
		
		gCamera.setPosition(glm::vec3(RADIUS + boundOffset - 1, lastFrameCamPos.y, lastFrameCamPos.z));
	}
	else if (pos.x <= -RADIUS - boundOffset) {

		gCamera.setPosition(glm::vec3(-RADIUS - boundOffset + 1, lastFrameCamPos.y, lastFrameCamPos.z));
	}
	else if (pos.z <= -boundOffset) {

		gCamera.setPosition(glm::vec3(lastFrameCamPos.x, lastFrameCamPos.y, -boundOffset + 1));
	}
	else if (pos.z >= 2 * RADIUS + boundOffset) {

		gCamera.setPosition(glm::vec3(lastFrameCamPos.x, lastFrameCamPos.y, 2 * RADIUS + boundOffset - 1));
	}
}

void Scene::constructEnvironment() {
	time = clock();
	vec3 playerPos = getCameraPos();
	generator->setRadius(RADIUS);
	for (size_t i = 0; i < originalObjects.size(); ++i) {
		generator->randomizeObject(*originalObjects[i], objectsInMemory);
	}
	
}
void Scene::test() {

}
void Scene::optimizeFromVBO() {
	threadDone = false;
	time = clock();
	vec3 playerPos = getCameraPos();
	for (size_t i = 0; i < objectsInMemory.size(); ++i) {
		Object* obj = objectsInMemory[i];
		if (obj != NULL) {
			int differenceX = (int)abs(objectsInMemory[i]->verts[0][0] - playerPos[0]);
			int differenceZ = (int)abs(objectsInMemory[i]->verts[0][2] - playerPos[2]);
			int dist = SEEDISTANCE * 1.7;
			if ((differenceZ < dist && differenceX < dist) && objectsInTransit[i] == NULL) {
				objectsInTransit[i] = objectsInMemory[i];
			}
			else if ((differenceZ > dist || differenceX > dist)) {
				objectsInTransit[i] = NULL;
			}
		}
	}
	threadDone = true;
}
void Scene::handleCollisionWithCamera() {
	vec3 cPos = gCamera.position();

	for (int i = 0; i < objectsToDraw.size(); ++i) {
		Object* obj = objectsToDraw[i];
		if (obj != NULL) {

			if (obj->type == "pinet2" || obj->type == "pinet1" || obj->type == "tree1" || obj->type == "tree6"
				|| obj->type == "tree2" || obj->type == "tree3" || obj->type == "tree4" || obj->type == "tree5") {
				//check the X axis
				if (abs(cPos.x - obj->position.x) < 0 + obj->boundingBox.x) {
					//check the Y axis
					if (abs(cPos.y - obj->position.y) < 0 + obj->boundingBox.y) {
						//check the Z axis
						if (abs(cPos.z - obj->position.z) < 0 + obj->boundingBox.z) {
							gCamera.setPosition(lastFrameCamPos);
							//COLLISION, stop camera from moving in the current direction
						//	cout << obj->type << endl;
						}
					}
				}
			}
		}
	}
}

void Scene::renewObjectsToDraw() {
	objectsToDraw = objectsInTransit;
}


int Scene::runEngine() { 
	light.position = gCamera.position();
	light.position.y -= 1.5;
	light.intensities = glm::vec3(1, 1, 1); //white
	makeOriginalObjects();
	cout << "building, please wait..." << endl;
	constructEnvironment();
	objectsToDraw = objectsInMemory;
	objectsInTransit = objectsInMemory;
	//makeMultipleObjects();
	//constructEnvironment();
	//objectsToDraw = objectsInMemory;

	initializeOpenGL();
	
	shader_program = loadShaders("COMP371_hw1.vs", "COMP371_hw1.fs");
	terrain_shader_program = loadShaders("terrain.vs", "terrain.fs");
	feature_shader_program = loadShaders("feature.vs", "feature.fs");
	//PlaySound(TEXT("night.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	generator->generatedOnce = true;
	oldPlayerPos = getCameraPos();
	vec3 pos = oldPlayerPos;
	generator->setPlayerPos(pos);
	//terr_textureID = testTexture("dirt1.bmp");
	terr_textureID = testObjectTextures(terrainTGA);
	pinet1_textureID = testObjectTextures(pinet1TGA);
	pinet2_textureID = testObjectTextures(pinet2TGA);
	tree1_textureID = testObjectTextures(tree1TGA);
	tree2_textureID = testObjectTextures(tree2TGA);
	tree3_textureID = testObjectTextures(tree3TGA);
	tree4_textureID = testObjectTextures(tree4TGA);
	tree5_textureID = testObjectTextures(tree5TGA);
	tree6_textureID = testObjectTextures(tree6TGA);
	fern1_textureID = testObjectTextures(fern1TGA);
	fern2_textureID = testObjectTextures(fern2TGA);
	fern3_textureID = testObjectTextures(fern3TGA);
	flow2_textureID = testObjectTextures(flow2TGA);
	flow3_textureID = testObjectTextures(flow3TGA);
	weed1_textureID = testObjectTextures(weed1TGA);
	weed3_textureID = testObjectTextures(weed3TGA);
	weed4_textureID = testObjectTextures(weed4TGA);
	weed4a_textureID = testObjectTextures(weed4aTGA);
	weed5_textureID = testObjectTextures(weed5TGA);
	weed6_textureID = testObjectTextures(weed6TGA);
	shr1h_textureID = testObjectTextures(shr1hTGA);
	shr2_textureID = testObjectTextures(shr2TGA);
	shr3_textureID = testObjectTextures(shr3TGA);
	shr4_textureID = testObjectTextures(shr4TGA);
	shr9_textureID = testObjectTextures(shr9TGA);
	shr15_textureID = testObjectTextures(shr15TGA);
	shr16_textureID = testObjectTextures(shr16TGA);
	shr17h_textureID = testObjectTextures(shr17hTGA);
	grass_textureID = testObjectTextures(grassTGA);

	pinet1_texture_normalID = testObjectTextures(pinet1_normalTGA);
	pinet2_texture_normalID = testObjectTextures(pinet2_normalTGA);
	tree1_texture_normalID = testObjectTextures(tree1_normalTGA);
	tree2_texture_normalID = testObjectTextures(tree2_normalTGA);
	tree3_texture_normalID = testObjectTextures(tree3_normalTGA);
	tree4_texture_normalID = testObjectTextures(tree4_normalTGA);
	tree5_texture_normalID = testObjectTextures(tree5_normalTGA);
	tree6_texture_normalID = testObjectTextures(tree6_normalTGA);
	fern1_texture_normalID = testObjectTextures(fern1_normalTGA);
	fern2_texture_normalID = testObjectTextures(fern2_normalTGA);
	fern3_texture_normalID = testObjectTextures(fern3_normalTGA);
	flow2_texture_normalID = testObjectTextures(flow2_normalTGA);
	flow3_texture_normalID = testObjectTextures(flow3_normalTGA);
	weed1_texture_normalID = testObjectTextures(weed1_normalTGA);
	weed3_texture_normalID = testObjectTextures(weed3_normalTGA);
	weed4_texture_normalID = testObjectTextures(weed4_normalTGA);
	weed4a_texture_normalID = testObjectTextures(weed4a_normalTGA);
	weed5_texture_normalID = testObjectTextures(weed5_normalTGA);
	weed6_texture_normalID = testObjectTextures(weed6_normalTGA);
	shr1h_texture_normalID = testObjectTextures(shr1h_normalTGA);
	shr2_texture_normalID = testObjectTextures(shr2_normalTGA);
	shr3_texture_normalID = testObjectTextures(shr3_normalTGA);
	shr4_texture_normalID = testObjectTextures(shr4_normalTGA);
	shr9_texture_normalID = testObjectTextures(shr9_normalTGA);
	shr15_texture_normalID = testObjectTextures(shr15_normalTGA);
	shr16_texture_normalID = testObjectTextures(shr16_normalTGA);
	shr17h_texture_normalID = testObjectTextures(shr17h_normalTGA);
	grass_texture_normalID = testObjectTextures(grass_normalTGA);
	setBoundaries();
	//applyTexture();//test
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	double lastTime = glfwGetTime();
	optimizeFromVBO();


	while (!glfwWindowShouldClose(window)) {
		/*
		generator->setPlayerPos(getCameraPos());
		generator->forward = gCamera.forward();
		if (threadDone == true) {
		//	cout << "attempting to construct" << endl;
			double timer = (clock() - time) / 1000.0f;
			if (timer > ENVIRONMENTREFRESHRATE && (oldPlayerPos.z != getCameraPos().z || oldPlayerPos.x != getCameraPos().x)) {
				cout << "constructing..." << endl;
				thread t(&Scene::constructEnvironment, this);
				t.detach();
			}
		}
		if (threadDone == true) {
			//cout << "about to draw" << endl;
			objectsToDraw = objectsInMemory;

		}
		*/
		if (threadDone == true) {
			//	cout << "attempting to construct" << endl;
			double timer = (clock() - time) / 1000.0f;
			if (timer > 1.5 ) {
			//	cout << "constructing..." << endl;
				thread t(&Scene::optimizeFromVBO, this);
				t.detach();
			}
		}
		
		if (threadDone == true) {
			double timer = (clock() - time) / 1000.0f;
			if (timer > 1.0f) {
				//	cout << "constructing..." << endl;
	//			thread t(&Scene::renewObjectsToDraw, this);
	//			t.detach();
			}
			

		}
		
		objectsToDraw = objectsInTransit;
		
		
		lastFrameCamPos = gCamera.position();
		double thisTime = glfwGetTime();
		Update((float)(thisTime - lastTime));
		lastTime = thisTime;
		//view_matrix = gCamera.matrix();//is projection()*view()
		view_matrix = gCamera.view();
		proj_matrix = gCamera.projection();

		/* Used for normal mapping */
		model_View_matrix = view_matrix * model_matrix;
		model_View_3x3_matrix = glm::mat3(model_View_matrix);
		MVP = proj_matrix * view_matrix * model_matrix;

		double timer = (clock() - time) / 1000.0f;
		if (timer > 0.1f) {
			//	cout << "constructing..." << endl;
		//	thread t(&Scene::handleCollisionWithCamera, this);
		//	t.detach();
		//	thread tt(&Scene::drawObjects, this);
		//	tt.detach();
		}
		handleCollisionWithCamera();
		boundariesCollision();
	//	proj_matrix = gCamera.projection();
	//	cout << gCamera.forward().z << endl;
	//	view_matrix[0][0] = -1;
		//view_matrix[1][1] = 0.97;
		//view_matrix[2][1] = 0.24;
		//view_matrix[3][1] = -0.24;
		//view_matrix[1][2] = 0.24;
		//view_matrix[2][2] = -0.97;
		//view_matrix[3][1] = -200;
		
	//	view_matrix[1][3] =0;
	//	view_matrix[2][3] = 1.1;
		//setUniform3v(uniformName, glm::value_ptr(v));
		//gProgram->setUniform("camera", gCamera.matrix());
		//time = clock() - 2000;
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		glEnable(GL_DEPTH_TEST);
	    glClearColor(0.0f, 0.0f, 0.0f, 0.0);
		//glClearColor(0.01f, 0.0f, 0.1f, 0.0);
		//glColor4f(0.0f, 0.0f, 1.0f,1.0f);
		glPointSize(point_size);
		glUseProgram(shader_program);


		//Pass the values of the three matrices to the shaders
		//glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, glm::value_ptr(proj_matrix));
		glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, &proj_matrix[0][0]);
		glUniformMatrix4fv(MVP_id, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(model_View_matrix_id, 1, GL_FALSE, &model_View_matrix[0][0]);
		glUniformMatrix3fv(model_View_3x3_matrix_id, 1, GL_FALSE, &model_View_3x3_matrix[0][0]);
		glBindVertexArray(VAO);
		drawEverything();


		glBindVertexArray(0);





		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
	}

	cleanUp();
	return 0;

}
vec3 Scene::getCameraPos() {
	/*
	mat4 ViewInv = inverse(view_matrix);
	GLdouble x = ViewInv[3][0];
	GLdouble y = ViewInv[3][1];
	GLdouble z = ViewInv[3][2];
	vec3 position(x,y,z);
	*/
	double x = gCamera.position()[0];
	double y = gCamera.position()[1];
	double z = gCamera.position()[2];
	vec3 position(x, y, z);
	
	//cout << position.z << endl;
	return position;
}

void windowResized(GLFWwindow* window, int width2, int height2) {

	widthB = width2;
	heightB = height2;
	glViewport(0, 0, width2, height2);
}

GLuint Scene::loadShaders(string vertex_shader_path, string fragment_shader_path) {
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_shader_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_shader_path.c_str());
		getchar();
		exit(-1);
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_shader_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_shader_path.c_str());
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_shader_path.c_str());
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);

 	//glBindAttribLocation(ProgramID, 0, "in_Position");//supposedly doesn't work on Radeon cards
	//glBindAttribLocation(ProgramID, 1, "vertex_Coordinate");
	//glBindAttribLocation(ProgramID, 2, "out_Coordinate");
	//appearing in the vertex shader.

	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	//The three variables below hold the id of each of the variables in the shader
	//If you read the vertex shader file you'll see that the same variable names are used.
	view_matrix_id = glGetUniformLocation(ProgramID, "view_matrix");
	model_matrix_id = glGetUniformLocation(ProgramID, "model_matrix");
	
	texture_location = glGetUniformLocation(ProgramID, "textureSampler");
	glUniform1i(texture_location, textureID);
	proj_matrix_id = glGetUniformLocation(ProgramID, "proj_matrix");

	return ProgramID;
}

bool Scene::initializeOpenGL() {
	/// Initialize GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return false;
	}

	/// Create a window of size 640x480 and with title "Lecture 2: First Triangle"
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	window = glfwCreateWindow(width, height, "Dark Forest", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return false;
	}

	int w, h;
	glfwGetWindowSize(window, &w, &h);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, 0, 0);
	glfwMakeContextCurrent(window);
	
	glfwSetScrollCallback(window, OnScroll);
	glfwSetWindowSizeCallback(window, windowResized);
	glfwSetKeyCallback(window, flashlightPressed);

	/// Initialize GLEW extension handler
	glewExperimental = GL_TRUE;	///Needed to get the latest version of OpenGL
	glewInit();

	/// Get the current OpenGL version
	const GLubyte* renderer = glGetString(GL_RENDERER); /// Get renderer string
	const GLubyte* version = glGetString(GL_VERSION); /// Version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	/// Enable the depth test i.e. draw a pixel if it's closer to the viewer
	
	glDepthFunc(GL_LESS);	/// The type of testing i.e. a smaller value as "closer"

	return true;
}

bool Scene::cleanUp() {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	//Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO);

	// Close GL context and any other GLFW resources
	glfwTerminate();

	return true;
}
