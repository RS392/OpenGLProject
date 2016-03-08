#include "stdafx.h"
#include "Camera.h"


Camera::Camera(const glm::mat4 &view_matrix)
{
	this->view_matrix = view_matrix;
}

Camera::~Camera()
{
}
