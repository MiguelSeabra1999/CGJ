#pragma once
#include "ComponentLib.h"
//#include "Panel.h"

namespace GameObjectSpace {
	class Heart : public Panel
	{

	public:
		Heart(GameObject* owner) :Panel(owner) {
			;
		};
		Heart(GameObject* owner, float x, float y, float scale_x, float scale_y, float r, float g, float b, float alpha, float rot) :Panel(owner, x, y, scale_x, scale_y, r, g, b, alpha, rot) {}
		bool isHeart() override {
			return true;
		}

	};

}
