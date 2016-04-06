
#version 330

uniform mat4 view_matrix, model_matrix, proj_matrix;

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec2 vertTexCoord;
layout (location = 2) in vec3 vertNormal;
layout (location = 3) in vec3 vertTangent;
layout (location = 4) in vec3 vertBitangent;

out vec3 fragVert;
out vec2 fragTexCoord;
out vec3 fragNormal;
out mat3 TBN;

void main() {

	mat4 CTM =  proj_matrix * view_matrix * model_matrix;
    // Pass the tex coord straight through to the fragment shader
    fragTexCoord = vertTexCoord;
	fragNormal = vertNormal;
	fragVert = in_Position;

    gl_Position = CTM * vec4(in_Position, 1);

	mat3 mv3x3 = mat3(transpose(inverse(view_matrix))*model_matrix);//
	
	vec3 vertexNormal_cameraspace = mv3x3 * normalize(vertNormal);//normal in model space
	vec3 vertexTangent_cameraspace = mv3x3 * normalize(vertTangent);//tangent in model space
	vec3 vertexBittangent_cameraspace = mv3x3 * normalize(vertBitangent);//bitangent in model space

	TBN = transpose(mat3(vertexTangent_cameraspace, vertexBittangent_cameraspace, vertexNormal_cameraspace));
}