#include "GameObjectLib.h"

using namespace GameObjectSpace;


FixedTopDownCamera::FixedTopDownCamera(float x, float y, float z)
{
	Camera::Camera();
	SetCameraCenter(x, y, z);
	SetCameraPosition();
	SetCameraLookAt();
	//set world up
	lookAt[6] = 1;
	lookAt[7] = 0;
	lookAt[8] = 0;

}

void FixedTopDownCamera::SetCameraCenter(float x, float y, float z) {
	center[0] = x;
	center[1] = y;
	center[2] = z;
}

void FixedTopDownCamera::update()
{

	//not calling GameObject::update since there is no need to perform a render step, however that means we can add compontents
	SetCameraPosition();
	SetCameraLookAt();
}
void FixedTopDownCamera::SetCameraPosition()
{
	lookAt[0] = center[0];
	lookAt[1] = center[1];
	lookAt[2] = center[2];
	
}


void FixedTopDownCamera::SetCameraLookAt()
{
	lookAt[3] = center[0];
	lookAt[4] = 0;
	lookAt[5] = center[2];
	
}
