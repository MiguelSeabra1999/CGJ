
#pragma once
#include "ParticleSystem.h"
#include "ComponentLib.h"
#include "Scene.h"
using namespace GameObjectSpace;

ParticleSystem::ParticleSystem() :GameObject()
{
	

}
void ParticleSystem::start()
{
	GameObject::start();
	spawnParticle();
	startTime = Scene::timeUtil->time;

}
void ParticleSystem::update()
{
	GameObject::update();
	if (lifetime > 0 && startTime + lifetime < Scene::timeUtil->time)
		destroy();
	if(lastSpawnTime  + spawnTime < Scene::timeUtil->time)
	{
		int spawnAmmount = randomRange(minSpawnAmmount, maxSpawnAmmount);
		for(int i = 0; i < spawnAmmount; i++)
		{
			spawnParticle();
		}
	}

}

void ParticleSystem::spawnParticle()
{
	
	lastSpawnTime = Scene::timeUtil->time;
	spawnTime = randomRangeFloat(minSpawnRate,maxSpawnRate);

	Particle* particle = new Particle();
	memcpy(particle->initialPosition, transform.globalTransform.pos, sizeof(float) * 3);
	randomRange(particle->initialSpeed, minInitialSpeed, maxInitialSpeed,3);
	randomRange(particle->acceleration, minAcceleration, maxAcceleration, 3);
	particle->initialSize = randomRangeFloat(minInitialSize, maxInitialSize);
	particle->finalSize = randomRangeFloat(minFinalSize, maxFinalSize);
	if(!randomColor)
	{
		memcpy(particle->initialColor, initialColor, sizeof(float) * 4);
		memcpy(particle->finalColor, finalColor, sizeof(float) * 4);
	}
	else
	{
		randomRange(particle->initialColor, 0, 1, 3);
		particle->initialColor[3] = 1;
		randomRange(particle->finalColor, 0, 1, 3);
		particle->finalColor[3] = 1;
	}
	particle->lifetime = randomRangeFloat(minLifetime, maxLifetime);
	particle->textureId = randomRangeFloat(minTextureIndex, maxTextureIndex);
	particle->shiftColors = shiftColors;
	
	currentScene->instatiate((GameObject*)particle, transform.globalTransform.pos);
}
