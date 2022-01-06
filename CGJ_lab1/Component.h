#pragma once
namespace GameObjectSpace {
	class GameObject;

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
		virtual int getTextureMode() {
			return 0;
		};
	};

}
