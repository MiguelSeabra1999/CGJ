#pragma once
#include "Collider.h"
#include "RigidBody.h"
namespace GameObjectSpace
{
	class Collision
	{
	public:
		
		Collider* Collider1;
		Collider* Collider2;

	};

	class PhysicsEngine//singleton
	{
	public:
		
		PhysicsEngine()
		{
			//instance = this;
		}
		void update();

		void CheckCollisions();

		void UpdatePositions();

	private:
		//static PhysicsEngine* instance;
	};
}

