#pragma once
#include "GameObject.h"
namespace GameObjectSpace {
	class Billboard : public GameObject
	{
	public:
		bool cylindrical = false;
		Billboard(bool cylindrical);
		void initDraw(GLuint myShaderProgramIndex);
		

	};
}
