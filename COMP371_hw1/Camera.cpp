#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}
/*
vec3 Camera::getCameraPos() {
	int viewport[4];
	// get matrixs and viewport:
	glGetDoublev(GL_MODELVIEW_MATRIX, matModelView);
	glGetDoublev(GL_PROJECTION_MATRIX, matProjection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluUnProject((viewport[2] - viewport[0]) / 2, (viewport[3] - viewport[1]) / 2,
		0.0, matModelView, matProjection, viewport,
		&camera_pos[0], &camera_pos[1], &camera_pos[2]);
}*/
Camera::~Camera()
{
}
