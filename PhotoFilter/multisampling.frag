#version 130
in vec2 v_texCoord;
out vec4 myfragcolor;
uniform sampler2D texture1;

//uniform vec2 u_textureSize;
void main(void)
{
	myfragcolor=texture2D(texture1,v_texCoord);

}

