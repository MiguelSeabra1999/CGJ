#include "UserInterface.h"
using namespace GameObjectSpace;

void UserInterface::SetUIGlobalPosition(float x, float y)
{
	transform.setPosition(x, y, 0.0f);
}

void UserInterface::SetUILocalPosition(float x, float y)
{
	transform.setLocalPosition(x, y, 0.0f);
}

void UserInterface::initDraw(VSShaderLib shader)
{
	GameObject::initDraw(shader.getProgramIndex());
	MyMesh amesh;
	amesh = createQuad(width, height);
	GameObject::initMaterial();
	amesh.mat = *material;
	myMeshes.push_back(amesh);


}