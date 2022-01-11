#pragma once
#include "GameObject.h"


namespace GameObjectSpace{

	class PlayerCar : public GameObject
	{
	public:
		RigidBody* rigidbody = nullptr;
		float velocity;
		float acceleration;
		float backAcceleration = 0.001;
		float forwardAcceleration = 0.006;
		float maxSpeed = 0.2;
		float friction = 0.0005;
		
		PlayerCar();
		void start();
		void update();
		void forward(bool state);
		void backward(bool state);
		void left(bool state);
		void right(bool state);

		void OnCollisionEnter();
	private:
		float inputDir[2];
		float turnSpeed = 0.005f;
		float turnSpeedVelocityMod = 4; //how much more % you cant turn at small speed vs high speed
	};
}