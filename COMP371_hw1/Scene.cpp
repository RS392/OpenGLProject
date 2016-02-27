#include "stdafx.h"
#include "Scene.h"

using namespace std;
using namespace glm;
#define M_PI        3.14159265358979323846264338327950288   /* pi */
#define DEG_TO_RAD	M_PI/180.0f

GLFWwindow* window = 0x00;

GLuint shader_program = 0;

GLuint view_matrix_id = 0;
GLuint model_matrix_id = 0;
GLuint proj_matrix_id = 0;

///Transformations
glm::mat4 proj_matrix;
glm::mat4 view_matrix;
glm::mat4 model_matrix;

GLfloat test[] = { 0.5f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f };

GLuint VBO, VAO, EBO, TBO;

GLfloat point_size = 3.0f;

int height = 600;
int width = 800;
vector<vec3> treeVertices(1);
vector<vec3> treeNormals(1);
vector<vec2> treeUvs(1);
TGAFILE treeTGA;

bool clicked;
double oldY = 0;

Scene::Scene()
{

}
void tempZoom() {
	GLint viewport[4]; //var to hold the viewport info
	GLdouble modelview[16]; //var to hold the modelview info
	GLdouble projection[16]; //var to hold the projection matrix info
	GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
	GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates
	GLdouble camera_pos[3];

	//int viewport[4];
	// get matrixs and viewport:
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluUnProject((viewport[2] - viewport[0]) / 2, (viewport[3] - viewport[1]) / 2,
		0.0, modelview, projection, viewport,
		&camera_pos[0], &camera_pos[1], &camera_pos[2]);

	//cout << "x: " << camera_pos[0] << endl;
	//Zoom-in, zoom-out
	double currentX = 0;
	double currentY = oldY;
	glfwGetCursorPos(window, &currentX, &currentY);

	if (clicked && (currentY != oldY) && currentY > 0 && currentY < height) {

		glm::vec3 eye(0.0f, 0.0f, currentY / 0.01f);
		view_matrix = glm::lookAt(eye, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		proj_matrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.01f, 1000.0f);
		oldY = currentY;
	}
}

Scene::~Scene()
{
}
void Scene::makeSingleTree() {
	FileReader* fileReader = new FileReader();
	fileReader->loadObj("obj__pinet2.obj", treeVertices, treeUvs, treeNormals);
	fileReader->loadTGAFile("pinet2.tga",&treeTGA);
	cout << treeTGA.imageHeight << endl;
}
void Scene::drawSingleTree() {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, treeVertices.size() * sizeof(vec3), &treeVertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
	glDrawArrays(GL_LINES, 0, treeVertices.size());
}
void Scene::drawEverything() {
	drawSingleTree();
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

int Scene::runEngine() { 
	

	makeSingleTree();
	
	initializeOpenGL();
	shader_program = loadShaders("COMP371_hw1.vs", "COMP371_hw1.fs");


	glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	
	
	while (!glfwWindowShouldClose(window)) {
		
		tempZoom();
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





void keyPressed(GLFWwindow *_window, int key, int scancode, int action, int mods) {

	switch (key) {

	case GLFW_KEY_W: 
		break;
	case GLFW_KEY_A: view_matrix = glm::translate(view_matrix, glm::vec3(0.05f, 0.0f, 0.0f));
		break;
	case GLFW_KEY_S: 
		break;
	case GLFW_KEY_D: view_matrix = glm::translate(view_matrix, glm::vec3(-0.05f, 0.0f, 0.0f));
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