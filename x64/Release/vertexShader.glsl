#version 330

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;

out vec3 fragPosition;
out vec3 fragNormal;

uniform mat4 meshMatrix = mat4(1);
uniform mat4 projMatrix = mat4(1);

void main() 
{
		gl_Position = projMatrix * meshMatrix * vec4(position,1);
		
		fragPosition=vec3(meshMatrix * vec4(position,1));
		fragNormal = vec3(meshMatrix * vec4(normal, 0));
}