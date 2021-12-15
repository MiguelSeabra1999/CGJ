#pragma once
#include "GameObject.h"

using namespace GameObjectSpace;

namespace CameraSpace {
	class Camera : public GameObject
	{
	public:
		float lookAt[9] = { 0 };
		Camera();
		void update();
		virtual void SetCameraPosition();
		virtual void SetCameraLookAt();
	};
}


