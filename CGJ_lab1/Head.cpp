#include "Head.h"
#include "ComponentLib.h"
using namespace GameObjectSpace;

// Created an instance of the Importer class in the meshFromAssimp.cpp file
extern Assimp::Importer importer;
// the global Assimp scene object
extern const aiScene* scene;

Head::Head():GameObject()
{
	LookAtCamera* lookAtCamera = new LookAtCamera(this);
	AddComponent(lookAtCamera);

}
void Head::initDraw(GLuint myShaderProgramIndex)
{
	GameObject::initDraw(myShaderProgramIndex);
	//import 3D file into Assimp scene graph
	Import3DFromFile("HeadModel/test.obj");

	//creation of Mymesh array with VAO Geometry and Material
	myMeshes = createMeshFromAssimp(scene, "HeadModel/test.obj/");
}

