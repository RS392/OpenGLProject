
#version 130

uniform sampler2D textureSampler;
in vec2 out_Texture_Coordinate;
out vec4 frag_colour;	//final output color used to render the point

void main () {
	frag_colour = texture(textureSampler, out_Texture_Coordinate);// .rgb
}