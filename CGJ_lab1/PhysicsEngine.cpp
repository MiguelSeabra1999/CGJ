#include "PhysicsEngine.h"
#include "AVTmathLib.h"
using namespace GameObjectSpace;
void PhysicsEngine::update()
{

	
	CheckCollisions(&collisions);
	UpdateVelocities();
	int n = collisions.size();
	for(int i = 0; i < n; i++)
	{
		SolveCollision(collisions[i]);
	}
	UpdatePositions();
	collisions.clear();
}
void PhysicsEngine::CheckCollisions(vector<Collision*>* collisions)
{
	//vector<Collision*> collisions;
	bool hitSomething = false;
	int n = Collider::allColliders.size();
	//cout << n << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
		/**/	if (Collider::allColliders[i]->rigidbody == nullptr && Collider::allColliders[j]->rigidbody == nullptr)
				continue;/**/
			Collision* col = nullptr;
			if (Collider::allColliders[i]->checkCollision(Collider::allColliders[j], &col))
			{
				collisions->push_back(col);
				Collider::allColliders[i]->owner->OnCollisionEnter();
				Collider::allColliders[j]->owner->OnCollisionEnter();
		
			}
		}
	}

}


void PhysicsEngine::UpdateVelocities()
{
	int n = RigidBody::allRigidBodies.size();
	for (int i = 0; i < n; i++)
	{
		RigidBody* rb = RigidBody::allRigidBodies[i];
		//v = Fext/mass;
		rb->velocity[0] += rb->allForces[0] / rb->mass;
		rb->velocity[1] += rb->allForces[1] / rb->mass;
		rb->velocity[2] += rb->allForces[2] / rb->mass;
		rb->velocity[0] *= 1 - rb->damping;
		rb->velocity[1] *= 1 - rb->damping;
		rb->velocity[2] *= 1 - rb->damping;

		rb->setAllForcesZero();
	}
}

void PhysicsEngine::UpdatePositions()
{
	int n = RigidBody::allRigidBodies.size();
	for(int i = 0; i < n; i++)
	{
		RigidBody* rb = RigidBody::allRigidBodies[i];

		//x = x + v;
		rb->transform->globalTransform.pos[0] = rb->transform->globalTransform.pos[0] + rb->velocity[0];
		rb->transform->globalTransform.pos[1] = rb->transform->globalTransform.pos[1] + rb->velocity[1];
		rb->transform->globalTransform.pos[2] = rb->transform->globalTransform.pos[2] + rb->velocity[2];	
	}

}

void PhysicsEngine::SolveCollision(Collision* collision)
{
	float r1[3], r2[3];
	
	float w1 = 0, w2 = 0;//inverse masses
	float restitution1 = 1, restitution2 = 1;

	if(collision->collider1->rigidbody != nullptr)
	{
		w1 = collision->collider1->rigidbody->inverseMass;
		restitution1 = collision->collider1->restitution;
	}
	if (collision->collider2->rigidbody != nullptr)
	{
		w2 = collision->collider2->rigidbody->inverseMass;
		restitution2 = collision->collider2->restitution;
	}
	if (w1 == 0 && w2 == 0)
		return;

	float forcePercent1 = w1 / (w1 + w2);
	float forcePercent2 = -1 * w2 / (w1 + w2);

	multVectorConstant(r1, collision->penetrationVector, forcePercent1);//when implementing mass this value needs to be the weighted mass average of the object
	multVectorConstant(r2, collision->penetrationVector, forcePercent2);
	collision->collider1->owner->transform.globalTransform.translate(r1);
	collision->collider2->owner->transform.globalTransform.translate(r2);

	float restituition = restitution1 * restitution2;
	float dot;
	if (collision->collider1->rigidbody != nullptr)
	{

		normalize(r1, r1, 3);
		dot = dotProduct(r1, collision->collider1->rigidbody->velocity, 3);

		multVectorConstant(r1, r1, -1*dot);
		collision->collider1->rigidbody->addImpulse(r1,restituition*2);
		cout << "update 1 ";
	}
	if (collision->collider2->rigidbody != nullptr)
	{

		//normalize(r2, r2, 3);
		//dot = dotProduct(r2, collision->collider2->rigidbody->velocity, 3);
		
		//multVectorConstant(r2, r2, dot);
		collision->collider2->rigidbody->addImpulse(r2,restituition*2);
		cout << "update 2 ";
	}
	cout << endl;
	
}

