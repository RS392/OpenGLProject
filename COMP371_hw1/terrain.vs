

#version 130

uniform mat4 view_matrix, model_matrix;

in  vec3 in_Position;		//vertex position
out vec3 out_Color;

void main () {
mat4 CTM = view_matrix;
gl_Position = CTM * vec4 (in_Position, 1.0);
	if(in_Position.y < -.1)
	{
		out_Color = vec3 (0.0,0.35,0.99);
	}
	else
	{
		out_Color = vec3 (0.3333333,0.419608,0.184314);
	}

}