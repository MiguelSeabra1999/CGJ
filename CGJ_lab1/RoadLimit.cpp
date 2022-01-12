
#include "RoadLimit.h"
#include "ComponentLib.h"

using namespace GameObjectSpace;




RoadLimit::RoadLimit() :GameObject()
{

}

void RoadLimit::initDraw(GLuint myShaderProgramIndex)
{
	GameObject::initDraw(myShaderProgramIndex);
	MyMesh amesh;

	amesh = createTorus(0.1,0.5,10,10);


	GameObject::initMaterial();
	amesh.mat = *material;
	myMeshes.push_back(amesh);


}

