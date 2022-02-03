#pragma once
#include "SmokeParticle.h"
#include "Scene.h"
using namespace GameObjectSpace;


SmokeParticle::SmokeParticle():GameObject()
{
	effectTime = effectTime + (float)randomRange((effectTime - effectTime_deviation) * 100.0f, (effectTime + effectTime_deviation) *100.0f) / 100.0f;
	scaleIncrease = scaleIncrease + (float)randomRange((scaleIncrease - scaleIncrease_deviation) * 100, (scaleIncrease + scaleIncrease_deviation) * 100) / 100.0f;
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
	castShadows = false;

}
void SmokeParticle::start()
{
	GameObject::start();
	startTime = Scene::timeUtil->time;
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
void SmokeParticle::update()
{
	GameObject::update();

	/**/

	float percent = (float)(Scene::timeUtil->time - startTime) / (float)effectTime;
	float percent2 = (float)(Scene::timeUtil->time - startTime) / ((float)effectTime*1.3f) ;
	percent = min(percent, 1.0f);
	float alpha = lerp(1.0f, 0.0f, percent2);

	lerp(transform.globalTransform.scale, startScale, finalScale, percent, 3);
	//cout << alpha << endl;
	//alpha = max(alpha, 0.1f);
	myMeshes[0].mat.diffuse[3] = alpha;
	curr++;
	if (percent2 >= 1)
	{
		destroy();
	}
	/**/
	//printVec(transform.localTransform.scale,3,"scale");
//	cout <<curr<<endl;
}

void SmokeParticle::initDraw(GLuint myShaderProgramIndex)
{
	GameObject::initDraw(myShaderProgramIndex);
	MyMesh amesh;
	amesh = createSphere(1.0f, 10);
	GameObject::initMaterial();

	amesh.mat = *material;
	myMeshes.push_back(amesh);
}
float SmokeParticle::randomizeScaleIncrease()
{
	return  (float)randomRange((scaleIncrease - scaleIncrease_deviation) * 100.0f, (scaleIncrease + scaleIncrease_deviation) * 100.0f) / 100.0f;
}

	


