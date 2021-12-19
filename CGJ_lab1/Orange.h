#pragma once
#include "GameObject.h"


namespace GameObjectSpace {
	class Orange : public GameObject
	{
	public:
		float radius = 1;
		float minStartSpeed = 0.00006;
		float maxStartSpeed = 0.0001;
		float acceleration = 0.0001;
		long int respawnTime = 0;
		bool respawning = false;

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

