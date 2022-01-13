#pragma once
#pragma once

#include "GameObject.h"
#include "Scene.h"

namespace GameObjectSpace {
	class SmokeParticle : public GameObject
	{
	public:
		float effectTime = 3.0f;
		float effectTime_deviation = 2.5f;
		int count = 20;
		int curr = 0;
		float finalScale[3] = {10,10,10};
		float startScale[3] = { 1,1,1 };
		float scaleIncrease = 5.0f;
		float scaleIncrease_deviation = 3.0f;
		float startTime = 0;
		SmokeParticle()
		{
			effectTime = effectTime + (float)randomRange((effectTime - effectTime_deviation) * 100, (effectTime + effectTime_deviation) * 100) / 100.0f;
			scaleIncrease = scaleIncrease + (float)randomRange((scaleIncrease - scaleIncrease_deviation) * 100, (scaleIncrease + scaleIncrease_deviation) * 100) / 100.0f;
			setColor(1.0f, 1.0f, 1.0f, 1.0f);
			
			
		}
		void start()
		{
			GameObject::start();
			//startTime = Scene::timeUtil->time;
			/**/
			transform.setScale(0.01f, 0.01f, 0.01f);
			finalScale[0] = transform.globalTransform.scale[0] * randomizeScaleIncrease();
			finalScale[1] = transform.globalTransform.scale[1] * randomizeScaleIncrease();
			finalScale[2] = transform.globalTransform.scale[2] * randomizeScaleIncrease();
			startScale[0] = transform.globalTransform.scale[0];
			startScale[1] = transform.globalTransform.scale[1];
			startScale[2] = transform.globalTransform.scale[2];
			/**/
		}
		void update() 
		{
			GameObject::update();
			
			/**/
			
			//float percent = (float)(Scene::timeUtil->time - startTime) / (float)effectTime;
			float percent = min(0.0f, 1.0f);
			float alpha = lerp(1.0f,0.0f,percent);
			lerp(transform.globalTransform.scale, startScale, finalScale, percent,3);
			//cout << alpha << endl;
			alpha = max(alpha, 0.5f);
			myMeshes[0].mat.diffuse[3] = alpha;
			curr++;
			if(percent >= 1)
			{
				destroy();
			}
			/**/
			//printVec(transform.localTransform.scale,3,"scale");
		//	cout <<curr<<endl;
		}

		void initDraw(GLuint myShaderProgramIndex)
		{
			GameObject::initDraw(myShaderProgramIndex);
			MyMesh amesh;
			amesh = createSphere(1.0f, 10);
			GameObject::initMaterial();

			amesh.mat = *material;
			myMeshes.push_back(amesh);
		}
		float randomizeScaleIncrease()
		{
			return  (float)randomRange((scaleIncrease - scaleIncrease_deviation) * 100, (scaleIncrease + scaleIncrease_deviation) * 100) / 100.0f;
		}
	
	};

}
