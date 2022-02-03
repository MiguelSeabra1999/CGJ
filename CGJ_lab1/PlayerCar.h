#pragma once
#include "GameObject.h"


namespace GameObjectSpace{

	class PlayerCar : public GameObject
	{
	public:
		RigidBody* rigidbody = nullptr;
		int hp = 5;
		float velocity;
		float acceleration;
		float backAcceleration = 0.0054;
		float forwardAcceleration = 0.006;
		float maxSpeed = 0.2;
		float turnSpeed = 0.8f;
		float handbrakeTurnPercent = 2.0f;
		bool handbreaking = false;
		
		PlayerCar();
		void start();
		void update();
		void forward(bool state);
		void backward(bool state);
		void left(bool state);
		void right(bool state);

		void OnCollisionEnter(Component* other);
		void OnTriggerEnter(Component* other);
		void handbreak(bool state);
		void respawn();
		void damage();
	private:
		float inputDir[2];
		float startingPos[3];
		float startingRot[3];
		

	};
}