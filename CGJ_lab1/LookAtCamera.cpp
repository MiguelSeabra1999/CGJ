#include "LookAtCamera.h"
#include "Scene.h"
using namespace GameObjectSpace;
LookAtCamera::LookAtCamera(GameObject* owner):Component(owner)
{

}
const char* LookAtCamera::GetType()
{
	return "LookAtCamera";
}
void LookAtCamera::update()
{

	Camera* cam = owner->currentScene->currentCam;
	if(cylindrical)
		owner->transform.lookAtCylindrical(&(cam->transform));
	else
		owner->transform.lookAt(&(cam->transform));

}