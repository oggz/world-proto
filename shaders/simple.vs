#version 330 core // Vertex Shader

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 uv_coordinate;
out vec2 uv_coord;
out vec3 position;
out vec3 position_worldspace;
out vec3 normal_cameraspace;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform float time;

void main(){
  position = vertex;
  gl_Position = P * V * M * vec4( vertex, 1 );

  uv_coord = uv_coordinate;
  position_worldspace = ( M * vec4( vertex, 1 ) ).xyz;
  normal_cameraspace = ( V * M * vec4( vertex_normal, 0 ) ).xyz;
}
