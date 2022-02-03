#pragma once
#include "Particle.h"
#include "ComponentLib.h"
#include "Scene.h"
using namespace GameObjectSpace;

Particle::Particle() :Billboard(true)
{

}
void Particle::initDraw(GLuint myShaderProgramIndex)
{
	Billboard::initDraw(myShaderProgramIndex);

}
void Particle::start()
{
	Billboard::start();
	startTime = Scene::timeUtil->time;
	percent = 0;
	velocity[0] = initialSpeed[0];
	velocity[1] = initialSpeed[1];
	velocity[2] = initialSpeed[2];
}
void Particle::update()
{
	Billboard::update();
	percent = (Scene::timeUtil->time - startTime) / lifetime;
	if (shiftColors)
		lerp(myMeshes[0].mat.diffuse, initialColor, finalColor, percent, 4);
	else
		myMeshes[0].mat.diffuse[3] = lerp(initialColor[3],finalColor[3],percent);
	float size = lerp(initialSize, finalSize, percent);
	transform.setScale(size, size, size);

	float accelerationScaled[3];
	multVectorConstant(accelerationScaled,acceleration,Scene::timeUtil->deltaTime);
	
	addVectors(velocity, velocity, accelerationScaled, 3);
	
	float velocityScaled[3];
	multVectorConstant(velocityScaled, velocity, Scene::timeUtil->deltaTime);

	transform.globalTransform.translate(velocityScaled);

	if(percent >= 1 || transform.globalTransform.pos[1]<=0)
		destroy();
}

