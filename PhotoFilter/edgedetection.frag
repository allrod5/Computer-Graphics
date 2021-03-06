#version 440
in vec2 v_texCoord;
uniform sampler2D texture1;
uniform float EdgeThreshold;
uniform vec2 u_resolution;
uniform float dividerValue;

float luma( vec3 color )
{
	return 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
}

vec4 highlightEdges()
{
	float dx = 1.0 / float(u_resolution.x);
	float dy = 1.0 / float(u_resolution.y);
	float s00 = luma(texture2D(texture1,v_texCoord + vec2(-dx,dy) ).rgb);
	float s10 = luma(texture2D(texture1,v_texCoord + vec2(-dx,0.0) ).rgb);
	float s20 = luma(texture2D(texture1,v_texCoord + vec2(-dx,-dy) ).rgb);
	float s01 = luma(texture2D(texture1,v_texCoord + vec2(0.0,dy) ).rgb);
	float s11 = luma(texture2D(texture1,v_texCoord + vec2(0.0,0.0) ).rgb);
	float s21 = luma(texture2D(texture1,v_texCoord + vec2(0.0,-dy) ).rgb);
	float s02 = luma(texture2D(texture1,v_texCoord + vec2(dx, dy) ).rgb);
	float s12 = luma(texture2D(texture1,v_texCoord + vec2(dx, 0.0) ).rgb);
	float s22 = luma(texture2D(texture1,v_texCoord + vec2(dx, -dy) ).rgb);
	float sx = s00 + 2 * s10 + s20 - (s02 + 2 * s12 + s22);
	float sy = s00 + 2 * s01 + s02 - (s20 + 2 * s21 + s22);
	float dist = sx * sx + sy * sy;
	if( dist>EdgeThreshold )
		return vec4(1.0);
	else
		return vec4(0.0,0.0,0.0,1.0);
}

void main()
{
	vec2 uv = v_texCoord.xy;
	if (uv.x < dividerValue+0.001 && uv.x > dividerValue-0.001) {
		gl_FragColor = vec4(0.0);
	} else if (uv.x < dividerValue) {
		gl_FragColor = highlightEdges();
	} else {
		gl_FragColor = texture2D(texture1, uv);
	}
}
