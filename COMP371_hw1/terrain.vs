

#version 130

uniform mat4 view_matrix, model_matrix;

in  vec3 in_Position;		//vertex position
in vec2 vertex_Texture_Coordinate;
out vec2 out_Texture_Coordinate;

void main () {
	mat4 CTM = view_matrix;
	gl_Position = CTM * vec4 (in_Position, 1.0);
	out_Texture_Coordinate = vertex_Texture_Coordinate;
	

}