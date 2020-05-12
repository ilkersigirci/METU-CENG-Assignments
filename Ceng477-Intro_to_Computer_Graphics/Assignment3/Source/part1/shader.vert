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


// Output to Fragment Shader
out vec2 textureCoordinate; // For texture-color
out vec3 vertexNormal; // For Lighting computation
out vec3 ToLightVector; // Vector from Vertex to Light;
out vec3 ToCameraVector; // Vector from Vertex to Camera;


float computeHeight(vec3 vec){

    vec3 rgb = vec.xyz;
    return heightFactor * rgb.x;
}

void main(){
    
    textureCoordinate = vec2(1- (position.x + offset) / widthTexture, 1-position.z / heightTexture);
    vec3 textureColor = texture(firstTexture, textureCoordinate).xyz;
    
    vec3 currentPosition = vec3(position.x, computeHeight(textureColor), position.z);
    
    vec3 vertice1 = vec3(position.x-1, heightFactor * currentPosition.y, position.z);
    vec3 vertice2 = vec3(position.x, heightFactor * currentPosition.y, position.z-1);
    vec3 vertice3 = vec3(position.x+1, heightFactor * currentPosition.y, position.z-1);
    vec3 vertice4 = vec3(position.x+1, heightFactor * currentPosition.y, position.z);
    vec3 vertice5 = vec3(position.x, heightFactor * currentPosition.y, position.z+1);
    vec3 vertice6 = vec3(position.x-1, heightFactor * currentPosition.y, position.z+1);

    
    
    vec2 neighborCoordinate = vec2((widthTexture - vertice1.x - offset) / widthTexture, (heightTexture - vertice1.z) / heightTexture);
    textureColor = texture(firstTexture, neighborCoordinate).xyz;
    vertice1.y = computeHeight(textureColor);
    vertice1 = vec4(MVP * vec4(vertice1,1.0)).xyz - currentPosition;


    neighborCoordinate = vec2((widthTexture - vertice2.x - offset) / widthTexture, (heightTexture - vertice2.z) / heightTexture);
    textureColor = texture(firstTexture, neighborCoordinate).xyz;
    vertice2.y = computeHeight(textureColor);
    vertice2 = vec4(MVP * vec4(vertice2,1.0)).xyz - currentPosition;


    neighborCoordinate = vec2((widthTexture - vertice3.x - offset) / widthTexture, (heightTexture - vertice3.z) / heightTexture);
    textureColor = texture(firstTexture, neighborCoordinate).xyz;
    vertice3.y = computeHeight(textureColor);
    vertice3 = vec4(MVP * vec4(vertice3,1.0)).xyz - currentPosition;


    neighborCoordinate = vec2((widthTexture - vertice4.x - offset) / widthTexture, (heightTexture - vertice4.z) / heightTexture);
    textureColor = texture(firstTexture, neighborCoordinate).xyz;
    vertice4.y = computeHeight(textureColor);
    vertice4 = vec4(MVP * vec4(vertice4,1.0)).xyz - currentPosition;


    neighborCoordinate = vec2((widthTexture - vertice5.x - offset) / widthTexture, (heightTexture - vertice5.z) / heightTexture);
    textureColor = texture(firstTexture, neighborCoordinate).xyz;
    vertice5.y = computeHeight(textureColor);
    vertice5 = vec4(MVP * vec4(vertice5,1.0)).xyz - currentPosition;


    neighborCoordinate = vec2((widthTexture - vertice6.x - offset) / widthTexture, (heightTexture - vertice6.z) / heightTexture);
    textureColor = texture(firstTexture, neighborCoordinate).xyz;
    vertice6.y = computeHeight(textureColor);
    vertice6 = vec4(MVP * vec4(vertice6,1.0)).xyz - currentPosition;

   
    vec3 totalNormal = cross(vertice1, vertice2);
    totalNormal += cross(vertice2, vertice3);
    totalNormal += cross(vertice3, vertice4);
    totalNormal += cross(vertice4, vertice5);
    totalNormal += cross(vertice5, vertice6);
    totalNormal += cross(vertice6, vertice1);
  

    vertexNormal = normalize( totalNormal);
    ToCameraVector = normalize(cameraPosition - currentPosition);

    ToLightVector = normalize(lightPosition -  currentPosition);
    
    gl_Position =  MVP * vec4(currentPosition,1);
}