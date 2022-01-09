#include "PhysicsEngine.h"
using namespace GameObjectSpace;
void PhysicsEngine::update()
{

	CheckCollisions();
	UpdatePositions();


}
void PhysicsEngine::CheckCollisions()
{
	vector<Collision*> collisions;
	bool hitSomething = false;
	int n = Collider::allColliders.size();
	//cout << n << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			Collision* col = new Collision;
			if (Collider::allColliders[i]->checkCollision(Collider::allColliders[j], col))
			{
				//collisions.push_back(col);
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

