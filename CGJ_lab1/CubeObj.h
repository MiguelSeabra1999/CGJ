#pragma once
#include "GameObject.h"

using namespace GameObjectSpace;

namespace CubeSpace {
	class Cube : public GameObject
	{
	public:
		Cube();
		void start();
		void update();
		void initDraw(GLuint myShaderProgramIndex);
	};

}
