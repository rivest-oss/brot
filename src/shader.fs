#version 330 core

out vec4 outColor;
uniform float off_x = 0.0;
uniform float off_y = 0.0;
uniform float scale = 1.0;
uniform float max_iterations = 256;

// Add, sub, mul.

void main() {
	vec2 uv = gl_FragCoord.xy / vec2(1280.0, 960.0);
	uv.x += off_x;
	uv.y += off_y;

	uv = uv * vec2(3.47 * scale, 2.24 * scale);
	uv = uv - vec2(2.0 * scale, 1.12 * scale);

	vec2 xy = vec2(0.0, 0.0);
	float iteration = 0;

	while((((xy.x * xy.x) + (xy.y * xy.y)) <= 4) && (iteration < max_iterations))
	{
		float tmp = xy.x * xy.x - xy.y * xy.y + uv.x;
		xy.y = 2 * xy.x * xy.y + uv.y;
		xy.x = tmp;
		iteration++;
	};

	float i = iteration / max_iterations;

	//outColor = vec4(uv.x * i * 1.5, uv.y * i * 1.5, 0.25 * i, 1.0);
	//outColor = vec4(i, i, i, 1.0);

	float a = 0.1;

	// Nice colors by @Eriksonn.
	// Source code: https://github.com/OneLoneCoder/Javidx9/blob/master/PixelGameEngine/SmallerProjects/OneLoneCoder_PGE_Mandelbrot.cpp#L542C1-L542C65
	outColor = vec4(
		0.5 * sin(a * iteration) + 0.5,
		0.5 * sin(a * iteration + 2.094) + 0.5,
		0.5 * sin(a * iteration + 4.188) + 0.5,
		1.0
	);
};
