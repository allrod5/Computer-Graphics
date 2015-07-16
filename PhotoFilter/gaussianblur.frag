#version 440
uniform float dividerValue;
uniform float blurSize;

uniform sampler2D texture1;
uniform lowp float qt_Opacity;
varying vec2 v_texCoord;

vec4 pass1()
{
	vec2 uv = v_texCoord.xy;
	vec4 c = vec4(0.0);
	if (uv.x < dividerValue) {
		c += texture2D(texture1, uv - vec2(0.0, 4.0*blurSize)) * 0.05;
		c += texture2D(texture1, uv - vec2(0.0, 3.0*blurSize)) * 0.09;
		c += texture2D(texture1, uv - vec2(0.0, 2.0*blurSize)) * 0.12;
		c += texture2D(texture1, uv - vec2(0.0, 1.0*blurSize)) * 0.15;
		c += texture2D(texture1, uv) * 0.18;
		c += texture2D(texture1, uv + vec2(0.0, 1.0*blurSize)) * 0.15;
		c += texture2D(texture1, uv + vec2(0.0, 2.0*blurSize)) * 0.12;
		c += texture2D(texture1, uv + vec2(0.0, 3.0*blurSize)) * 0.09;
		c += texture2D(texture1, uv + vec2(0.0, 4.0*blurSize)) * 0.05;
	} else {
		c = texture2D(texture1, v_texCoord);
	}
	// First pass we don't apply opacity
	return c;
}

vec4 pass2()
{
	vec2 uv = v_texCoord.xy;
	vec4 c = vec4(0.0);
	if (uv.x < dividerValue) {
		c += texture2D(texture1, uv - vec2(4.0*blurSize, 0.0)) * 0.05;
		c += texture2D(texture1, uv - vec2(3.0*blurSize, 0.0)) * 0.09;
		c += texture2D(texture1, uv - vec2(2.0*blurSize, 0.0)) * 0.12;
		c += texture2D(texture1, uv - vec2(1.0*blurSize, 0.0)) * 0.15;
		c += texture2D(texture1, uv) * 0.18;
		c += texture2D(texture1, uv + vec2(1.0*blurSize, 0.0)) * 0.15;
		c += texture2D(texture1, uv + vec2(2.0*blurSize, 0.0)) * 0.12;
		c += texture2D(texture1, uv + vec2(3.0*blurSize, 0.0)) * 0.09;
		c += texture2D(texture1, uv + vec2(4.0*blurSize, 0.0)) * 0.05;
	} else {
		c = texture2D(texture1, v_texCoord);
	}
	return qt_Opacity * c;
}

void main()
{
	gl_FragColor = pass1();
	gl_FragColor += pass2();
}
