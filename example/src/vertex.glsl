#version 330 core

// These match the values in glVertexAttribPointer
layout(location = 0) in vec3 vertexPosition_model;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal_model;
layout(location = 3) in vec2 vertexUV;

uniform mat4 M;
uniform mat4 V;
uniform mat4 MVP;

out vec3 fragmentPosition_world;
out vec3 fragmentColor;
out vec3 fragmentNormal_world;
out vec2 fragmentUV;
  
void main(){
    // Output position of the vertex, in clip space : MVP * position
    gl_Position = MVP * vec4(vertexPosition_model, 1);
    fragmentPosition_world = (M * vec4(vertexPosition_model, 1)).xyz;

    fragmentColor = vertexColor;

    fragmentNormal_world = (M * vec4(vertexNormal_model, 0)).xyz;

    fragmentUV = vertexUV;
}
