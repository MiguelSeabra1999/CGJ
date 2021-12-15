#pragma once
#include "GameObject.h"

using namespace GameObjectSpace;

namespace WheelSpace {
	class Wheel : public GameObject
	{
	public:
		Wheel();
		void start();
		void update();
		void initDraw(GLuint myShaderProgramIndex);
	};
}

