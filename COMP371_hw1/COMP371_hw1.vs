

#version 130

uniform mat4 view_matrix, model_matrix;

in  vec3 in_Position;		//vertex position
out vec3 out_Color;

void main () {
mat4 CTM = view_matrix;
gl_Position = CTM * vec4 (in_Position, 1.0);

//gl_Position = vec4(0,200,5000,1);
	out_color = vec3(1,1,1);

}