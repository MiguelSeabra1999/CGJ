#pragma once

#include "GameObject.h"


namespace GameObjectSpace {
	class RoadLimit : public GameObject
	{
	public:
		RoadLimit();
		void initDraw(GLuint myShaderProgramIndex);
	};

}
