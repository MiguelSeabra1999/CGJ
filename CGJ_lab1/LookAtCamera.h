#pragma once
#include "ComponentLib.h"

namespace GameObjectSpace
{


	class LookAtCamera :public Component
	{

	public:
		bool cylindrical = false;
		LookAtCamera(GameObject* owner);
		const char* GetType();
		void update();
	};

}