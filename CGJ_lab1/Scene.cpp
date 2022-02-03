#include "Scene.h"



using namespace GameObjectSpace;


TimeUtil* Scene::timeUtil = new TimeUtil();

void Scene::initShadowMaterial()
{
	shadowMaterial->diffuse[0] = 0.0;
	shadowMaterial->diffuse[1] = 0.0;
	shadowMaterial->diffuse[2] = 0.0;
	shadowMaterial->diffuse[3] = 0.2f;

	shadowMaterial->ambient[0] = 0;
	shadowMaterial->ambient[1] = 0;
	shadowMaterial->ambient[2] = 0;
	shadowMaterial->ambient[3] = 0;

	shadowMaterial->specular[0] = 0;
	shadowMaterial->specular[1] = 0;
	shadowMaterial->specular[2] = 0;
	shadowMaterial->specular[3] = 0;

	shadowMaterial->emissive[0] = 0;
	shadowMaterial->emissive[1] = 0;
	shadowMaterial->emissive[2] = 0;
	shadowMaterial->emissive[3] = 0;
	shadowMaterial->shininess = 0;
	shadowMaterial->texCount = 0;
	shadowMaterial->roughness = 0;
	shadowMaterial->reflective = 0;
}

void GameObjectSpace::Scene::init(GLuint _shaderIndex)
{

	
	initShadowMaterial();
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

void Scene::update()
{
	if (paused)
		return;
	physicsEngine->update();
	int count = gameObjects.size();
	for (int i = 0; i < count; i++)
	{
			(*gameObjects[i]).update();

	}

}

void Scene::draw(bool reversed)
{

	lightsStep();
	int count = gameObjects.size();
	if (count == 0)
		return;

	if(!reversed && useShadows)
	{
		
		for (int i = 1; i < count; i++)
		{

			(*gameObjects[i]).DrawShadow();
		}
		
	
	}

	
	glDepthMask(GL_TRUE);

	for (int i = 1; i < count; i++)
	{

		(*gameObjects[i]).opaqueDraw(reversed);
	}
	
	glDepthMask(GL_FALSE);

	count = gameObjects.size();
	for (int i = 1; i < count; i++)
	{
		(*gameObjects[i]).transparentDraw(reversed);
	}
	if (!paused)
	{
		destroyQueuedGameObjects();
		createQueuedGameObjects();
	}
	UpdateFlarePositions();
	glDepthMask(GL_TRUE);
	
}


void Scene::updateAndDrawUI(int st)
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
			//glStencilFunc(GL_NEVER, 0x1, 0x1);
			//glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);

			(*uiElements[i]).DrawUI(st);
			(*uiElements[i]).update();
		}
	}
	destroyQueuedGameObjects();
	createQueuedGameObjects();
}


void Scene::UpdateFlarePositions() {

	int flarePos[2];
	int m_viewport[4];
	float lightScreenPos[3];
	glGetIntegerv(GL_VIEWPORT, m_viewport);


	computeDerivedMatrix(PROJ_VIEW_MODEL);  //pvm to be applied to lightPost. pvm is used in project function


	for (GameObject* el : uiElements) {
		if (el->IsFlare()) {
			Flare* flare = (Flare*)el;
			//memcpy(flare->m_pvm, mCompMatrix[PROJ_VIEW_MODEL], sizeof(float) * 16);
			if (!flare->lightSrc->on || !project(flare->lightSrc->light->position, lightScreenPos, m_viewport)) {
				//printf("Error in getting projected light in screen\n");  //Calculate the window Coordinates of the light position: the projected position of light on viewport
				flare->SetActive(false);
			}
			else if (flare->lightSrc->lightType != LightType::global) {
				//cout << "here" << endl;
				flare->flarePos[0] = (int)lightScreenPos[0];
				flare->flarePos[1] = (int)lightScreenPos[1];
				flare->SetActive(true);
			}
		}
	}
	// for elevery light except ambient


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

void Scene::lightsStep() {


	//Update light positions
	for (int i = 0; i < GameObject::lights.size(); i++)
	{
		if (GameObject::lights[i]->on) {
			multMatixTransposeByVector(GameObject::lights[i]->light->eye_coords_direction, mMatrix[VIEW], GameObject::lights[i]->light->direction);
			multMatixTransposeByVector(GameObject::lights[i]->light->eye_coords_position, mMatrix[VIEW], GameObject::lights[i]->light->position);

		}
	}

	sendLightsToShader();
}