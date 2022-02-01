
#pragma once
#include "GameObject.h"
namespace GameObjectSpace {
	class Skybox : public GameObject
	{
	public:
		GLint cubeMap_loc;
		Skybox();
		void initDraw(GLuint myShaderProgramIndex);
		void BindTexture();

		void draw();

	};
}
