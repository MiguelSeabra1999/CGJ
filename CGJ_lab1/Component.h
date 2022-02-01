#pragma once
#include "GameObject.h"
namespace GameObjectSpace {


	class Component
	{
	public:
		GameObject* owner;
		bool isAct = true;

		Component(){};
		Component(GameObject* owner) { Component::owner = owner; }

		virtual void update()
		{

		}

		virtual void setActive(bool act) {
			isAct = act;
		}

		virtual void init()
		{
		}
		virtual const char* GetType()
		{
			return "";
		}
		virtual bool isFlareElement() { return false; }
		virtual bool isActive() { return isAct; }
	};

}