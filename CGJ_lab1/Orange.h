#pragma once
#include "GameObject.h"


namespace GameObjectSpace {
	class Orange : public GameObject
	{
	public:
		float radius = 1;
		float minStartSpeed = 0.00001;
		float maxStartSpeed = 0.00003;
		float acceleration = 0.0001;
		RigidBody* rigidbody;

		Orange();
		void start();
		void update();
		void initDraw(GLuint myShaderProgramIndex);
	};
}

