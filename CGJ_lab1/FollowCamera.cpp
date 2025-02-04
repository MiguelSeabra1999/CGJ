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
	lerp = true;


}

FollowCamera::FollowCamera(Transform * parent, CamType_t t, float args[8]) {
	Camera::Camera(t, args);
	radius = sqrt(verticalDist * verticalDist + horizontalDist * horizontalDist);
	moving = true;
	GameObject::transform.parent = parent;
	SetProjArgs(args);
	SetCameraType(t);
	SetCameraPosition();
	SetCameraLookAt();
	SetCameraRadius();
	SetAngles();
	lerp = true;
}

void FollowCamera::update()
{

	//not calling GameObject::update since there is no need to perform a render step, however that means we can add compontents
	if (follow) {
		UpdateCameraPosition();
		SetCameraLookAt();

	}
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
	// o alpha funciona ao inverso aka -alpha
	// mudar o playerMoving para ver se o carro ainda tem aceleracao
	// fazer o lerp ao contrario qdo se faz marcha atras
	SetCameraRadius();
	UpdateAngles();


	if (lerp) {
		PlayerCar * car = (PlayerCar*)GameObject::transform.parent->gameObject;
		if (car->velocity>0) {
			if (zeta > threshhold) { alpha -= zeta/angularConstantForLerp; }
			else if (zeta < -threshhold) { alpha -= zeta/angularConstantForBackWardsLerp; }

		}
		else if (car->velocity < 0) {
			if (zeta < PI-threshhold && zeta>0) { alpha += (PI-zeta) / angularConstantForBackWardsLerp; }
			else if (zeta > -PI+threshhold && zeta<0) { alpha += -(PI+zeta) / angularConstantForBackWardsLerp; }
		}
	}

	GameObject::transform.globalTransform.pos[0] = GameObject::transform.parent->globalTransform.pos[0] + radius * sin(alpha) * cos(beta);
	GameObject::transform.globalTransform.pos[1] = GameObject::transform.parent->globalTransform.pos[1] + radius * sin(beta);
	GameObject::transform.globalTransform.pos[2] = GameObject::transform.parent->globalTransform.pos[2] + radius * cos(alpha) * cos(beta);

	SetCameraRadius();
	SetZeta();


}
void FollowCamera::SetPlayerMoving(bool state)
{
	playerMoving = state;
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
	if (alpha >= 2 * PI) alpha -= 2 * PI;
	else if (alpha <= 2 * PI) alpha += 2 * PI;
	if (beta >= 2*PI) beta -= 2*PI;
	else if (beta <= 2 * PI) beta += 2 * PI;
	//if (zeta >= 2 * PI) zeta -= 2 * PI;
}

void FollowCamera::SetZeta() {
	float res, dot;
	float xzProj[3] = { rad[0], 0.0f, rad[2] };
	float right[3] = { -GameObject::transform.parent->globalTransform.right[0], 0.0f, -GameObject::transform.parent->globalTransform.right[2] };
	float forward[3] = { GameObject::transform.parent->globalTransform.forward[0], 0.0f, GameObject::transform.parent->globalTransform.forward[2] };

	dot = dotProduct(forward, xzProj);
	res = acos(dotProduct(right, xzProj)/ (length(right) * length(xzProj)));
	if (dot > 0)
		zeta = res;
	else
		zeta = -res;

}