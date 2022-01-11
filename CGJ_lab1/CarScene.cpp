#include "CarScene.h"

using namespace GameObjectSpace;

void CarScene::loadTextures()
{
	GameObject::initTexture("lightwood.tga");
	GameObject::initTexture("plastic.jpg");
	GameObject::initTexture("butter.jpg");
	GameObject::initTexture("Grass2.jpg");
	GameObject::initTexture("stripes.jpg");



}

void CarScene::init(GLuint shaderIndex)
{

	loadTextures();


	Collider* col;
	AABB* aabb;
	//##############################  Car  ###############################################
	PlayerCar* playerCar = new PlayerCar();
	playerCar->transform.setScale(.2, .2, .2);
	playerCar->transform.setPosition(0, .1, 0);
	aabb = new AABB(playerCar);
	playerCar->AddComponent(aabb);
	player = playerCar;
	gameObjects.push_back((GameObject*)playerCar);
	gameObjects.push_back((GameObject*)aabb->cube);
	aabb->setDim(0.3, 0.45, 0.3);
	// ------- body --------
	//base
	Cube* cube;
	cube = new Cube();
	cube->transform.setLocalScale(3, .6, 1.7);
	cube->transform.setLocalPosition(.5, .2, 0);
	cube->transform.setParent(&(playerCar->transform));
	cube->setColor(1.0f, 0.0f, 0.0f, 1.0f);
	cube->textureId = 0;

	//roof
	cube = new Cube();
	cube->transform.setLocalScale(1.4, .1, 1.7);
	cube->transform.setLocalPosition(.69, 1.02, 0);
	cube->transform.setParent(&(playerCar->transform));
	cube->setColor(1.0f, 0.0f, 0.0f, 1.0f);
	cube->textureId = 0;


	//glass
	cube = new Cube();
	cube->transform.setLocalScale(1.4, .5, 1.7);
	cube->transform.setLocalPosition(.69, .725, 0);
	cube->transform.setParent(&(playerCar->transform));
	cube->setColor(0.5f, 0.5f, 0.8f, 0.4f);
	//back
	cube = new Cube();
	cube->transform.setLocalScale(.8, .8, 1.7);
	cube->transform.setLocalPosition(1.4, .5, 0);
	cube->transform.setRotation(0, 0, 45);
	cube->transform.setParent(&(playerCar->transform));
	cube->setColor(1.0f, 0.0f, 0.0f, 1.0f);
	cube->textureId = 0;


	// ------ Wheels --------

	Wheel* wheel = new Wheel();
	wheel->transform.setLocalPosition(-0.5, 0, 1);
	wheel->transform.setRotation(90, 0, 0);
	wheel->transform.setLocalScale(0.3, 0.3, 0.3);
	wheel->setColor(0.4f, 0.4f, 0.4f, 1.0f);
	wheel->transform.setParent(&(playerCar->transform));
	wheel->textureId = 1;

	wheel = new Wheel();
	wheel->transform.setLocalPosition(-0.5, 0, -1);
	wheel->transform.setRotation(90, 0, 0);
	wheel->transform.setLocalScale(0.3, 0.3, 0.3);
	wheel->setColor(0.4f, 0.4f, 0.4f, 1.0f);
	wheel->transform.setParent(&(playerCar->transform));
	wheel->textureId = 1;



	wheel = new Wheel();
	wheel->transform.setLocalPosition(1.5, 0, 1);
	wheel->transform.setRotation(90, 0, 0);
	wheel->transform.setLocalScale(0.3, 0.3, 0.3);
	wheel->setColor(0.4f, 0.4f, 0.4f, 1.0f);
	wheel->transform.setParent(&(playerCar->transform));
	wheel->textureId = 1;


	wheel = new Wheel();
	wheel->transform.setLocalPosition(1.5, 0, -1);
	wheel->transform.setRotation(90, 0, 0);
	wheel->transform.setLocalScale(0.3, 0.3, 0.3);
	wheel->setColor(0.4f, 0.4f, 0.4f, 1.0f);
	wheel->transform.setParent(&(playerCar->transform));
	wheel->textureId = 1;

	/**/
	// ------- Headlights ------
	Headlight* headlight = new Headlight(playerCar);
	headlight->light->color[0] = 1;
	headlight->light->color[1] = 0.9f;
	headlight->light->color[2] = 0.2f;
	headlight->light->linear = 1;
	headlight->light->cos_angle = .9f;
	headlight->transform.setRotation(0, 0, 90);
	headlight->transform.setLocalPosition(-1.1, .2, -.45);
	headlight->transform.setParent(&(playerCar->transform));


	headlight = new Headlight(playerCar);
	headlight->light->color[0] = 1;
	headlight->light->color[1] = 0.9f;
	headlight->light->color[2] = 0.2f;
	headlight->light->linear = 1;
	headlight->light->cos_angle = .9f;
	headlight->transform.setRotation(0, 0, 90);
	headlight->transform.setLocalPosition(-1.1, 0.2, .45);
	headlight->transform.setParent(&(playerCar->transform));
	/**/

	//########################### Map and Obstacles ##################################

	float mapSize = 30;
	cube = new Cube();
	cube->setResizable(mapSize, mapSize);
	//cube->transform.setScale(mapSize, 1, mapSize);
	cube->transform.setPosition(0, -0.5, 0);
	cube->setColor(1.0f, 1.0f, 1.0f, 1.0f);
	cube->textureId = 0;
	cube->secondTextureId = 4;
	gameObjects.push_back((GameObject*)cube);
	//butter
	cube = new Cube();
	cube->transform.setScale(1, 1, 3);
	cube->transform.setPosition(0, 0, 0);
	cube->setColor(1.0f, 1.0f, 1.0f, 1.0f);
	aabb = new AABB(cube);
	cube->AddComponent(aabb);
	aabb->setDim(1.1, 1.1, 3.1);
	gameObjects.push_back((GameObject*)cube);
	gameObjects.push_back((GameObject*)aabb->cube);
	cube->textureId = 2;


	cube = new Cube();
	cube->transform.setScale(mapSize, 5, 1);
	cube->transform.setPosition(0, 0, mapSize / 2);
	cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
	aabb = new AABB(cube);
	cube->AddComponent(aabb);
	gameObjects.push_back((GameObject*)cube);
	gameObjects.push_back((GameObject*)aabb->cube);
	aabb->setDim(mapSize + 0.1, 5.1, 1.1);

	cube = new Cube();
	cube->transform.setScale(mapSize, 5, 1);
	cube->transform.setPosition(0, 0, -mapSize / 2);
	cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
	aabb = new AABB(cube);
	cube->AddComponent(aabb);
	gameObjects.push_back((GameObject*)cube);
	gameObjects.push_back((GameObject*)aabb->cube);
	aabb->setDim(mapSize + 0.1, 5.1, 1.1);


	cube = new Cube();
	cube->transform.setScale(1, 5, mapSize);
	cube->transform.setPosition(mapSize / 2, 0, 0);
	cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
	aabb = new AABB(cube);
	cube->AddComponent(aabb);
	gameObjects.push_back((GameObject*)cube);
	gameObjects.push_back((GameObject*)aabb->cube);
	aabb->setDim(1.1, 5.1, mapSize + 0.1);

	cube = new Cube();
	cube->transform.setScale(1, 5, mapSize);
	cube->transform.setPosition(-mapSize / 2, 0, 0);
	cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
	aabb = new AABB(cube);
	cube->AddComponent(aabb);
	gameObjects.push_back((GameObject*)cube);
	gameObjects.push_back((GameObject*)aabb->cube);
	aabb->setDim(1.1, 5.1, mapSize + 0.1);

	Orange* orange = new Orange(mapSize);
	orange->transform.setPosition(1, .5, 0);
	orange->setColor(1, 1, 1, 0.5f);
	aabb = new AABB(orange);
	orange->AddComponent(aabb);
	gameObjects.push_back((GameObject*)orange);
	gameObjects.push_back((GameObject*)aabb->cube);
	aabb->setDim(1, 1, 1);



	//#################### Cameras ##############################
	FollowCamera* followCamera = new FollowCamera(&(player->transform), CamType_t::perspective_t, followCameraPerspectiveArguments);
	//followCamera->transform.setParent(&(playerCar->transform));
	cameras.push_back((Camera*)followCamera);


	FixedTopDownCamera* fixedCamera = new FixedTopDownCamera(positionTopDownCamera, CamType_t::perspective_t, fixedCameraPerspectiveArguments);
	//fixedCamera->transform.setParent(&(playerCar->transform));
	cameras.push_back((Camera*)fixedCamera);
	gameObjects.push_back((GameObject*)fixedCamera);

	currentCam = followCamera;

	//################## Lights ###############################
	LightSource* lightSource;
	lightSource = new LightSource(LightType::global);
	lightSource->light->color[0] = 0.1f;
	lightSource->light->color[1] = 0.1f;
	lightSource->light->color[2] = 0.1f;
	gameObjects.push_back((GameObject*)lightSource);

	/**/
	lightSource = new LightSource(LightType::directional);
	lightSource->light->color[0] = 0.4f;
	lightSource->light->color[1] = 0.4f;
	lightSource->light->color[2] = 0.4f;
	lightSource->transform.setRotation(0, -90, 0);
	gameObjects.push_back((GameObject*)lightSource);
	/**/
	lightSource = new LightSource(LightType::point);
	lightSource->light->color[0] = 0.5f;
	lightSource->light->color[1] = 0.09f;
	lightSource->light->color[2] = 0.9f;

	lightSource->transform.globalTransform.setPosition(0, 2, 0);
	lightSource->light->quadratic = .2;
	gameObjects.push_back((GameObject*)lightSource);
	/**/


	Scene::init(shaderIndex);

	for (GameObject* obj : gameObjects) {
		obj->currentScene = this;
	}
}

void CarScene::changeMainCamera(unsigned char code)
{
	Scene::changeMainCamera(code);
	switch (code)
	{
	case '1':
		currentCam = cameras[0];

		break;
	case '2':
		currentCam = cameras[0];

		break;
	case '3':
		currentCam = cameras[1];

		break;
	case '4':
		currentCam = cameras[1];

	}
}