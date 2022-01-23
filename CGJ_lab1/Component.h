#pragma once
#include "GameObject.h"
namespace GameObjectSpace {


	class Component
	{
	public:
		GameObject* owner;
		bool isActive = true;

		Component(){};
		Component(GameObject* owner) { Component::owner = owner; }

		virtual void update()
		{

		}

		virtual void setActive(bool act) {
			isActive = act;
		}

		virtual void init()
		{
		}
		virtual const char* GetType()
		{
			return "";
		}
	};

}