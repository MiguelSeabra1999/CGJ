#include "CubeObj.h"
#include "ComponentLib.h"

using namespace GameObjectSpace;




Cube::Cube():GameObject()
{
	
}
void Cube::update()
{
	GameObject::update();
	RigidBody* rb = (RigidBody*)Cube::GetComponent("RigidBody");
	if (rb != nullptr)
	{
		//cout << rb->velocity[0] << ", " << rb->velocity[1] << ", " << rb->velocity[2] << endl;
	}
	
}
void Cube::OnCollisionEnter()
{


}

void Cube::initDraw(GLuint myShaderProgramIndex)
{
	GameObject::initDraw(myShaderProgramIndex);
	MyMesh amesh;
	if(!resizable)
		amesh = createCube();
	else {
		//transform.setScale(1.0f, 1.0f, 1.0f);
		amesh = createCube(size_x, size_y);
	}

	GameObject::initMaterial();
	amesh.mat = *material;
	myMeshes.push_back(amesh);


}

