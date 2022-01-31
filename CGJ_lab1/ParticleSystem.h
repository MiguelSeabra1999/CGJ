#pragma once
#pragma once
#include "GameObject.h"
#include "GameObjectLib.h"
namespace GameObjectSpace {
	class ParticleSystem : public GameObject
	{
	public:
		float minInitialSpeed[3];
		float maxInitialSpeed[3];
		float minAcceleration[3];
		float maxAcceleration[3];
		float minInitialSize;
		float maxInitialSize;
		float minFinalSize;
		float maxFinalSize;
		float initialColor[4];
		float finalColor[4];
		float minLifetime;
		float maxLifetime;
		int minTextureIndex;
		int maxTextureIndex;
		bool randomColor = true;
		bool shiftColors = true;
		float minSpawnRate;
		float maxSpawnRate;
		int minSpawnAmmount = 1;
		int maxSpawnAmmount = 1;
		float lifetime;
		ParticleSystem();
		void start();
		void update();
		void spawnParticle();
	private:
		float lastSpawnTime;
		float spawnTime;
		float startTime;

	};
}
