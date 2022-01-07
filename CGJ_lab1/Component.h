#pragma once
#include "GameObject.h"
namespace GameObjectSpace {


	class Component
	{
	public:
		GameObject* owner;

		virtual void update()
		{

		}
		virtual void init()
		{
		}
	};

}