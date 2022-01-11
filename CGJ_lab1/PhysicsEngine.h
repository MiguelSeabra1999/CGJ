#pragma once
#include "Collider.h"
#include "RigidBody.h"
namespace GameObjectSpace
{
	class Collision
	{
	public:
		Collider* collider1;
		Collider* collider2;
		float penetrationVector[3]; //from collider1 to collider2
		Collision(Collider* Collider1, Collider* Collider2, float penetration_x, float penetration_y, float penetration_z)
		{
			collider1 = Collider1;
			collider2 = Collider2;
			penetrationVector[0] = penetration_x;
			penetrationVector[1] = penetration_y;
			penetrationVector[2] = penetration_z;
		}
		Collision(Collider* Collider1, Collider* Collider2, float* penetration)
		{
			//Collision(Collider1, Collider2, penetration[0], penetration[1], penetration[2]);
			collider1 = Collider1;
			collider2 = Collider2;
			penetrationVector[0] = penetration[0];
			penetrationVector[1] = penetration[1];
			penetrationVector[2] = penetration[2];
		}

	};

	class PhysicsEngine//singleton
	{
	public:
		vector<Collision*> collisions;
		PhysicsEngine()
		{
			//instance = this;
		}
		void update();

		void CheckCollisions(vector<Collision*>* collisions);

		void UpdatePositions();

		void SolveCollision(Collision* collision);

		void UpdateVelocities();

	//private:
		//static PhysicsEngine* instance;
	};
}

