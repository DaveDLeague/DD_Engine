#version 330 core

in vec3 vecPosition;

uniform mat4 modelViewProjMatrix;

void main(){
	gl_Position = modelViewProjMatrix * vec4(vecPosition, 1.0);
}
