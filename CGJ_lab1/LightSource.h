#pragma once
#include "GameObject.h"
namespace GameObjectSpace {
	enum class LightType {
		point,
		directional,
		spot,
		global
	};
	class LightSource : public GameObject
	{
	public:
		Light* light;
		LightType lightType;
		LightSource(LightType type)
		{
			GameObject::GameObject();
			light = new Light;
			lightType = type;
			switch(type)
			{
				case LightType::point:
					light->type = 0;
					break;
				case LightType::directional:
					light->type = 1;
					break;
				case LightType::spot:
					light->type = 2;
					break;
				case LightType::global:
					light->type = 3;
					break;
			}
			GameObject::lights.push_back(light);
			GameObject::n_lights += 1;


		}

		void start()
		{
			transform.globalTransform.pos[0] = light->position[0];
			transform.globalTransform.pos[1] = light->position[1];
			transform.globalTransform.pos[2] = light->position[2];
		}

		void update()
		{
			light->position[0] = transform.globalTransform.pos[0];
			light->position[1] = transform.globalTransform.pos[1];
			light->position[2] = transform.globalTransform.pos[2];

	


			if(lightType == LightType::directional || lightType == LightType::spot)
			{
				light->direction[0] = transform.globalTransform.forward[0];
				light->direction[1] = transform.globalTransform.forward[1];
				light->direction[2] = transform.globalTransform.forward[2];
			}

			GameObject::update();


		}

	};
}