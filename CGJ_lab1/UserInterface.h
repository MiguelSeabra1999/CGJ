#pragma once
#include "GameObjectLib.h"

namespace GameObjectSpace {

	class UserInterface : public GameObject
	{
	public:
		float width = 0.0f, height = 0.0f;
		VSShaderLib shader;
		UserInterface():GameObject() {
			;
		}
		UserInterface(VSShaderLib shader) :UserInterface() {
			SetUIShader(shader);
		}
		void SetUIGlobalPosition(float x, float y);
		void SetUILocalPosition(float x, float y);
		void initDraw(VSShaderLib shader);
		void SetUIShader(VSShaderLib s){ shader = s; }
		bool GetUI() override { return false; }
		//private:
		//void start() override;
	};
}