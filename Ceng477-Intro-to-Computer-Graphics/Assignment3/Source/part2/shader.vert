#version 410

layout(location = 0) in vec3 position;

// Data from CPU 
uniform mat4 MVP; // ModelViewProjection Matrix
uniform mat4 MV; // ModelView idMVPMatrix
uniform vec3 cameraPosition;
uniform float heightFactor;

// Texture-related data
uniform sampler2D firstTexture;
uniform sampler2D secondTexture;
uniform int widthTexture;
uniform int heightTexture;

uniform vec3 lightPosition;
uniform float offset;
uniform float pi;


// Output to Fragment Shader
out vec2 textureCoordinate; // For texture-color
out vec3 vertexNormal; // For Lighting computation
out vec3 ToLightVector; // Vector from Vertex to Light;
out vec3 ToCameraVector; // Vector from Vertex to Camera;


float computeHeight(vec3 vec){
    vec3 textureColor = texture(firstTexture, textureCoordinate).xyz;
    return heightFactor * textureColor.x;
}
void main(){
    textureCoordinate = vec2((position.x / 125.0f - offset), (position.z / 250.0f));
    
    float radius = 350.0f;
    float alpha = 2.0*pi*(float(position.x)/125.0f);
    float beta =  pi*(float(position.z)/250.0f);

    float x = radius*sin(beta)*cos(alpha);
    float y = radius*sin(beta)*sin(alpha);
    float z = radius*cos(beta);
    
    vec3 myPos = vec3(x, y, z);

    vertexNormal = normalize(myPos);
    myPos += computeHeight(position)*vertexNormal;

    ToCameraVector = normalize(cameraPosition - myPos);
    ToLightVector = normalize(lightPosition -  myPos);
    
    // set gl_Position variable correctly to give the transformed vertex position
    gl_Position =  MVP * vec4(myPos,1);
    // gl_Position = vec4(0,0,0,0); // this is a placeholder. It does not correctly set the position
   
}