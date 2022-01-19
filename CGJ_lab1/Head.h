#pragma once
#include "GameObject.h"


namespace GameObjectSpace {
	class Head : public GameObject
	{
	public:
		Head();
		void initDraw(GLuint myShaderProgramIndex);

	};
}

