#include "FinishLine.h"

#include "Scene.h"
#include "GameObjectLib.h"
using namespace GameObjectSpace;


FinishLine::FinishLine(GameObject* _particleSystem) :GameObject()
{
	particleSystem = _particleSystem;
	((ParticleSystem*)particleSystem)->autoPlay = false;

}

void FinishLine::start()
{
	GameObject::start();
	startLap = Scene::timeUtil->time;

}

void FinishLine::update()
{
	GameObject::update();
	currentLap = Scene::timeUtil->time - startLap;
	string current = "Current Lap: ";
	currentLapText->text = (current + to_string(currentLap)).c_str();

	
}

void FinishLine::initDraw(GLuint myShaderProgramIndex)
{
	GameObject::initDraw(myShaderProgramIndex);
	
}

void FinishLine::OnTriggerEnter(Component* other)
{
	((ParticleSystem*)particleSystem)->playOnce();
	saveLap();
}

void FinishLine::saveLap()
{
	
	if (currentLap < 10)
		return;
	if (currentLap < bestLap  || bestLap < 0)
		bestLap = currentLap;
	cout << "current: " << currentLap << endl;
	cout << "bestLap " << bestLap << endl;
	string current = "Best Lap: ";
	bestLapText->text = (current + to_string(bestLap)).c_str();
	startLap = Scene::timeUtil->time;

}