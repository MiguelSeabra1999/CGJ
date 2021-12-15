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
		float forwardAcceleration = 0.003;
		float maxSpeed = 0.1;
		float friction = 0.005;
		PlayerCar();
		void start();
		void update();
		void initDraw(GLuint myShaderProgramIndex);
		void forward(bool state);
		void backward(bool state);
		void left(bool state);
		void right(bool state);

	private:
		float inputDir[2];
		float speed = 0.01f;
	};
}