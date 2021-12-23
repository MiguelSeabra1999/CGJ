#pragma once
struct Light
{
	float position[4] = { 0,0,0,1 };
	float color[4] = { 1,1,1,1 };
	float direction[4] = { -0.5f,-0.5f,0,0 };
	float angle = 45.0f;
	int type = 0; // 0-> point, 1 -> dir , 2 -> spot, 3 -> global
	//attenuation parameters
	float constant = 0;
	float linear = 0;
	float quadratic = 0;
};
