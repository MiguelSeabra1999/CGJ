#include "CubeObj.h"
#include "ComponentLib.h"

using namespace GameObjectSpace;




Cube::Cube():GameObject()
{
	
}
void Cube::update()
{
	GameObject::update();

	
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

