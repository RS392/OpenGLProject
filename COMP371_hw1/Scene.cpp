#include "stdafx.h"
#include "Scene.h"

using namespace std;
using namespace glm;
#define M_PI        3.14159265358979323846264338327950288   /* pi */
#define DEG_TO_RAD	M_PI/180.0f

GLFWwindow* window = 0x00;

GLuint shader_program = 0;
bool terrainView = true;
GLuint view_matrix_id = 0;
GLuint model_matrix_id = 0;
GLuint proj_matrix_id = 0;

int height = 500, heightB = 600;
int width = 800, widthB = 800;

///Transformations
glm::mat4 proj_matrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.01f, 1000.0f);;
glm::mat4 view_matrix = glm::lookAt(glm::vec3(0.0f, 50.0f, -200.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 model_matrix;


GLuint VBO, VAO, EBO, TBO;

GLfloat point_size = 3.0f;

//vector<vec3> treeVertices(1);


TGAFILE treeTGA;

bool clicked;
double oldX = 0;
double oldY = 0;
GLfloat displacementz = 0.0f;
GLfloat displacementx = 0.0f;

Scene::Scene()
{
	generator = new RandomAttributeGenerator();
	numberOfOriginalObjects = 3;
	for (int i = 0; i < numberOfOriginalObjects; ++i) {
		object obj(1); // empty place holder to allocate memory
		originalObjects.push_back(obj);
	}
	object obj(1);
	objectsToDraw.push_back(obj);
	terrain = new Terrain();//for testing
}

Scene::~Scene()
{
}

void Scene::makeMultipleObjects() {
	char typeOfObject; // 'p' for pinet, 'f' for fern, 't' for tree. // This is important to know because sizes
	// and other things will of course depend on the object type
	
	for (size_t i = 0; i < originalObjects.size(); ++i) {
		if (i == 0) {
			typeOfObject = 'p';
		}
		else if (i == 1) {
			typeOfObject = 't';
		}
		else if (i == 2) {
			typeOfObject = 'f';
		}
		generator->randomizeObject(originalObjects[i], typeOfObject, objectsInMemory);
	}
}
void Scene::makeOriginalObjects() {
	FileReader* fileReader = new FileReader();
	
	fileReader->loadObj("obj__pinet2.obj", originalObjects[0], treeUvs, treeNormals);
	fileReader->loadTGAFile("pinet2.tga",&treeTGA);
	fileReader->loadObj("obj__tree1.obj", originalObjects[1], treeUvs, treeNormals);
	fileReader->loadObj("obj__fern1.obj", originalObjects[2], treeUvs, treeNormals);
	//fileReader->loadObj("obj__flow2.obj", originalObjects[3], treeUvs, treeNormals);
	
}
void Scene::drawTerrain()
{
	//change the view/projection matrices to look down more
	if (terrainView)
	{
		glm::vec3 eye(0.0f, 1.0f, -2.0f);
		view_matrix = glm::lookAt(eye, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		proj_matrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.01f, 100.0f);
		terrainView = false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*terrain->getVertices().size(), (&terrain->getVertices()[0]), GL_STATIC_DRAW);

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
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)*terrain->getWireFrameIndices().size(), (&terrain->getWireFrameIndices()[0]), GL_STATIC_DRAW);
	//glDrawElements(GL_LINES, terrain->getWireFrameIndices().size(), GL_UNSIGNED_INT, nullptr);//Terrain test

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)*terrain->getIndicesForTriangles().size(), (&terrain->getIndicesForTriangles()[0]), GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, terrain->getIndicesForTriangles().size(), GL_UNSIGNED_INT, nullptr);//Terrain test


}

void Scene::drawObjects() {
	
	for (size_t i = 0; i < objectsToDraw.size(); ++i) {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, objectsToDraw[i].size() * sizeof(vec3), &objectsToDraw[i][0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);
		glDrawArrays(GL_TRIANGLES, 0, objectsToDraw[i].size());
	}
}
void Scene::drawEverything() {
	drawObjects();
	//drawTerrain();

}
void Scene::applyTexture() {
	glGenTextures(1, &TBO);
	glBindTexture(GL_TEXTURE_2D, TBO);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	
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

void rotateCamera() {

	double xpos = oldX;
	double ypos = oldY;
	glfwGetCursorPos(window, &xpos, &ypos);

	if (xpos > oldX && xpos < widthB) {
		
		view_matrix = glm::lookAt(glm::vec3(0.0f + displacementx, 50.0f, -200.0f + displacementz), glm::vec3(cos((xpos - oldX) / 100.0f), 0.0f, sin((xpos - oldX) / 100.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
		oldX = xpos = widthB / 2;
	}
	else if (xpos < oldX && xpos > 0) {

		view_matrix = glm::rotate(view_matrix, -0.0001f, glm::vec3(0, 1, 0));
		oldX = ypos = 0;
	}
}

void Scene::constructEnvironment() {
	int radius = 200;
	vec3 playerPos = getCameraPos();
	bool inRange = false;
	// add objects from objects in range to objectsToDraw
	for (int i = 0; i < objectsInMemory.size(); ++i) {
		int differenceX = abs(objectsInMemory[i][0][0]) - abs(playerPos[0]); // 
		int differenceZ = abs(objectsInMemory[i][0][2]) - abs(playerPos[2]);
		object ob = objectsInMemory[i];
		bool isAlreadyDrawn = find(objectsToDraw.begin(), objectsToDraw.end(), ob) != objectsToDraw.end();
		if (differenceX < radius && differenceZ < radius && !isAlreadyDrawn) {
			objectsToDraw.push_back(objectsInMemory[i]);
		}

	}
	
	//destroy objects out of range
	/*
	for (int i = 0; i < objectsToDraw.size(); ++i) {
		int differenceX = abs(objectsToDraw[i][0][0]) - abs(playerPos[0]); // 
		int differenceZ = abs(objectsToDraw[i][0][2]) - abs(playerPos[2]);
		bool isAlreadyDrawn = std::find(objectsToDraw.begin(), objectsToDraw.end(), objects[i]) != objects.end();
		if (differenceX > radius && differenceZ > radius && isAlreadyDrawn) {
			objectsToDraw.erase(objectsToDraw.begin() + i);
		}
	}
	*/
}

int Scene::runEngine() { 
	

	makeOriginalObjects();
	makeMultipleObjects();
	
	initializeOpenGL();
	shader_program = loadShaders("COMP371_hw1.vs", "COMP371_hw1.fs");


	glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	
	int timer = 0;
	while (!glfwWindowShouldClose(window)) {
		++timer;
		if (timer > 10000) {
			cout << "constructing" << endl;
			constructEnvironment();
			timer = 0;
		}
		//rotateCamera();
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.2f, 0.2f, 0.5f);
		//glColor4f(0.1f,0.2f,0.2f,0.5f);
		glPointSize(point_size);
		glUseProgram(shader_program);


		//Pass the values of the three matrices to the shaders
		glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, glm::value_ptr(proj_matrix));
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
	
	mat4 ViewInv = inverse(view_matrix);
	GLdouble x = ViewInv[3][0];
	GLdouble y = ViewInv[3][1];
	GLdouble z = ViewInv[3][2];
	vec3 position(x,y,z);
	return position;
}
void keyPressed(GLFWwindow *_window, int key, int scancode, int action, int mods) {

	switch (key) {

	case GLFW_KEY_W: view_matrix = glm::translate(view_matrix, glm::vec3(0.0f, 0.0f, -10.0f));
						displacementz += 10.0f;
		break;
	case GLFW_KEY_A: view_matrix = glm::translate(view_matrix, glm::vec3(-10.0f, 0.0f, 0.0f));
						displacementx += 5.0f;
		break;
	case GLFW_KEY_S: view_matrix = glm::translate(view_matrix, glm::vec3(0.0f, 0.0f, 10.0f));
						displacementz -= 10.0f;
		break;
	case GLFW_KEY_D: view_matrix = glm::translate(view_matrix, glm::vec3(10.0f, 0.0f, 0.0f));
						displacementx -= 5.0f;
		break;
	//case GLFW_KEY_B: cout << getCameraPos()[0] << endl;

		break;

	default: break;
	}
}

void buttonClicked(GLFWwindow* window, int button, int action, int mods) {

	//Zoom-in, zoom-out
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		clicked = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		clicked = false;
	}
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

	glBindAttribLocation(ProgramID, 0, "in_Position");

	//appearing in the vertex shader.
	glBindAttribLocation(ProgramID, 1, "in_Color");

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
	glfwMakeContextCurrent(window);

	glfwSetMouseButtonCallback(window, buttonClicked);

	glfwSetKeyCallback(window, keyPressed);

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
	glDeleteBuffers(1, &EBO);

	// Close GL context and any other GLFW resources
	glfwTerminate();

	return true;
}
