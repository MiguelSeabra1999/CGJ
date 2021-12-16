#include "GameObjectLib.h"

using namespace GameObjectSpace;


FollowCamera::FollowCamera(SimpleTransform* target)
{
	Camera::Camera();
	targetTransform = target;
	SetCameraPosition();
	SetCameraLookAt();
	//set world up
	lookAt[6] = 0;
	lookAt[7] = 1;
	lookAt[8] = 0;

}
void FollowCamera::update()
{

	//not calling GameObject::update since there is no need to perform a render step, however that means we can add compontents
	SetCameraPosition();
	SetCameraLookAt();
}
void FollowCamera::SetCameraPosition()
{
	lookAt[0] = targetTransform->pos[0] + targetTransform->right[0] * horizontalDist;
	lookAt[1] = targetTransform->pos[1] + verticalDist;
	lookAt[2] = targetTransform->pos[2] + targetTransform->right[2] * horizontalDist;
	/*lookAt[0] = targetTransform->pos[0];
	lookAt[1] = targetTransform->pos[1] + 1;
	lookAt[2] = targetTransform->pos[2];*/
}
void FollowCamera::SetCameraLookAt()
{
	lookAt[3] = targetTransform->pos[0];
	lookAt[4] = targetTransform->pos[1] ;
	lookAt[5] = targetTransform->pos[2] ;
	/*lookAt[3] = 0;
	lookAt[4] = 0;
	lookAt[5] = 1;*/
}
