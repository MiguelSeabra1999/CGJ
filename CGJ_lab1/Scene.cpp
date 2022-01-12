#include "Scene.h"



using namespace GameObjectSpace;


TimeUtil* Scene::timeUtil;


void Scene::init(GLuint _shaderIndex)
{
	Scene::timeUtil = new TimeUtil();
	Scene::timeUtil->init();
	shaderIndex = _shaderIndex;
	useGizmos = false;
	physicsEngine = new PhysicsEngine();
	int count = gameObjects.size();
	for (int i = 0; i < count; i++)
	{
		(*gameObjects[i]).initDraw(shaderIndex);
		(*gameObjects[i]).start();
	}
	count = transparentGameObjects.size();
	for (int i = 0; i < count; i++)
	{
		(*transparentGameObjects[i]).initDraw(shaderIndex);
		(*transparentGameObjects[i]).start();
	}
}


void Scene::updateAndDraw()
{

	physicsEngine->update();
	int count = gameObjects.size();
	for (int i = 0; i < count; i++)
	{
		(*gameObjects[i]).update();
		(*gameObjects[i]).opaqueDraw();
	}
	glDepthMask(GL_FALSE);

	count = gameObjects.size();
	for (int i = 0; i < count; i++)
	{
		(*gameObjects[i]).transparentDraw();
	}
	glDepthMask(GL_TRUE);
}
void Scene::sendLightsToShader()
{
	int count = gameObjects.size();
	for (int i = 0; i < count; i++)
	{
		(*gameObjects[i]).SendLightsToShader();
	}
	count = transparentGameObjects.size();
	for (int i = 0; i < count; i++)
	{
		(*transparentGameObjects[i]).SendLightsToShader();
	}
}

void Scene::changeMainCamera(unsigned char code) {}
void Scene::destroy()
{
	Collider::allColliders.clear();
	RigidBody::allRigidBodies.clear();
	GameObject::lights.clear();
	GameObject::n_lights = 0;
	gameObjects.clear();
}
void Scene::restart()
{
	destroy();
	init(shaderIndex);
}

