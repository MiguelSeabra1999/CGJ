#pragma once
#include "Camera.h"

namespace GameObjectSpace {
	class FixedTopDownCamera : public Camera
	{
	public:
		float center[3] = { 0.0f };
		FixedTopDownCamera(float pos[3]);
		FixedTopDownCamera(float pos[3], CamType_t t, float args[6]);
		void update();
		void SetCameraPosition();
		void SetCameraCenter(float pos[3]);
		void SetCameraLookAt();
	};
}
