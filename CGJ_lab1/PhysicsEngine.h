#pragma once
#include "Collider.h"
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
			instance = this;
		}
		void update()
		{
			CheckCollisions();
		}
		void CheckCollisions();
		

	private:
		static PhysicsEngine* instance;
	};
}

