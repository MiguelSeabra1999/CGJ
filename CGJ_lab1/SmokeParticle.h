#pragma once
#pragma once

#include "GameObject.h"


namespace GameObjectSpace {
	class SmokeParticle : public GameObject
	{
	public:
		float effectTime = 3.0f;
		int count = 20;
		int curr = 0;
		float finalScale[3] = {10,10,10};
		float startScale[3] = { 1,1,1 };
		float scaleIncrease = 1.5f;
		SmokeParticle()
		{
		
			setColor(1.0f, 1.0f, 1.0f, 1.0f);
			

		}
		void start()
		{
			GameObject::start();
			/**/
			transform.setScale(0.05f, 0.05f, 0.05f);
			finalScale[0] = transform.globalTransform.scale[0] * scaleIncrease;
			finalScale[1] = transform.globalTransform.scale[1] * scaleIncrease;
			finalScale[2] = transform.globalTransform.scale[2] * scaleIncrease;
			startScale[0] = transform.globalTransform.scale[0];
			startScale[1] = transform.globalTransform.scale[1];
			startScale[2] = transform.globalTransform.scale[2];
			/**/
		}
		void update() 
		{
			GameObject::update();
			
			/**/
			float percent = (float)curr / (float)count;
			percent = min(percent, 1.0f);
			float alpha = lerp(1.0f,0.0f,percent);
			lerp(transform.globalTransform.scale, startScale, finalScale, percent,3);
			cout << alpha << endl;
			alpha = max(alpha, 0.5f);
			myMeshes[0].mat.diffuse[3] = alpha;
			curr++;
			/**/
			//printVec(transform.localTransform.scale,3,"scale");
			cout <<curr<<endl;
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
		void SendLightsToShader()
		{
			cout << "d";
		}
	};

}
