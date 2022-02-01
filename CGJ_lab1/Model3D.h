#pragma once

#include "GameObject.h"


namespace GameObjectSpace {
	class Model3D : public GameObject
	{
	public:
		const char* fileLocation;
		Model3D(const char* file);
		void initDraw(GLuint myShaderProgramIndex );

	};
}

