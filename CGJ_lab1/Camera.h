#pragma once
#include "GameObject.h"


namespace GameObjectSpace {
	enum class CamType_t {
		perspective_t,
		ortho_t,
	};
	class Camera : public GameObject
	{
	public:
		Camera();
		float lookAt[9] = { 0.0f };
		float alpha = 0.0f;
		float beta = 0.0f;
		float radius = 0.0f;
		bool follow = true;
		bool lerp = false;
		float multiplier = 1.0f;
		Camera(CamType_t t, float args[8]);
		void update();
		void draw();
		virtual void SetCameraPosition();
		virtual void SetCameraLookAt();
		void SetCameraType(CamType_t t);
		void UpdateProjection();
		void SetProjArgs(float args[8]);
		bool GetMovingAttr();
		virtual float GetCameraRadius();
		virtual void SetCameraRadius();
		virtual void UpdateCameraPosition();
		virtual void SetCameraCharacteristics(CamType_t t, float args[8], float w, float h);
		virtual void SetFollow(bool state) { follow = state; };
		virtual void SetLerp(bool l) {};
		void SetWidthHeightProj(float w, float h) {
			projArgs[0] = w;
			projArgs[1] = h;
		}

		void SetMuliplier(float m) {
			multiplier = m;
		}

		virtual void SetPlayerMoving(bool state){}
		
		void ResetCamera() {
			alpha = 0.0f;
			beta = 0.0f;
		};
		virtual bool GetLerp() {
			return lerp;
		}

	protected:
		float projArgs[8];
		CamType_t myType = CamType_t::perspective_t;
		bool moving = false;
	};
	
}


