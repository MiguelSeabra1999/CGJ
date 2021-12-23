#pragma once
#include "LightSource.h"
namespace GameObjectSpace {
	class Headlight : public LightSource
	{
	public:
		GameObject* target;
		Headlight(GameObject* mTarget) : LightSource(LightType::spot)
		{
			LightSource::LightSource(LightType::spot);
			target = mTarget;

		}
		void start()
		{
			LightSource::start();
		}
		void update()
		{
			LightSource::update();
			LightSource::light->direction[0] = target->transform.globalTransform.right[0];
			LightSource::light->direction[1] = target->transform.globalTransform.right[1];
			LightSource::light->direction[2] = target->transform.globalTransform.right[2];
		}

	};
}