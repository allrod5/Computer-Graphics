#version 440
uniform float dividerValue;
uniform vec2 u_resolution;
uniform float magTol;
uniform float quantize;

uniform sampler2D texture1;
uniform lowp float qt_Opacity;
varying vec2 v_texCoord;

void main()
{
	vec4 color = vec4(1.0, 0.0, 0.0, 1.1);
	vec2 uv = v_texCoord.xy;
	if (uv.x < dividerValue+0.001 && uv.x > dividerValue-0.001)
		color = vec4(0.0);
	else if (uv.x < dividerValue) {
		vec2 st = v_texCoord.st;
		vec3 rgb = texture2D(texture1, st).rgb;
		vec2 stp0 = vec2(1.0/u_resolution.x,  0.0);
		vec2 st0p = vec2(0.0     ,  1.0/u_resolution.y);
		vec2 stpp = vec2(1.0/u_resolution.x,  1.0/u_resolution.y);
		vec2 stpm = vec2(1.0/u_resolution.x, -1.0/u_resolution.y);
		float i00 =   dot( texture2D(texture1, st).rgb, vec3(0.2125,0.7154,0.0721));
		float im1m1 = dot( texture2D(texture1, st-stpp).rgb, vec3(0.2125,0.7154,0.0721));
		float ip1p1 = dot( texture2D(texture1, st+stpp).rgb, vec3(0.2125,0.7154,0.0721));
		float im1p1 = dot( texture2D(texture1, st-stpm).rgb, vec3(0.2125,0.7154,0.0721));
		float ip1m1 = dot( texture2D(texture1, st+stpm).rgb, vec3(0.2125,0.7154,0.0721));
		float im10 =  dot( texture2D(texture1, st-stp0).rgb, vec3(0.2125,0.7154,0.0721));
		float ip10 =  dot( texture2D(texture1, st+stp0).rgb, vec3(0.2125,0.7154,0.0721));
		float i0m1 =  dot( texture2D(texture1, st-st0p).rgb, vec3(0.2125,0.7154,0.0721));
		float i0p1 =  dot( texture2D(texture1, st+st0p).rgb, vec3(0.2125,0.7154,0.0721));
		float h = -1.*im1p1 - 2.*i0p1 - 1.*ip1p1  +  1.*im1m1 + 2.*i0m1 + 1.*ip1m1;
		float v = -1.*im1m1 - 2.*im10 - 1.*im1p1  +  1.*ip1m1 + 2.*ip10 + 1.*ip1p1;
		float mag = sqrt(h*h + v*v);
		if (mag > magTol) {
			color = vec4(0.0, 0.0, 0.0, 1.0);
		}
		else {
			rgb.rgb *= quantize;
			rgb.rgb += vec3(0.5, 0.5, 0.5);
			ivec3 irgb = ivec3(rgb.rgb);
			rgb.rgb = vec3(irgb) / quantize;
			color = vec4(rgb, 1.0);
		}
	} else {
		color = texture2D(texture1, uv);
	}
	gl_FragColor = color;
}
