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
		
		float lookAt[9] = { 0.0f };
		float alpha = 0.0f;
		float beta = 0.0f;
		float radius = 0.0f;
		Camera();
		Camera(CamType_t t, float args[6]);
		void update();
		virtual void SetCameraPosition();
		virtual void SetCameraLookAt();
		void SetCameraType(CamType_t t);
		void UpdateProjection();
		void SetProjArgs(float args[6]);
		bool GetMovingAttr();
		virtual float GetCameraRadius();
		virtual void SetCameraRadius();
		virtual void UpdateCameraPosition();

		virtual void SetPlayerMoving(bool state){}
		
		void ResetCamera() {
			alpha = 0.0f;
			beta = 0.0f;
		};

	protected:
		float projArgs[6] = { 53.13f, 1.3333f, 0.1f, 1000.0f, 0.0f, 0.0f };
		CamType_t myType = CamType_t::perspective_t;
		bool moving = false;
	};
	
}


