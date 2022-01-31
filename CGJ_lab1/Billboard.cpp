
#pragma once
#include "Billboard.h"
#include "ComponentLib.h"
using namespace GameObjectSpace;

Billboard::Billboard(bool cylindrical) :GameObject()
{
	LookAtCamera* lookAtCamera = new LookAtCamera(this);
	AddComponent(lookAtCamera);
	if(cylindrical)
	{
		lookAtCamera->cylindrical = true;
	}
	GameObject::isBillboard = true;

}
void Billboard::initDraw(GLuint myShaderProgramIndex)
{
	GameObject::initDraw(myShaderProgramIndex);
	MyMesh amesh;
	amesh = createQuad(1, 1);

	GameObject::initMaterial();
	material->diffuse[3] = 1;
	amesh.mat = *material;
	myMeshes.push_back(amesh);

}

