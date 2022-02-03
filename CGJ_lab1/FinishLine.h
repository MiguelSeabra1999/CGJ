#pragma once

#include "GameObject.h"
#include "ComponentLib.h"

namespace GameObjectSpace {
	class FinishLine : public GameObject
	{
	public:
		GameObject* particleSystem;
		AABB* col;
		float bestLap = -1;
		float currentLap = 0;
		float startLap = 0;
		TextElement* currentLapText;
		TextElement* bestLapText;

		FinishLine(GameObject* _particleSystem);
		void initDraw(GLuint myShaderProgramIndex);
		void OnTriggerEnter(Component* other);
		void start();
		void saveLap();
		void update();
	};
}

