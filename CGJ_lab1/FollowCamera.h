#pragma once
#include "Camera.h"

namespace GameObjectSpace {
	class FollowCamera : public Camera
	{
	public:
		float horizontalDist = 3;
		float verticalDist = 1.5;
		float rad[3];
		bool playerMoving = false;
		float zeta = 0.0f;
		float threshhold = 0.0005f;

		float angularConstantForLerp = 30.0f;
		float angularConstantForBackWardsLerp = 20.0f;



		FollowCamera(Transform * parent);
		FollowCamera(Transform * parent, CamType_t t, float args[8]);
		void update();
		void SetCameraPosition();
		void SetCameraLookAt();
		float GetCameraRadius();
		void SetCameraRadius();
		void UpdateCameraPosition();
		void SetAngles();
		void UpdateAngles();
		void SetPlayerMoving(bool state);
		void SetZeta();
		void SetLerp(bool l) override { lerp = l; }
		//void SetFollow(bool state);
	};


}
