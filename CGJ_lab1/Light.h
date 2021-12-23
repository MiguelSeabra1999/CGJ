#pragma once
struct Light
{
	float position[4] = { 0,0,0,1 };
	float eye_coords_position[4] = { 0,0,0,0 };
	float color[4] = { 1,1,1,1 };
	float direction[4] = { 0,1,0,0 };
	float eye_coords_direction[4] = {0,0,0,0 };
	float cos_angle = 0.5;//cos(angle) , in rads. Uses cosine to save on shader maths
	int type = 0; // 0-> point, 1 -> dir , 2 -> spot, 3 -> global
	//attenuation parameters
	float constant = 0;
	float linear = 0;
	float quadratic = 0;
};
