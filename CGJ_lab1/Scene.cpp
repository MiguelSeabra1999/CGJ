#include "Scene.h"



using namespace GameObjectSpace;


TimeUtil* Scene::timeUtil = new TimeUtil();


void GameObjectSpace::Scene::init(GLuint _shaderIndex)
{
	//Scene::timeUtil = new TimeUtil();
	Scene::timeUtil->init();
	shaderIndex = _shaderIndex;
	useGizmos = false;
	physicsEngine = new PhysicsEngine();
	int count = gameObjects.size();
	GameObject::n_lights = 0;
	for (int i = 0; i < count; i++)
	{
		(*gameObjects[i]).initDraw(shaderIndex);
		(*gameObjects[i]).start();
		if ((*gameObjects[i]).GetLight())
			GameObject::n_lights++;
	}
}

void Scene::initUI(unsigned int shaderID)
{


	int count = uiElements.size();
	for (int i = 0; i < count; i++)
	{
		(*uiElements[i]).initDraw(shaderID);
		(*uiElements[i]).start();
	}
}

void Scene::updateAndDraw()
{
	if(!paused)
		physicsEngine->update();
	int count = gameObjects.size();
	glDepthMask(GL_TRUE);
	for (int i = 0; i < count; i++)
	{
		if(!paused)
			(*gameObjects[i]).update();
		(*gameObjects[i]).opaqueDraw();
	}
	


	glDepthMask(GL_FALSE);
	count = gameObjects.size();
	for (int i = 0; i < count; i++)
	{
		(*gameObjects[i]).transparentDraw();
	}
	if (!paused)
	{
		destroyQueuedGameObjects();
		createQueuedGameObjects();
	}
}


void Scene::updateAndDrawUI()
{
	pauseMenu->SetActive(paused);
	int count = uiElements.size();
	for (int i = 0; i < count; i++)
	{
		if ((*uiElements[i]).IsActive()) {
			if ((*uiElements[i]).GetFullScreen()) {
				(*uiElements[i]).SetWidth(windowX);
				(*uiElements[i]).SetHeight(windowY);
			}
			(*uiElements[i]).DrawUI();
			(*uiElements[i]).update();
		}
	}
	destroyQueuedGameObjects();
	createQueuedGameObjects();
}




void Scene::destroyQueuedGameObjects()
{
	int n = gameObjectsForDeletion.size();
	for (int i = 0; i < n; i++)
	{
		gameObjectsForDeletion[i]->reallyDestroy();
	}
	gameObjectsForDeletion.clear();
}
void Scene::createQueuedGameObjects()
{
	int n = gameObjectsForCreation.size();
	for (int i = 0; i < n; i++)
	{
		gameObjects.push_back(gameObjectsForCreation[i]);
		gameObjectsForCreation[i]->initDraw(shaderIndex);
		gameObjectsForCreation[i]->start();
	}
	gameObjectsForCreation.clear();
}
void Scene::sendLightsToShader()
{
	int count = gameObjects.size();

	gameObjects[0]->SendLightsToShader();
	

}

void Scene::changeMainCamera(unsigned char code) {}
void Scene::destroy()
{
	Collider::allColliders.clear();
	//RigidBody::allRigidBodies.clear();
	GameObject::lights.clear();
	GameObject::n_lights = 0;
	gameObjects.clear();
}
void Scene::restart()
{
	//destroy();
	//init(shaderIndex);
	restartScene = true;
}
void Scene::instatiate(GameObject* obj, float* pos)
{
	obj->currentScene = this;
	obj->transform.globalTransform.pos[0] = pos[0];
	obj->transform.globalTransform.pos[1] = pos[1];
	obj->transform.globalTransform.pos[2] = pos[2];
	gameObjectsForCreation.push_back((GameObject*)obj);
}
