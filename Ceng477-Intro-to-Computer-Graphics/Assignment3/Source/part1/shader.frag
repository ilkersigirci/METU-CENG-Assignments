#version 410

out vec4 color;

uniform mat4 MVP; 
uniform mat4 MV; 
uniform vec4 cameraPosition;

uniform sampler2D firstTexture;
uniform sampler2D secondTexture;
uniform int widthTexture;
uniform int heightTexture;

in vec2 textureCoordinate;
in vec3 vertexNormal;   // For Lighting computation
in vec3 ToLightVector;  // Vector from Vertex to Light;
in vec3 ToCameraVector; // Vector from Vertex to Camera;

void main() {

	vec4 textureColor = texture(secondTexture, textureCoordinate);

	vec4 ka = vec4(0.25,0.25,0.25,1.0); // ambient reflectance coefficient
	vec4 Ia = vec4(0.3,0.3,0.3,1.0); // ambient light color

	vec4 kd = vec4(1.0, 1.0, 1.0, 1.0); // diffuse reflectance coefficient
	vec4 Id = vec4(1.0, 1.0, 1.0, 1.0); // diffuse light color
	
	vec4 ks = vec4(1.0, 1.0, 1.0, 1.0); // specular reflectance coefficient
	vec4 Is = vec4(1.0, 1.0, 1.0, 1.0); // specular light color
	
	int specExp = 100; // specular exponent

	vec3 halfvector = normalize(ToCameraVector + ToLightVector);

	vec4 ambient = Ia * ka;
	//vec4 diffuse = Id * kd * clamp(dot(vertexNormal, ToLightVector), 0, 1);
	vec4 diffuse = Id * kd * clamp(max(0, dot(normalize(vertexNormal), normalize(ToLightVector))), 0, 1);
	vec4 specular =  Is * ks * pow(max(0, clamp(dot(vertexNormal, halfvector), 0, 1)), specExp);
	
	color = vec4(clamp( textureColor.xyz * vec3(ambient + diffuse + specular), 0.0, 1.0), 1.0);
}
