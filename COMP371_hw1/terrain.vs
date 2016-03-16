
#version 330

uniform mat4 view_matrix, model_matrix;

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec2 vertTexCoord;
out vec2 fragTexCoord;

void main() {

	mat4 CTM = view_matrix;
    // Pass the tex coord straight through to the fragment shader
    fragTexCoord = vertTexCoord;
    
    gl_Position = CTM * vec4(in_Position, 1);
}