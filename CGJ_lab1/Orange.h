#pragma once
#include "GameObject.h"


namespace GameObjectSpace {
	class Orange : public GameObject
	{
	public:
		float radius = 1;
	
		float acceleration = 0.003;
		long int respawnTime = 0;
		bool respawning = false;
		float dir[3];
		string name = "Orange";

		RigidBody* rigidbody;
		Collider* collider;
		float bounds;

		Orange(float mapSize);
		void start();
		void update();
		void initDraw(GLuint myShaderProgramIndex);
		void respawn();
		void queueRespawn();
		void goToRandomPos();
		void moveInRandomDirection();
		void OnTriggerEnter();
	};
}

