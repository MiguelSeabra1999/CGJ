#include "Orange.h"

using namespace GameObjectSpace;



Orange::Orange(float mapSize)
{
	//GameObject::GameObject();

	rigidbody = new RigidBody(&transform);
	AddComponent(rigidbody);
	moveInRandomDirection();

	bounds = mapSize / 2;

	

}
void Orange::start()
{
	GameObject::start();
}
void Orange::update()
{
	GameObject::update();
	//transform.globalTransform.pos[0] += 0.1f;
	GameObject::transform.globalTransform.rotate(2, 5, 3);
	if(!respawning)
	{
		if (abs(transform.globalTransform.pos[0]) > bounds || abs(transform.globalTransform.pos[1]) > bounds || abs(transform.globalTransform.pos[2]) > bounds)
		{
			queueRespawn();
			//respawn();
		}
	}
	else if (currentTime > respawnTime)
	{
		respawn();
	}
	//cout << transform.globalTransform.pos[0] << " " << transform.globalTransform.pos[2];
}

void Orange::queueRespawn()
{

	respawnTime = currentTime + 2;
	myMeshes.clear();
	respawning = true;
}
void Orange::respawn()
{

	respawning = false;
	respawnTime = 0;
	initDraw(shaderProgramIndex);
	goToRandomPos();
	moveInRandomDirection();

}
void Orange::initDraw(GLuint myShaderProgramIndex)
{
	GameObject::initDraw(myShaderProgramIndex);
	MyMesh amesh;
	amesh = createSphere(radius, 3);
	
	GameObject::initMaterial();
	amesh.mat = *material;
	myMeshes.push_back(amesh);
}

void Orange::goToRandomPos()
{
	randomRange(-bounds, bounds);
	transform.setPosition(0, 0.5, 0);
}

void Orange::moveInRandomDirection()
{

	float angle = randomRange(0, 360);
	GameObject::transform.globalTransform.setRotation(0, 0, 0);
	GameObject::transform.globalTransform.rotate(0,angle,0);

	rigidbody->setVelocity(transform.globalTransform.forward);
	multVectorConstant(rigidbody->velocity, rigidbody->velocity, maxStartSpeed);
	rigidbody->setAcceleration(transform.globalTransform.forward);
	multVectorConstant(rigidbody->acceleration, rigidbody->acceleration, acceleration);
}


