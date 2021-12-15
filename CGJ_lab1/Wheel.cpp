#include "Wheel.h"


using namespace WheelSpace;
using namespace GameObjectSpace;


Wheel::Wheel()
{
	GameObject::GameObject();
}
void Wheel::start()
{

}
void Wheel::update()
{
	GameObject::update();
	GameObject::transform.localTransform.rotate(0, 5, 0);
}
void Wheel::initDraw(GLuint myShaderProgramIndex)
{
	GameObject::initDraw(myShaderProgramIndex);
	MyMesh amesh;
	float amb[] = { 0.2f, 0.15f, 0.1f, 1.0f };
	float diff[] = { 0.8f, 0.6f, 0.4f, 1.0f };
	float spec[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float emissive[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float shininess = 100.0f;
	int texcount = 0;


	amesh = createTorus(1, 2, 10, 10);
	memcpy(amesh.mat.diffuse, diff, 4 * sizeof(float));
	memcpy(amesh.mat.specular, spec, 4 * sizeof(float));
	memcpy(amesh.mat.emissive, emissive, 4 * sizeof(float));
	amesh.mat.shininess = shininess;
	amesh.mat.texCount = texcount;
	myMeshes.push_back(amesh);


}
