#include "Orange.h"
#include "Scene.h"
using namespace GameObjectSpace;



Orange::Orange(float mapSize)
{
	//GameObject::GameObject();

	rigidbody = new RigidBody(this);
	rigidbody->damping = 0;
	AddComponent(rigidbody);
	moveInRandomDirection();
	
	bounds = mapSize / 2;

}
void Orange::start()
{
	GameObject::start();
	collider = (Collider*)GetComponent("Collider");
	respawn();
	//queueRespawn();
}
void Orange::update()
{
	GameObject::update();
	//transform.globalTransform.pos[0] += 0.1f;
	GameObject::transform.globalTransform.rotate(2, 5, 3);

	rigidbody->addForce(transform.localTransform.forward, acceleration);

	if(!respawning)
	{
		if (abs(transform.globalTransform.pos[0]) > bounds || abs(transform.globalTransform.pos[1]) > bounds || abs(transform.globalTransform.pos[2]) > bounds)
		{
			queueRespawn();
		}
	}
	else if (Scene::timeUtil->time > respawnTime)
	{
		respawn();
	}

	//cout << transform.globalTransform.pos[0] << " " << transform.globalTransform.pos[2];
}

void Orange::queueRespawn()
{
	collider->isActive = false;
	respawnTime = Scene::timeUtil->time + 2;
	myMeshes.clear();
	respawning = true;
}
void Orange::respawn()
{
	collider->isActive = true;
	respawning = false;
	respawnTime = 0;
	initDraw(shaderProgramIndex);
	goToRandomPos();
	moveInRandomDirection();
	rigidbody->setVelocitiesZero();

}
void Orange::initDraw(GLuint myShaderProgramIndex)
{
	GameObject::initDraw(myShaderProgramIndex);
	MyMesh amesh;
	amesh = createSphere(radius, 10);
	
	GameObject::initMaterial();
	amesh.mat = *material;
	myMeshes.push_back(amesh);
}

void Orange::goToRandomPos()
{
	float pos = randomRange(-bounds, bounds);
	transform.setPosition(pos/4, 0.5, pos/4);
}

void Orange::moveInRandomDirection()
{
	
	float angle = randomRange(0, 360);
	GameObject::transform.localTransform.setRotation(0, 0, 0);
	GameObject::transform.localTransform.rotate(0,angle,0);
	
	/** /
	rigidbody->setVelocity(transform.globalTransform.forward);
	multVectorConstant(rigidbody->velocity, rigidbody->velocity, maxStartSpeed);
	rigidbody->setAcceleration(transform.globalTransform.forward);
	multVectorConstant(rigidbody->acceleration, rigidbody->acceleration, acceleration);
	/**/
}
void Orange::OnTriggerEnter()
{
	queueRespawn();
}


