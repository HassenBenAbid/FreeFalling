#version 330 core 

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 lightPos;
uniform sampler2D tex[32];

in DATA {
	vec4 pos;
	vec2 texCoord;
	float texID;
	vec4 color;
}inData;

void main(){
	vec2 hpos = vec2(0.0f, 0.0f);
	float inten = 0.6f;
	vec4 texColor = inData.color;

	if (inData.texID > 0.0f){
		int texID = int (inData.texID - 0.5f);
		vec4 alTex = texture(tex[texID], inData.texCoord);
		if (alTex.a < 0.1f) discard;

		texColor = alTex + vec4(inData.color.rgb,0.0f);
	}

	color = texColor ;
}
