#pragma once
#pragma once
#include "LightSource.h"
namespace GameObjectSpace {
	class BallLight : public LightSource
	{
	public:
		bool goingUp = false;
		float hoverAmmount = 0.2f;
		float speed = 0.001f;
		float startY = 0;
		BallLight() : LightSource(LightType::point)
		{
			reflective = 0.6f;

		}
		void start()
		{
			LightSource::start();
			startY = transform.globalTransform.pos[1];
			speed += randomRange(-100, 100) * 0.0001;
			//light->quadratic =0.5f;
			
		}
		void update()
		{
		
			if(goingUp)
			{
				transform.globalTransform.pos[1] += speed;
				//light->quadratic += speed;
				if(transform.globalTransform.pos[1] >= startY + hoverAmmount)
				{
					transform.globalTransform.pos[1] = startY + hoverAmmount;
					//light->quadratic = 1;
					goingUp = false;
				}
			}
			else
			{
				transform.globalTransform.pos[1] -= speed;
			//	light->quadratic -= speed;
				if (transform.globalTransform.pos[1] <= startY - hoverAmmount)
				{
					transform.globalTransform.pos[1] = startY - hoverAmmount;
					//light->quadratic = 0.1;
					goingUp = true;
				}
			}
			LightSource::update();
		}


		void initDraw(GLuint myShaderProgramIndex)
		{

			LightSource::initDraw(myShaderProgramIndex);
			MyMesh amesh;
			amesh = createSphere(0.7f,10);
			GameObject::initMaterial();
			material->emissive[0] = diff[0];
			material->emissive[1] = diff[1];
			material->emissive[2] = diff[2];
			amesh.mat = *material;
			myMeshes.push_back(amesh);


		}
	
	};
}