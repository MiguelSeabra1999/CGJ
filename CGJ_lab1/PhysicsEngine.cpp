#include "PhysicsEngine.h"
using namespace GameObjectSpace;
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

