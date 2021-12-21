#include "GameObjectLib.h"

using namespace GameObjectSpace;


FixedTopDownCamera::FixedTopDownCamera(float pos[3])
{
	Camera::Camera();
	SetCameraCenter(pos);
	SetCameraPosition();
	SetCameraLookAt();
	follow = false;
	//set world up
	lookAt[6] = 1;
	lookAt[7] = 0;
	lookAt[8] = 0;

}

FixedTopDownCamera::FixedTopDownCamera(float pos[3], CamType_t t, float args[8]) {
	Camera::Camera(t, args);
	//set world up
	lookAt[6] = 1;
	lookAt[7] = 0;
	lookAt[8] = 0;
	follow = false;
	SetProjArgs(args);
	SetCameraType(t);
	SetCameraCenter(pos);
	SetCameraPosition();
	SetCameraLookAt();
}

void FixedTopDownCamera::SetCameraCenter(float pos[3]) {
	center[0] = pos[0];
	center[1] = pos[1];
	center[2] = pos[2];
}

void FixedTopDownCamera::update()
{

	//not calling GameObject::update since there is no need to perform a render step, however that means we can add compontents
	if (follow) {
		SetCameraPosition();
		SetCameraLookAt();
	}
}
void FixedTopDownCamera::SetCameraPosition()
{
	if (GameObject::transform.parent!= nullptr) {
		lookAt[0] = GameObject::transform.parent->globalTransform.pos[0];
		lookAt[1] = center[1];
		lookAt[2] = GameObject::transform.parent->globalTransform.pos[2];

	}
	else {
		lookAt[0] = center[0];
		lookAt[1] = center[1];
		lookAt[2] = center[2];
	}
	
}


void FixedTopDownCamera::SetCameraLookAt()
{
	if (GameObject::transform.parent != nullptr) {
		lookAt[3] = GameObject::transform.parent->globalTransform.pos[0];
		lookAt[4] = 0;
		lookAt[5] = GameObject::transform.parent->globalTransform.pos[2];
	}
	else {
		lookAt[0] = center[0];
		lookAt[1] = 0;
		lookAt[2] = center[2];
	}

	
}
