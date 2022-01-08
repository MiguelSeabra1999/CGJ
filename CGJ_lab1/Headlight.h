#pragma once
#include "LightSource.h"
namespace GameObjectSpace {
	class Headlight : public LightSource
	{
	public:
		GameObject* target;
		Headlight(GameObject* mTarget) : LightSource(LightType::spot)
		{
		//	LightSource::LightSource(LightType::spot);
			target = mTarget;

		}
		void start()
		{
			LightSource::start();

			LightSource::light->direction[0] = target->transform.globalTransform.right[0];
			LightSource::light->direction[1] = target->transform.globalTransform.right[1];
			LightSource::light->direction[2] = target->transform.globalTransform.right[2];
		}
		void update()
		{
			LightSource::update();
			LightSource::light->direction[0] = target->transform.globalTransform.right[0];
			LightSource::light->direction[1] = target->transform.globalTransform.right[1];
			LightSource::light->direction[2] = target->transform.globalTransform.right[2];
		}
		void initDraw(GLuint myShaderProgramIndex)
		{
			
			LightSource::initDraw(myShaderProgramIndex);
			MyMesh amesh;
			amesh = createTorus(0,.25, 10, 10);
			GameObject::initMaterial();
			material->emissive[0] = 1;
			material->emissive[1] = .9;
			material->emissive[2] = .2;
			amesh.mat = *material;
			myMeshes.push_back(amesh);


		}
	};
}