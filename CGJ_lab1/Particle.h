#pragma once

#include "GameObject.h"
#include "GameObjectLib.h"
namespace GameObjectSpace {
	class Particle : public Billboard
	{
	public:
		float initialPosition[3];
		float initialSpeed[3];
		float acceleration[3];
		float initialSize;
		float finalSize;
		float initialColor[4];
		float finalColor[4];
		float lifetime;
		bool shiftColors = true;

		Particle();
		void initDraw(GLuint myShaderProgramIndex);
		void update();
		void start();
	private:
		float percent;
		float startTime;
		float velocity[3];
		
	};
}
#pragma once
