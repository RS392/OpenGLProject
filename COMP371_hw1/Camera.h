#pragma once
class Camera
{
private:
	glm::mat4 view_matrix;

public:
	Camera(const glm::mat4 &view_matrix);
	~Camera();

	void keyPressed(GLFWwindow *_window, int key, int scancode, int action, int mods);
};

