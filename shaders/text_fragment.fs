#version 330 core
out vec4 color;

in vec2 texCoordinates;

uniform sampler2D text;
uniform vec4 textColor;

void main()
{    
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoordinates).r);
    color = textColor * sampled;
} 
