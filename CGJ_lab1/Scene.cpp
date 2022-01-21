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
	GameObject::n_lights = 0;
	for (int i = 0; i < count; i++)
	{
		(*gameObjects[i]).initDraw(shaderIndex);
		(*gameObjects[i]).start();
		if ((*gameObjects[i]).GetLight())
			GameObject::n_lights++;
	}

}


void Scene::initUI(GLint shaderID)
{
	
	
	int count = uiElements.size();
	for (int i = 0; i < count; i++)
	{
		//cout << "initialized ui draw" << endl;
		(*uiElements[i]).initDraw(shaderID);
		(*uiElements[i]).start();
	}

}

void Scene::updateAndDraw()
{
	if(!paused)
		physicsEngine->update();
	int count = gameObjects.size();
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
	glDepthMask(GL_TRUE);
	if (!paused)
	{
		destroyQueuedGameObjects();
		createQueuedGameObjects();
	}
}


void Scene::updateAndDrawUI()
{
	int count = uiElements.size();
	for (int i = 0; i < count; i++)
	{
		//cout << "updating ui elements" << endl;
		if ((*uiElements[i]).IsActive()) {
			//(*gameObjects[i]).opaqueDraw();
			//do something similar to text rendering 
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
