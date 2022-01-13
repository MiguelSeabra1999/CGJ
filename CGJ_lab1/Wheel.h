#pragma once
#include "GameObject.h"
#include "PlayerCar.h"

namespace GameObjectSpace {
	class Wheel : public GameObject
	{
	public:
		PlayerCar* car;
		Wheel();
		void start();
		void update();
		void initDraw(GLuint myShaderProgramIndex);
		void spawnParticle();
	};
}

