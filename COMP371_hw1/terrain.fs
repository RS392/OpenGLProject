
#version 150
uniform sampler2D tex; //this is the texture
in vec2 fragTexCoord; //this is the texture coord
out vec4 finalColor; //this is the output color of the pixel

void main() {
     finalColor = texture(tex, fragTexCoord);
	//finalColor = vec4(fragTexCoord, 0.0,0.0);
}