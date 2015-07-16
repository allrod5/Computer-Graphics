#version 440
in vec2 v_texCoord;

uniform vec2 u_resolution;
uniform sampler2D texture1;
uniform float blurSize;

out vec4 FragColor;
uniform float PixOffset[5] = float[](0.0,1.0,2.0,3.0,4.0);
uniform float Weight[5];

vec4 pass1()
{
	float dy = blurSize / float(u_resolution.y);
	vec4 sum = texture2D(texture1, v_texCoord) * Weight[0];
	for( int i = 1; i < 5; i++ )
	{
		sum += texture2D( texture1,
						v_texCoord+vec2(0.0,PixOffset[i]) * dy )
				* Weight[i];
		sum += texture2D( texture1,
						v_texCoord- vec2(0.0,PixOffset[i]) * dy )
				* Weight[i];
	}
	return sum;
}

vec4 pass2()
{
	float dx = blurSize / float(u_resolution.x);
	vec4 sum = texture2D(texture1, v_texCoord) * Weight[0];
	for( int i = 1; i < 5; i++ )
	{
		sum += texture2D( texture1,
						v_texCoord+ vec2(PixOffset[i],0.0) * dx )
				* Weight[i];
		sum += texture2D( texture1,
						v_texCoord- vec2(PixOffset[i],0.0) * dx )
				* Weight[i];
	}
	return sum;
}

void main()
{
	FragColor = pass1();
	FragColor *= pass2();
}
