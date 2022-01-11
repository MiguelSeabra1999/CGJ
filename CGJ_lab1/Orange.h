#pragma once
#include "GameObject.h"


namespace GameObjectSpace {
	class Orange : public GameObject
	{
	public:
		float radius = 1;
	
		float acceleration = 0.01;
		long int respawnTime = 0;
		bool respawning = false;
		float dir[3];

		RigidBody* rigidbody;
		float bounds;

		Orange(float mapSize);
		void start();
		void update();
		void initDraw(GLuint myShaderProgramIndex);
		void respawn();
		void queueRespawn();
		void goToRandomPos();
		void moveInRandomDirection();
	};
}

