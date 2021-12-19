#include "Camera.h"

using namespace GameObjectSpace;
	
Camera::Camera()
{
	GameObject::GameObject();


}

Camera::Camera(CamType_t t, float args[6]) {
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

	cout << "pos: " << lookAt[0] << ", " << lookAt[1] << ", " << lookAt[2] << endl;
	cout << "target pos: " << lookAt[3] << ", " << lookAt[4] << ", " << lookAt[5] << endl;
	cout << "radius: " << GetCameraRadius() << endl;


}
void Camera::SetCameraPosition() {
}
void Camera::SetCameraLookAt() {
}

void Camera::UpdateProjection() {
	// parameters left, right, bottom, top, near, far
	loadIdentity(PROJECTION);
	if (myType == CamType_t::ortho_t) {
		ortho(projArgs[0], projArgs[1], projArgs[2], projArgs[3], projArgs[4], projArgs[5]);
	}

	//parameters angle, ration, near, far
	if (myType == CamType_t::perspective_t) {
		perspective(projArgs[0], projArgs[1], projArgs[2], projArgs[3]);
	}

}


void Camera::SetProjArgs(float args[6])
{
	projArgs[0] = args[0];
	projArgs[1] = args[1];
	projArgs[2] = args[2];
	projArgs[3] = args[3];
	projArgs[4] = args[4];
	projArgs[5] = args[5];
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




