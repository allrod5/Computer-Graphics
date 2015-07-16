#version 130
in vec2 v_texCoord;
out vec4 myfragcolor;
uniform sampler2D texture1;
uniform float Gamma;
uniform float dividerValue;

void main(void)
{
	vec2 uv = v_texCoord.xy;
	if (uv.x < dividerValue+0.001 && uv.x > dividerValue-0.001) {
		myfragcolor = vec4(0.0);
	} else if (uv.x < dividerValue) {
		myfragcolor=texture2D(texture1,v_texCoord);
		myfragcolor = vec4( pow( myfragcolor.rgb, vec3(1.0/Gamma) ), 1.0 );
	} else {
		myfragcolor = texture2D(texture1, uv);
	}

}

