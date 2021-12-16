#pragma once
#include "GameObject.h"


namespace GameObjectSpace {
	class Wheel : public GameObject
	{
	public:
		Wheel();
		void start();
		void update();
		void initDraw(GLuint myShaderProgramIndex);
	};
}

