#pragma once
#include "Camera.h"

namespace GameObjectSpace {
	class FollowCamera : public Camera
	{
	public:
		SimpleTransform* targetTransform;
		float horizontalDist = 3;
		float verticalDist = 1.5;

		FollowCamera(SimpleTransform* target);
		void update();
		void SetCameraPosition();
		void SetCameraLookAt();
	};
}
