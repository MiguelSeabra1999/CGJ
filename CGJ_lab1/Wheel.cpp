#include "Wheel.h"

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
	amesh = createTorus(1, 2, 10, 10);
	diff[0] = 0.2f;
	diff[1] = 0.2f;
	diff[2] = 0.2f;
	GameObject::initMaterial();
	amesh.mat = *material;
	myMeshes.push_back(amesh);


}
