
#version 150

uniform mat4 model_matrix, view_matrix, proj_matrix,model_View_matrix,model_View_3x3_matrix,MVP;

uniform sampler2D tex; //this is the texture
uniform sampler2D normal_texture;
in vec2 fragTexCoord; //this is the texture coord
in vec3 fragNormal;
in vec3 fragVert;
in mat3 TBN;

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
    mat4 inverseView = inverse(view_matrix);
	vec4 camera = inverseView[3];
	vec3 cameraTBN = TBN*vec3(camera.x, camera.y, camera.z);
	vec3 point =  TBN*fragVert;
    vec3 cameraToPoint = -1.0*vec3(fragVert.x - camera.x, fragVert.y - camera.y, fragVert.z - camera.z);
	//vec3 cameraToPoint = (-1.0*vec3(point.x - cameraTBN.x, point.y - cameraTBN.y, point.z - cameraTBN.z));//in tangent space
	vec3 normal = normalize(normalMatrix * fragNormal);
	//vec3 normal = texture(normal_texture, fragTexCoord).rgb*2.0 - 1.0;
	if(dot(normalize(cameraToPoint), fragNormal) > 0)
	{
		normal *= -1.0;
	}
	float q = length(cameraToPoint);
	float a = 1.0;//0.6
	float b = 0.5;
	float c = 0.1;
	float attenuation = 1.0/(a + b*q+c*q*q);
    //calculate the location of this fragment (pixel) in world coordinates
    vec3 fragPosition = vec3(model * vec4(fragVert, 1));
    
    //calculate the vector from this pixels surface to the light source
   //vec3 surfaceToLight = (light.position - point);
    vec3 surfaceToLight = light.position - fragPosition;
	
    //calculate the cosine of the angle of incidence
    float brightness = dot(normal, surfaceToLight) * attenuation;// / (length(surfaceToLight) * length(normal));
    brightness = clamp(brightness, 0, 1) ;

    //calculate final color of the pixel, based on:
    // 1. The angle of incidence: brightness
    // 2. The color/intensities of the light: light.intensities
    // 3. The texture and texture coord: texture(tex, fragTexCoord)
    vec4 surfaceColor = texture(tex, fragTexCoord);
	//vec4 surfaceColor = texture(normal_texture, fragTexCoord);//tested second texture
	if(surfaceColor.a < 0.5)
	{ 
		discard;
	 }
	
	//vec3 fogDistance = fragVert - light.position;
	float distance = sqrt((cameraToPoint.x * cameraToPoint.x) + (cameraToPoint.y * cameraToPoint.y) + (cameraToPoint.z * cameraToPoint.z));;
	//vec3 rayDir
	float fogB = 0.01f;
	float fogAmount = 1.0 - exp(-distance*fogB);
	vec3 fogColor = vec3(0.01,0.01,0.01);

	finalColor = vec4(brightness * light.intensities * surfaceColor.rgb, surfaceColor.a);
	vec3 fogFinalColor = mix(finalColor.rgb, fogColor, fogAmount);
	
	finalColor = vec4 (fogFinalColor, surfaceColor.a);
	//finalColor = vec4(brightness * light.intensities * surfaceColor.rgb, surfaceColor.a);
	
//	if (normal.x == 0)
//		finalColor = texture(tex, fragTexCoord);
//	else
		
   // finalColor = texture(tex, fragTexCoord);
	 //finalColor.y = finalColor.y - n;
	//finalColor = vec4(fragTexCoord, 0.0,0.0);
}