#pragma once
#include "Camera.h"

namespace GameObjectSpace {
	class FixedTopDownCamera : public Camera
	{
	public:
		float center[3] = { 0.0f };
		FixedTopDownCamera(float x, float y, float z);
		void update();
		void SetCameraPosition();
		void SetCameraCenter(float x, float y, float z);
		void SetCameraLookAt();
	};
}
