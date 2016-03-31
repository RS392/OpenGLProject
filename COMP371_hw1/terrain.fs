
#version 150

uniform mat4 model_matrix, view_matrix, proj_matrix;
uniform sampler2D tex; //this is the texture
in vec2 fragTexCoord; //this is the texture coord
in vec3 fragNormal;
in vec3 fragVert;

out vec4 finalColor; //this is the output color of the pixel


uniform struct Light {
   vec3 position;
   vec3 intensities; //a.k.a the color of the light
} light;

void main() {
	mat4 model = proj_matrix * view_matrix * model_matrix;
	//calculate normal in world coordinates
	mat3 normalMatrix = transpose(inverse(mat3(model)));
    //mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * fragNormal);
    
    //calculate the location of this fragment (pixel) in world coordinates
    vec3 fragPosition = vec3(model * vec4(fragVert, 1));
    
    //calculate the vector from this pixels surface to the light source
    vec3 surfaceToLight = light.position - fragPosition;
	
    //calculate the cosine of the angle of incidence
    float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
    brightness = clamp(brightness, 0, 1);

    //calculate final color of the pixel, based on:
    // 1. The angle of incidence: brightness
    // 2. The color/intensities of the light: light.intensities
    // 3. The texture and texture coord: texture(tex, fragTexCoord)
    vec4 surfaceColor = texture(tex, fragTexCoord);
	mat4 inverseView = inverse(view_matrix);
	vec4 camera = inverseView[3];
	
	finalColor = vec4(brightness * light.intensities * surfaceColor.rgb, surfaceColor.a);
	
//	if (normal.x == 0)
//		finalColor = texture(tex, fragTexCoord);
//	else
		
   // finalColor = texture(tex, fragTexCoord);
	 //finalColor.y = finalColor.y - n;
	//finalColor = vec4(fragTexCoord, 0.0,0.0);
}