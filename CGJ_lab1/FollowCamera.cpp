﻿#include "GameObjectLib.h"

using namespace GameObjectSpace;


FollowCamera::FollowCamera(Transform * parent)
{
	Camera::Camera();
	radius = sqrt(verticalDist*verticalDist + horizontalDist * horizontalDist);
	moving = true;
	GameObject::transform.parent = parent;
	SetCameraPosition();
	SetCameraLookAt();
	SetCameraRadius();
	SetAngles();


}

FollowCamera::FollowCamera(Transform * parent, CamType_t t, float args[6]) {
	Camera::Camera();
	radius = sqrt(verticalDist * verticalDist + horizontalDist * horizontalDist);
	moving = true;
	GameObject::transform.parent = parent;
	SetCameraPosition();
	SetCameraLookAt();
	SetCameraRadius();
	SetAngles();
}

void FollowCamera::update()
{

	//not calling GameObject::update since there is no need to perform a render step, however that means we can add compontents
	//SetCameraPosition();
	UpdateCameraPosition();
	SetCameraLookAt();
}
void FollowCamera::SetCameraPosition()
{

	GameObject::transform.globalTransform.pos[0] = GameObject::transform.parent->globalTransform.pos[0] + GameObject::transform.parent->globalTransform.right[0] * horizontalDist;
	GameObject::transform.globalTransform.pos[1] = GameObject::transform.parent->globalTransform.pos[1] + verticalDist;
	GameObject::transform.globalTransform.pos[2] = GameObject::transform.parent->globalTransform.pos[2] + GameObject::transform.parent->globalTransform.right[2] * horizontalDist;
}

void FollowCamera::UpdateCameraPosition()
{
	// muda estas constantes para valores de sensibilidade a passar a camara
	SetCameraRadius();
	//UpdateAngles();
	cout << "zeta :" << zeta << endl;
	if ( zeta>0) alpha -= zeta/0.01f; //zeta/0.001f;
	if ( zeta<0) alpha += zeta/0.01f;//zeta/0.001f;
	
	GameObject::transform.globalTransform.pos[0] = GameObject::transform.parent->globalTransform.pos[0] + radius * cos(alpha) ;
	GameObject::transform.globalTransform.pos[1] = GameObject::transform.parent->globalTransform.pos[1] + radius* sin(beta) ;
	GameObject::transform.globalTransform.pos[2] = GameObject::transform.parent->globalTransform.pos[2] + radius*sin(alpha) *cos(beta);
	SetCameraRadius();
	SetZeta();


}
void FollowCamera::PlayerAKeyState(bool state)
{
	Astate = state;
}
void FollowCamera::PlayerDKeyState(bool state)
{
	Dstate = state;
}

void FollowCamera::SetCameraLookAt()
{
	lookAt[0] = GameObject::transform.globalTransform.pos[0];
	lookAt[1] = GameObject::transform.globalTransform.pos[1];
	lookAt[2] = GameObject::transform.globalTransform.pos[2];
	lookAt[3] = GameObject::transform.parent->globalTransform.pos[0];
	lookAt[4] = GameObject::transform.parent->globalTransform.pos[1];
	lookAt[5] = GameObject::transform.parent->globalTransform.pos[2];
	//set world up
	lookAt[6] = 0;
	lookAt[7] = 1;
	lookAt[8] = 0;
}

void FollowCamera::SetCameraRadius() {
	rad[0] = lookAt[3] - lookAt[0];
	rad[1] = lookAt[4] - lookAt[1];
	rad[2] = lookAt[5] - lookAt[2];
}


float FollowCamera::GetCameraRadius() {
	return radius;
}

void FollowCamera::SetAngles() {
	float yzProj[3] = {0.0f, rad[1], rad[2]};
	float xzProj[3] = { rad[0], 0.0f, rad[2] };
	float zz[3] = { 0.0f, 0.0f, 1.0f };

	alpha = acos(dotProduct(zz, xzProj) / (length(zz) * length(xzProj)));
	beta = acos(dotProduct(zz, yzProj)/ (length(zz)*length(yzProj)));
}


void FollowCamera::UpdateAngles() {
	//SetAngles();
	if (alpha >= 2*PI) alpha = 2*PI;
	if (beta >= 2*PI) beta = 2*PI;
	if (zeta >= 2 * PI) zeta = 2 * PI;
}

void FollowCamera::SetZeta() {
	float xzProj[3] = { rad[0], 0.0f, rad[2] };
	float right[3] = { -GameObject::transform.parent->globalTransform.right[0], 0.0f, -GameObject::transform.parent->globalTransform.right[2] };

	zeta = acos(dotProduct(right, xzProj) / (length(right) * length(xzProj)));
}