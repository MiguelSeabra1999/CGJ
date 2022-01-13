#include "Wheel.h"
#include "SmokeParticle.h"
#include "Scene.h"

using namespace GameObjectSpace;


Wheel::Wheel()
{
	GameObject::GameObject();
}
void Wheel::start()
{
	car = (PlayerCar*)transform.parent->gameObject;
}
void Wheel::update()
{
	GameObject::update();
	GameObject::transform.localTransform.rotate(0, 5, 0);

	
	if (car->acceleration > 0 && car->handbreaking)
		spawnParticle();
}
void Wheel::initDraw(GLuint myShaderProgramIndex)
{
	GameObject::initDraw(myShaderProgramIndex);
	MyMesh amesh;
	amesh = createTorus(1, 2, 10, 10);
	GameObject::initMaterial();
	amesh.mat = *material;
	myMeshes.push_back(amesh);


}
void Wheel::spawnParticle()
{
	SmokeParticle* particle = new SmokeParticle();
	float spawnPos[3] = { (int)randomRange(-100,100) / 10000.0f,(int)randomRange(-100,100) / 10000.0f,(int)randomRange(-100,100) / 10000.0f };
	addVectors(spawnPos, spawnPos, transform.globalTransform.pos, 3);
	car->currentScene->instatiate((GameObject*)particle, spawnPos);
}