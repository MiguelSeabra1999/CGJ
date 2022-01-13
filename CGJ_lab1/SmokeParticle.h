#pragma once
#include "GameObject.h"

namespace GameObjectSpace {
	class SmokeParticle : public GameObject
	{
	public:
		float effectTime = 0.25f;
		float effectTime_deviation = 0.14f;
		int count = 20;
		int curr = 0;
		float finalScale[3] = {10,10,10};
		float startScale[3] = { 1,1,1 };
		float scaleIncrease = 5.0f;
		float scaleIncrease_deviation = 3.0f;
		float startTime = 0;
		SmokeParticle();
		void start();
		void update();
		void initDraw(GLuint myShaderProgramIndex);
		float randomizeScaleIncrease();
	};

}
