#pragma once
#include "GameObject.h"
namespace GameObjectSpace {


	class Component
	{
	public:
		GameObject* owner;

		Component(GameObject* owner) { Component::owner = owner; }
		Component(){};

		virtual void update()
		{

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