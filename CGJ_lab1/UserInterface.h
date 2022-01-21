#pragma once
#include "GameObject.h"
namespace GameObjectSpace {
	class UserInterface : public GameObject
	{
	public:
		UserInterface();
		bool GetUI() override { return true; }


	};

}