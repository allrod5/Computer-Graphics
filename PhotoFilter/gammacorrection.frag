#version 130
in vec2 v_texCoord;
out vec4 myfragcolor;
uniform sampler2D texture1;
uniform float Gamma;

void main(void)
{
	myfragcolor=texture2D(texture1,v_texCoord);
	myfragcolor = vec4( pow( myfragcolor.rgb, vec3(1.0/Gamma) ), 1.0 );
}

