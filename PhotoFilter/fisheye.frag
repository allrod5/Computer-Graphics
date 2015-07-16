#version 130
in vec2 v_texCoord;
uniform sampler2D texture1;
uniform vec2 u_resolution;
uniform vec2 mouse;
uniform float lensSize; // 0.4

void main(void)
{
	vec2 p = gl_FragCoord.xy / u_resolution.xy;
	vec2 m = mouse.xy / u_resolution.xy;

	vec2 d = m - p;
	float r = sqrt(dot(d, d)); // distance of pixel from mouse

	vec2 uv;
	vec3 col = vec3(0.0, 0.0, 0.0);
	if (r > lensSize+0.001)
	{
		uv = p;
		col = texture2D(texture1, vec2(uv.x, -uv.y)).xyz;
	}
	else if (r < lensSize-0.001)
	{
		// Thanks to Paul Bourke for these formulas; see
		// http://paulbourke.net/miscellaneous/lenscorrection/
		// and .../lenscorrection/lens.c
		// Choose one formula to uncomment:
		// SQUAREXY:
		// uv = m + vec2(d.x * abs(d.x), d.y * abs(d.y));
		// SQUARER:
		uv = m + d * r; // a.k.a. m + normalize(d) * r * r
		// SINER:
		// uv = m + normalize(d) * sin(r * 3.14159 * 0.5);
		// ASINR:
		// uv = m + normalize(d) * asin(r) / (3.14159 * 0.5);
		col = texture2D(texture1, vec2(uv.x, -uv.y)).xyz;
	}
	gl_FragColor = vec4(col, 1.0);
}
