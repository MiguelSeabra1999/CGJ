#include "Camera.h"

using namespace CameraSpace;
	
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

