#include "Model3D.h"
#include "ComponentLib.h"
using namespace GameObjectSpace;

// Created an instance of the Importer class in the meshFromAssimp.cpp file
extern Assimp::Importer importer;
// the global Assimp scene object
extern const aiScene* scene;

Model3D::Model3D(const char* file) :GameObject()
{
	fileLocation = file;
}
void Model3D::initDraw(GLuint myShaderProgramIndex)
{
	GameObject::initDraw(myShaderProgramIndex);
	//import 3D file into Assimp scene graph
	Import3DFromFile(fileLocation);

	//creation of Mymesh array with VAO Geometry and Material
	myMeshes = createMeshFromAssimp(scene, fileLocation);
}

