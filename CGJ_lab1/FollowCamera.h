#pragma once
#include "Camera.h"

using namespace CameraSpace;

namespace FollowCameraSpace {
	class FollowCamera : public Camera
	{
	public:
		SimpleTransform* targetTransform;
		float horizontalDist = 3;
		float verticalDist = 3;

		FollowCamera(SimpleTransform* target);
		void update();
		void SetCameraPosition();
		void SetCameraLookAt();
	};
}
