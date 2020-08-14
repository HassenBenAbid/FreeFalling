#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in float texID;
layout (location = 3) in vec4 color;

uniform mat4 pr_matrix ;
uniform mat4 vw_matrix = mat4(1.0f);
uniform mat4 ml_matrix = mat4(1.0f);

out DATA {
	vec4 pos;
	vec2 texCoord;
	float texID;
	vec4 color;
} dataOut;


void main(){
	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
	dataOut.pos = ml_matrix * position;
	dataOut.texCoord = texCoord;
	dataOut.texID = texID;
	dataOut.color = color;
}
