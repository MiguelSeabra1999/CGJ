#include "Camera.h"

using namespace GameObjectSpace;
	
Camera::Camera()
{
	GameObject::GameObject();


}

Camera::Camera(CamType_t t, float args[8]) {
	GameObject::GameObject();
	SetProjArgs(args);
	SetCameraType(t);
}

void Camera::update()
{
	//not calling GameObject::update since there is no need to perform a render step, however that means we can add compontents
}


void Camera::UpdateCameraPosition(){
	lookAt[0] = GameObject::transform.globalTransform.pos[0];
	lookAt[1] = GameObject::transform.globalTransform.pos[1];
	lookAt[2] = GameObject::transform.globalTransform.pos[2];
}
void Camera::SetCameraPosition() {
}
void Camera::SetCameraLookAt() {
}

void Camera::UpdateProjection() {

	loadIdentity(PROJECTION);
	// parameters left, right, bottom, top, near, far
	float ratio = (multiplier * projArgs[0]) / projArgs[1];
	if (myType == CamType_t::ortho_t) {
		ortho(projArgs[2], projArgs[3], projArgs[4]/ratio, projArgs[5]/ratio, projArgs[6], projArgs[7]);
	}

	//parameters angle, ration, near, far
	if (myType == CamType_t::perspective_t) {
		perspective(projArgs[2], ratio, projArgs[3], projArgs[4]);
	}

}


void Camera::SetProjArgs(float args[8])
{
	projArgs[0] = args[0];
	projArgs[1] = args[1];
	projArgs[2] = args[2];
	projArgs[3] = args[3];
	projArgs[4] = args[4];
	projArgs[5] = args[5];
	projArgs[6] = args[6];
	projArgs[7] = args[7];
}



void Camera::SetCameraType(CamType_t t) {
	myType = t;
}

bool Camera::GetMovingAttr() {
	return moving;
}

float Camera::GetCameraRadius()
{

	return 0.0f;
}

void Camera::SetCameraRadius()
{
	float resFinal[3];
	resFinal[0] = lookAt[3] - lookAt[0];
	resFinal[1] = lookAt[4] - lookAt[1];
	resFinal[2] = lookAt[5] - lookAt[2];
	radius = length(resFinal);
}

void Camera::SetCameraCharacteristics(CamType_t t, float args[8], float w, float h)
{
	SetCameraType(t);
	SetProjArgs(args);
	SetWidthHeightProj(w, h);
}




