#pragma once
#include "Camera.h"

namespace GameObjectSpace {
	class FollowCamera : public Camera
	{
	public:
		float horizontalDist = 3;
		float verticalDist = 1.5;
		float rad[3];
		bool Astate = false;
		bool Dstate = false;
		float zeta = 0.0f;


		FollowCamera(Transform * parent);
		FollowCamera(Transform * parent, CamType_t t, float args[6]);
		void update();
		void SetCameraPosition();
		void SetCameraLookAt();
		float GetCameraRadius();
		void SetCameraRadius();
		void UpdateCameraPosition();
		void SetAngles();
		void UpdateAngles();
		void PlayerAKeyState(bool state);
		void PlayerDKeyState(bool state);
		void SetZeta();
	};


}
