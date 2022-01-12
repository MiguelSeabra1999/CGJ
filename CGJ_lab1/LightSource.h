#pragma once
#include "GameObject.h"
namespace GameObjectSpace {
	enum class LightType {
		point,
		directional,
		spot,
		global
	};
	struct Light
	{
		float position[4] = { 0,0,0,1 };
		float eye_coords_position[4] = { 0,0,0,0 };
		float color[4] = { 1,1,1,1 };
		float direction[4] = { 0,1,0,0 };
		float eye_coords_direction[4] = { 0,0,0,0 };
		float cos_angle = 0.5;//cos(angle) , in rads. Uses cosine to save on shader maths
		int type = 0; // 0-> point, 1 -> dir , 2 -> spot, 3 -> global
		//attenuation parameters
		float constant = 0;
		float linear = 0;
		float quadratic = 0;
	};
	class LightSource : public GameObject
	{
	public:
		bool on = true;
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
			GameObject::lights.push_back(this);
		}

		virtual void start()
		{

			if (transform.parent == nullptr)
			{
				light->position[0] = transform.globalTransform.pos[0];
				light->position[1] = transform.globalTransform.pos[1];
				light->position[2] = transform.globalTransform.pos[2];
			}
			else
			{
				float t[3] = { 0,0,0 };
				multVectors(t, transform.localTransform.pos, transform.parent->globalTransform.scale, 3);

				light->position[0] = transform.parent->globalTransform.pos[0] ;
				light->position[1] = transform.parent->globalTransform.pos[1] ;
				light->position[2] = transform.parent->globalTransform.pos[2] ;
			}

		}

		virtual void update()
		{
			GameObject::update();
			light->position[0] = transform.globalTransform.pos[0];
			light->position[1] = transform.globalTransform.pos[1];
			light->position[2] = transform.globalTransform.pos[2];	
		}
		void LightSource::initDraw(GLuint myShaderProgramIndex)
		{
			GameObject::initDraw(myShaderProgramIndex);
	

		}
		void setColor(float r, float g, float b, float alpha)
		{
			GameObject::setColor(r, g, b, alpha);
			light->color[0] = r;
			light->color[1] = g;
			light->color[2] = b;
		}

	};
}