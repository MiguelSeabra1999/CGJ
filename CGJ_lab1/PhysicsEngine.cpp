#include "PhysicsEngine.h"
#include "AVTmathLib.h"
using namespace GameObjectSpace;
void PhysicsEngine::update()
{

	UpdatePositions();
	CheckCollisions(&collisions);

	int n = collisions.size();
	for(int i = 0; i < n; i++)
	{
		SolveCollision(collisions[i]);
	}

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
			Collision* col = nullptr;
			if (Collider::allColliders[i]->checkCollision(Collider::allColliders[j], &col))
			{
				collisions->push_back(col);
				cout << "Collision";
			}
		}
	}

}

void PhysicsEngine::UpdatePositions()
{
	int n = RigidBody::allRigidBodies.size();
	for(int i = 0; i < n; i++)
	{
		RigidBody* rb = RigidBody::allRigidBodies[i];
		//v = Fext/mass;
		rb->velocity[0] = rb->allForces[0] / rb->mass;
		rb->velocity[1] = rb->allForces[1] / rb->mass;
		rb->velocity[2] = rb->allForces[2] / rb->mass;
		//x = x + v;
		rb->transform->globalTransform.pos[0] = rb->transform->globalTransform.pos[0] + rb->velocity[0];
		rb->transform->globalTransform.pos[1] = rb->transform->globalTransform.pos[1] + rb->velocity[1];
		rb->transform->globalTransform.pos[2] = rb->transform->globalTransform.pos[2] + rb->velocity[2];

		rb->setAllForcesZero();
	}
}

void PhysicsEngine::SolveCollision(Collision* collision)
{
	float r1[3], r2[3];
	
	multVectorConstant(r1, collision->penetrationVector, 0.5f );//when implementing mass this value needs to be the weighted mass average of the object
	multVectorConstant(r2, collision->penetrationVector, -0.5f);
	collision->collider1->owner->transform.globalTransform.translate(r1);
	collision->collider2->owner->transform.globalTransform.translate(r2);
	
}

