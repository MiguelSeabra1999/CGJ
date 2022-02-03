#pragma once
#include "GameObject.h"


namespace GameObjectSpace {
	class Cube : public GameObject
	{
	public:
		bool resizable = false;
		float size_x=1.0f, size_y=1.0f;
		Cube();
		void setResizable(float size_x, float size_y) { resizable = true; Cube::size_x = size_x; Cube::size_y = size_y; }
		
		void initDraw(GLuint myShaderProgramIndex);

		void update();
		void OnCollisionEnter();

		string GetType() { return "Cube"; };
	};

}
