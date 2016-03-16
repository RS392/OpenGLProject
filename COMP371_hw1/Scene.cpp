#include "stdafx.h"
#include "Scene.h"

using namespace std;
using namespace glm;
#define M_PI        3.14159265358979323846264338327950288   /* pi */
#define DEG_TO_RAD	M_PI/180.0f
#define SEEDISTANCE 1000

GLFWwindow* window = 0x00;

GLuint shader_program = 0;
GLuint terrain_shader_program = 0;
bool terrainView = true;
GLuint view_matrix_id = 0;
GLuint model_matrix_id = 0;
GLuint proj_matrix_id = 0;

int height = 500, heightB = 600;
int width = 800, widthB = 800;

///Transformations
glm::mat4 proj_matrix;
glm::mat4 view_matrix;
glm::mat4 model_matrix;


GLuint VBO, VAO, EBO, TBO, VBO2;

GLfloat point_size = 3.0f;

//vector<vec3> treeVertices(1);


TGAFILE treeTGA;

bool clicked;
double oldX = 0;
double oldY = 0;
GLfloat displacementz = 0.0f;
GLfloat displacementx = 0.0f;

bool threadDone;
tdogl::Camera gCamera;
double gScrollY = 0.0;


// update the scene based on the time elapsed since last update
void Update(float secondsElapsed) {

	//move position of camera based on WASD keys, and XZ keys for up and down
	const float moveSpeed = 220.0; //units per second
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
	/*
	if (moving) {
		PlaySound(TEXT("footsteps2.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	} else 
		PlaySound(NULL, 0, 0);
	*/

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
	
	gScrollY = 0;
}
// records how far the y axis has been scrolled
void OnScroll(GLFWwindow* window, double deltaX, double deltaY) {
	gScrollY += deltaY;
}
Scene::Scene()
{
	generator = new RandomAttributeGenerator();
	numberOfOriginalObjects = 4;
	for (int i = 0; i < numberOfOriginalObjects; ++i) {
		Object* obj = new Object(); // empty place holder to allocate memory
		
		originalObjects.push_back(obj);
	}
	
	
	time = clock();
	glm::vec3 cameraPosition(0.0, 50, RADIUS);
//	gCamera.setNearAndFarPlanes(0.1f,5000.0f);
	gCamera.setNearAndFarPlanes(1.0f, SEEDISTANCE);

	gCamera.setPosition(cameraPosition);
	terrain = new Terrain(cameraPosition);//for testing
	//gCamera.setPosition(glm::vec3(0,0,0));//near terrain
	//gCamera.setViewportAspectRatio(width / height);
	

	//PlaySound(TEXT("forestSound.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);// terrain

}

Scene::~Scene()
{
}

void Scene::makeOriginalObjects() {
	FileReader* fileReader = new FileReader();
	
	fileReader->loadObj("obj__pinet2.obj", originalObjects[0]->verts, treeUvs, treeNormals);
	fileReader->loadTGAFile("pinet2.tga",&treeTGA);
	fileReader->loadObj("obj__tree1.obj", originalObjects[1]->verts, treeUvs, treeNormals);
	fileReader->loadObj("obj__fern1.obj", originalObjects[2]->verts, treeUvs, treeNormals);
	fileReader->loadObj("obj__grass.obj", originalObjects[3]->verts, treeUvs, treeNormals);
	originalObjects[0]->verts.erase(originalObjects[0]->verts.begin());
	originalObjects[1]->verts.erase(originalObjects[1]->verts.begin());
	originalObjects[2]->verts.erase(originalObjects[2]->verts.begin());
	originalObjects[3]->verts.erase(originalObjects[3]->verts.begin());
	originalObjects[0]->type = "pinet2";
	originalObjects[1]->type = "tree1";
	originalObjects[2]->type = "fern1";
	originalObjects[3]->type = "grass";
}
void Scene::drawTerrain()
{
	glUseProgram(terrain_shader_program);
	glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model_matrix));
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*terrain->getVertices().size(), (&terrain->getVertices()[0]), GL_STATIC_DRAW);
	//cout << terrain->getVertices().size() << endl;
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
		
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*terrain->getWireFrameIndices().size(), (&terrain->getWireFrameIndices()[0]), GL_STATIC_DRAW);
	glDrawElements(GL_LINES, terrain->getWireFrameIndices().size(), GL_UNSIGNED_INT, nullptr);//Terrain test
	//glDrawArrays(GL_POINTS, 0, (terrain->getVertices().size()/3));
	//glDrawArrays(GL_POINTS, 0, (terrain->getVertices().size()));
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)*terrain->getIndicesForTriangles().size(), (&terrain->getIndicesForTriangles()[0]), GL_STATIC_DRAW);
	//glDrawElements(GL_TRIANGLES, terrain->getIndicesForTriangles().size(), GL_UNSIGNED_INT, nullptr);//Terrain test
	//cout << terrain->getVertices().size() << " size versus " << terrain->getIndicesForTriangles().size() << endl;
	glUseProgram(shader_program);
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
void Scene::drawEverything() {
	drawObjects();
	drawTerrain();

}
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
		(GLsizei)treeTGA.imageWidth,
		(GLsizei)treeTGA.imageHeight,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		treeTGA.imageData);
	glBindTexture(GL_TEXTURE_2D, 0);

}
// id: 
void Scene::constructEnvironment() {
	threadDone = false;
	time = clock();
	vec3 playerPos = getCameraPos();
	char typeOfObject; // 'p' for pinet, 'f' for fern, 't' for tree. // This is important to know because sizes
					   // and other things will of course depend on the object type
	generator->setRadius(RADIUS);
	for (size_t i = 0; i < originalObjects.size(); ++i) {
		generator->randomizeObject(*originalObjects[i], objectsInMemory);
	}
	//destroy objects out of range
	/*
	for (size_t i = 0; i < objectsInMemory.size(); ++i) {
		int differenceX = (int) abs(abs(objectsInMemory[i].verts[0][0]) - abs(playerPos[0])); // 
		int differenceZ = (int) abs(abs(objectsInMemory[i].verts[0][2]) - abs(playerPos[2]));

		if (differenceZ > RADIUS * 1.1 ) {
			
			objectsInMemory.erase(objectsInMemory.begin() + i);
		}

	}*/
	
	//oldPlayerPos = getCameraPos();
	//generator->setOldPlayerPos(oldPlayerPos);
	threadDone = true;
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
			int dist = SEEDISTANCE * 1.2;
			if ((differenceZ < dist || differenceX < dist) && objectsToDraw[i] == NULL) {
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
			if (obj->type == "pinet2") {
				//check the X axis
				if (abs(cPos.x - obj->position.x) < 0 + obj->boundingBox.x) {
					//check the Y axis
					if (abs(cPos.y - obj->position.y) < 0 + obj->boundingBox.y) {
						//check the Z axis
						if (abs(cPos.z - obj->position.z) < 0 + obj->boundingBox.z) {
							gCamera.setPosition(lastFrameCamPos);
							cout << "omfg just hit a tree" << endl;
							//COLLISION, stop camera from moving in the current direction
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
	PlaySound(TEXT("forestSound.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	generator->generatedOnce = true;
	oldPlayerPos = getCameraPos();
	vec3 pos = oldPlayerPos;
	generator->setPlayerPos(pos);
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
		view_matrix = gCamera.matrix();
		double timer = (clock() - time) / 1000.0f;
		if (timer > 0.1f) {
			//	cout << "constructing..." << endl;
		//	thread t(&Scene::handleCollisionWithCamera, this);
		//	t.detach();
		//	thread tt(&Scene::drawObjects, this);
		//	tt.detach();
		}
		handleCollisionWithCamera();
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
		glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
		//glColor4f(0.1f,0.2f,0.2f,0.5f);
		glPointSize(point_size);
		glUseProgram(shader_program);


		//Pass the values of the three matrices to the shaders
		//glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, glm::value_ptr(proj_matrix));
		glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model_matrix));

		glBindVertexArray(VAO);
		drawEverything();


		glBindVertexArray(0);;





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

//	glBindAttribLocation(ProgramID, 0, "in_Position");

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
	//proj_matrix_id = glGetUniformLocation(ProgramID, "proj_matrix");

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

	/// Initialize GLEW extension handler
	glewExperimental = GL_TRUE;	///Needed to get the latest version of OpenGL
	glewInit();

	/// Get the current OpenGL version
	const GLubyte* renderer = glGetString(GL_RENDERER); /// Get renderer string
	const GLubyte* version = glGetString(GL_VERSION); /// Version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	/// Enable the depth test i.e. draw a pixel if it's closer to the viewer
	glEnable(GL_DEPTH_TEST); /// Enable depth-testing
	glDepthFunc(GL_LESS);	/// The type of testing i.e. a smaller value as "closer"

	return true;
}

bool Scene::cleanUp() {
	glDisableVertexAttribArray(0);
	//Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO);

	// Close GL context and any other GLFW resources
	glfwTerminate();

	return true;
}
