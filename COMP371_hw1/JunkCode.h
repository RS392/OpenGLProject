#pragma once
/*
PLEASE DO NOT DELETE CODE IN HERE UNTIL THE END OF THE PROJECT.

Add here the code that you just deleted from the project in case you are not sure whether you still need it or not.
*/


class JunkCode
{
public:
	JunkCode();
	~JunkCode();
};

/*
goes in vs
#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){

// Output position of the vertex, in clip space : MVP * position
gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

// UV of the vertex. No special space for this one.
UV = vertexUV;
}







//goes in fs
#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D myTextureSampler;

void main(){

color = texture( myTextureSampler, UV ).rgb;
}


*/