#pragma once
#include "GameObject.h"


namespace GameObjectSpace {
	class Cube : public GameObject
	{
	public:
		Cube();
	
		void update();
		void initDraw(GLuint myShaderProgramIndex);
	};

}
