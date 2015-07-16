#version 400
in vec2 v_texCoord;
uniform sampler2D texture1;
uniform sampler2D BlurTex;

uniform vec2 u_resolution;
uniform float blurSize;
uniform float LumThresh;
uniform float dividerValue;

out vec4 FragColor;

uniform float PixOffset[10] = float[](0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
uniform float Weight[10];

float luma( vec3 color ) {
	return 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
}

vec4 pass1()
{
	vec4 val = texture2D(texture1, v_texCoord);
	return val * clamp( luma(val.rgb) -LumThresh, 0.0, 1.0 ) * (1.0 / (1.0 - LumThresh) );
}

vec4 pass2()
{
	float dy = blurSize / float(u_resolution.y);
	vec4 sum = texture2D(BlurTex, v_texCoord) * Weight[0];
	for( int i = 1; i < 10; i++)
	{
		sum += texture2D( BlurTex, v_texCoord +
						vec2(0.0,PixOffset[i]) * dy ) * Weight[i];
		sum += texture2D( BlurTex, v_texCoord -
						vec2(0.0,PixOffset[i]) * dy ) * Weight[i];
	}
	return sum;
}

vec4 pass3()
{
	float dx = blurSize / float(u_resolution.x);
	vec4 val = texture2D(texture1, v_texCoord);
	vec4 sum = texture2D(BlurTex, v_texCoord) * Weight[0];
	for( int i = 1; i < 10; i++ )
	{
		 sum += texture2D( BlurTex, v_texCoord + vec2(PixOffset[i],0.0) * dx ) * Weight[i];
		 sum += texture2D( BlurTex, v_texCoord - vec2(PixOffset[i],0.0) * dx ) * Weight[i];
	 }
	 return val + sum;
}
void main()
{
	vec2 uv = v_texCoord.xy;
	if (uv.x < dividerValue+0.001 && uv.x > dividerValue-0.001) {
		FragColor = vec4(0.0);
	} else if (uv.x < dividerValue) {
		FragColor = pass1();
		FragColor += pass2();
		FragColor += pass3();
	} else {
		FragColor = texture2D(texture1, uv);
	}
}
