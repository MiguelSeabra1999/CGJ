#include "Camera.h"

using namespace GameObjectSpace;
	
Camera::Camera()
{
	GameObject::GameObject();

}

void Camera::update()
{
	//not calling GameObject::update since there is no need to perform a render step, however that means we can add compontents
}
void Camera::SetCameraPosition() {}
void Camera::SetCameraLookAt() {}

void Camera::UpdateProjection() {

	// for now all orthographic projections have near == -1 and far == 1, it is the most common use case
	// other scenarios arent relavant for this project
	// parameters left, right, bottom, top, near, far
	if (myType == CamType_t::ortho_t) {
		//printf("ortho!");

		ortho(projArgs[0], projArgs[1], projArgs[2], projArgs[3], -1, 1);
	}

	//parameters angle, ration, near, far
	if (myType == CamType_t::perspective_t) {
		perspective(projArgs[0], projArgs[1], projArgs[2], projArgs[3]);
	}

}


void Camera::SetProjArgs(float arg1, float arg2, float arg3, float arg4)
{
	projArgs[0] = arg1;
	projArgs[1] = arg2;
	projArgs[2] = arg3;
	projArgs[3] = arg3;
}

void Camera::SetCameraType(CamType_t t) {
	myType = t;
}


