#include "CubeObj.h"


using namespace GameObjectSpace;




Cube::Cube()
{
	
}

void Cube::update()
{
	GameObject::update();


}
void Cube::initDraw(GLuint myShaderProgramIndex)
{
	GameObject::initDraw(myShaderProgramIndex);
	MyMesh amesh;
	amesh = createCube();
	GameObject::initMaterial();
	amesh.mat = *material;
	myMeshes.push_back(amesh);


}

