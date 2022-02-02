#include "CarScene.h"

using namespace GameObjectSpace;

void CarScene::loadTextures()
{
	GameObject::initTexture("lightwood.tga"); // indexTexture = 0
	GameObject::initTexture("plastic.jpg");   // indexTexture = 1
	GameObject::initTexture("butter.jpg");    // indexTexture = 2
	GameObject::initTexture("Grass2.jpg");    // indexTexture = 3
	GameObject::initTexture("stripes.jpg");   // indexTexture = 4
	GameObject::initTexture("heart.png");   // indexTexture = 5
	GameObject::initTexture("sun.png");		// indexTexture = 6
	GameObject::initTexture("tex1.png");   // indexTexture = 7
	GameObject::initTexture("tex2.png");    // indexTexture = 8
	GameObject::initTexture("tex3.png");    // indexTexture = 9
	GameObject::initTexture("tex4.png");   // indexTexture = 10
	GameObject::initTexture("tex5.png");   // indexTexture = 11
	GameObject::initTexture("tex6.png");    // indexTexture = 12
	GameObject::initTexture("tex7.png");    // indexTexture = 13
	GameObject::initTexture("tex8.png");   // indexTexture = 14
	GameObject::initTexture("tex9.png");   // indexTexture = 15

	GameObject::initTexture("tree.png");   // indexTexture =  16
	GameObject::initTexture("legoNormalMap.jpg");   // indexTexture =  17
	GameObject::initTexture("noiseNormalMap.jpg");   // indexTexture =  18
	GameObject::initTexture("stripesNormal.png");   // indexTexture =  19
	GameObject::initCubeMapTexture();   // indexTexture = 20
	GameObject::initTexture("particle.png");   // indexTexture =  21


}

void CarScene::init(unsigned int _shaderIndex)
{
	Scene::init(_shaderIndex);
	//loadTextures();
	gameObjects.clear();


	Collider* col;
	AABB* aabb;
	RigidBody* rb;

	//##############################  Car  ###############################################
	PlayerCar* playerCar = new PlayerCar();
	playerCar->transform.setScale(.2, .2, .2);
	playerCar->transform.setPosition(0, .1, 0);
	aabb = new AABB(playerCar);
	playerCar->AddComponent(aabb);
	rb = new RigidBody(playerCar);
	//rb->damping = 0.04f;
	playerCar->AddComponent(rb);
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
	cube->transform.setLocalScale(1.4, .5, 1.6);
	cube->transform.setLocalPosition(.69, .725, 0);
	cube->transform.setParent(&(playerCar->transform));
	cube->reflective = 0.2f;
	
	cube->setColor(0.5f, 1.0f, 1.0f, 0.6f);
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
	/**/
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

	float mapSize = 33;
	loadMap();
	/**/
	cube = new Cube();
	cube->setResizable(mapSize, mapSize);
	cube->transform.setScale(1, 10, 1);
	cube->transform.setPosition(0, -5, 0);
	cube->setColor(1.0f, 1.0f, 1.0f, 1.0f);
	cube->reflective = 0.2f;
	cube->roughness = 10.0f;
	cube->textureId = 0;
	cube->secondTextureId = 4;
	gameObjects.push_back((GameObject*)cube);


	/**/
	//butter
	cube = new Cube();
	cube->transform.setScale(1, 1, 3);
	cube->transform.setPosition(0, 0, 3);

	cube->normalMapTextureId = 18;
	cube->setColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	aabb = new AABB(cube);
	

	cube->AddComponent(aabb);
	rb = new RigidBody(cube);
	rb->damping = 0.0003f;
	rb->setMass(0.1f);
	cube->AddComponent(rb);
	aabb->setDim(1.1, 1.1, 3.1);
	gameObjects.push_back((GameObject*)cube);
	gameObjects.push_back((GameObject*)aabb->cube);
	cube->textureId = 2;

	//Skybox
	Skybox* skybox = new Skybox();
	skybox->textureId = 20;
	skybox->transform.setScale(200, 200, 200);
	gameObjects.push_back((GameObject*)skybox);

	/** /
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
	/**/

	
	Orange* orange = new Orange(mapSize);
	orange->transform.setPosition(1, .5, 0);
	orange->setColor(1.0f, 0.75f, 0.1f, 0.5f);
	aabb = new AABB(orange);
	aabb->isTrigger = true;
	orange->AddComponent(aabb);
	gameObjects.push_back((GameObject*)orange);
	gameObjects.push_back((GameObject*)aabb->cube);
	aabb->setDim(1, 1, 1);

	spawnTrees(mapSize/2, 2, 100);


	//#################### Cameras ##############################
	FollowCamera* followCamera = new FollowCamera(&(player->transform), CamType_t::perspective_t, followCameraPerspectiveArguments, -0.1f, 0.1f);
	followCamera->SetLerp(false);
	followCamera->offset[0] = 0.1f;
	followCamera->offset[1] = 0.125f;
	//followCamera->SetDistances(0.2f, 0.2f);
	//followCamera->transform.setParent(&(playerCar->transform));
	cameras.push_back((Camera*)followCamera);


	FixedTopDownCamera* fixedCamera = new FixedTopDownCamera(positionTopDownCamera, CamType_t::perspective_t, fixedCameraPerspectiveArguments);
	//fixedCamera->transform.setParent(&(playerCar->transform));
	cameras.push_back((Camera*)fixedCamera);
	gameObjects.push_back((GameObject*)fixedCamera);

	currentCam = followCamera;

	//################## Lights ###############################
	LightSource* lightSource;
	/**/
	lightSource = new LightSource(LightType::global);
	lightSource->light->color[0] = 0.2f;
	lightSource->light->color[1] = 0.2f;
	lightSource->light->color[2] = 0.2f;
	gameObjects.push_back((GameObject*)lightSource);

	/** /
	LightSource* directional = new LightSource(LightType::directional);
	//balllight->lightType = LightType::directional;
	//balllight->light->type = (int)balllight->lightType;
	directional->light->color[0] = 1.0f;
	directional->light->color[1] = 1.0f;
	directional->light->color[2] = 1.0f;
	
	directional->setColor(1.0f, 1.0f, 1.0f, 1.0f);
	//balllight->transform.globalTransform.setPosition(20, 10 ,0);
	//balllight->transform.globalTransform.setScale(0.5f, 0.5f, 0.5f);
	directional->transform.setRotation(45, -90, 0);
	gameObjects.push_back((GameObject*)directional);

	/**/

	Model3D* moon = new Model3D("MOON.OBJ");
	moon->transform.setPosition(20, 20,1.0f);
	moon->transform.setRotation(0, 110, 0);
	moon->transform.setScale(.5f, .5f, .5f);
	moon->emissive[0] = 1.0f;
	moon->emissive[1] = 1.0f;
	moon->emissive[2] = 1.0f;
	gameObjects.push_back(moon);

	lightSource = new LightSource(LightType::directional);
	lightSource->light->color[0] = 1.0f;
	lightSource->light->color[1] = 1.0f;
	lightSource->light->color[2] = 1.0f;
	lightSource->light->color[3] = 1.0f;

	lightSource->transform.setRotation(-45, -90, 0);
	lightSource->transform.setPosition(20, 20, 0);
	gameObjects.push_back(lightSource);
	/** /ballLight = new BallLight();
	ballLight->transform.globalTransform.setPosition(20, 2, 2);
	ballLight->transform.globalTransform.setScale(0.5f, 0.5f, 0.5f);
	ballLight->speed = 0.0f;
	ballLight->setColor(1, 1, 1, 1);
	gameObjects.push_back((GameObject*)ballLight);
	/**/

	/**/
	BallLight* ballLight = new BallLight();
	ballLight->transform.globalTransform.setPosition(-1, 3, -1);
	ballLight->transform.globalTransform.setScale(0.5f,0.5f,0.5f);
	ballLight->light->linear = .2;
	ballLight->setColor(1,1,0,1);
	gameObjects.push_back((GameObject*)ballLight);
	/**/
	ballLight = new BallLight();
	ballLight->transform.globalTransform.setPosition(mapSize/3 ,1, 0);
	ballLight->transform.globalTransform.setScale(0.5f, 0.5f, 0.5f);
	ballLight->light->linear = .2;
	ballLight->setColor(1, 0, 1, 1);
	gameObjects.push_back((GameObject*)ballLight);

	ballLight = new BallLight();
	ballLight->transform.globalTransform.setPosition(-mapSize / 3, 1, 0);
	ballLight->transform.globalTransform.setScale(0.5f, 0.5f, 0.5f);
	ballLight->light->linear = .2;
	ballLight->setColor(0, 1, 1, 1);
	gameObjects.push_back((GameObject*)ballLight);

	ballLight = new BallLight();
	ballLight->transform.globalTransform.setPosition(0, 1, mapSize / 3);
	ballLight->transform.globalTransform.setScale(0.5f, 0.5f, 0.5f);
	ballLight->light->linear = .2;
	ballLight->setColor(1, 0, 0, 1);
	gameObjects.push_back((GameObject*)ballLight);

	ballLight = new BallLight();
	ballLight->transform.globalTransform.setPosition(0, 1, -mapSize / 3);
	ballLight->transform.globalTransform.setScale(0.5f, 0.5f, 0.5f);
	ballLight->light->linear = .2;
	ballLight->setColor(0, 1, 0, 1);
	gameObjects.push_back((GameObject*)ballLight);

	ballLight = new BallLight();
	ballLight->transform.globalTransform.setPosition(1,1, 1);
	ballLight->transform.globalTransform.setScale(0.5f, 0.5f, 0.5f);
	ballLight->light->linear = .2;
	ballLight->setColor(0, 0, 1, 1);
	gameObjects.push_back((GameObject*)ballLight);

	////////////////////////////////PARTICLE SYSTEM	/////////////////////////////
		/**/
	ParticleSystem* ps = new ParticleSystem();
	float speed = 7;

	ps->minInitialSpeed[0] = -1.0f * speed;
	ps->minInitialSpeed[1] = -1.0f * speed;
	ps->minInitialSpeed[2] = -1.0f * speed;
	ps->maxInitialSpeed[0] = speed;
	ps->maxInitialSpeed[1] = speed;
	ps->maxInitialSpeed[2] = speed;
	float gravForce = -9;
	ps->minAcceleration[0] = 0;
	ps->minAcceleration[1] = gravForce;
	ps->minAcceleration[2] = 0;
	ps->maxAcceleration[0] = 0;
	ps->maxAcceleration[1] = gravForce;
	ps->maxAcceleration[2] = 0;
	ps->minInitialSize = 0;
	ps->maxInitialSize = 0;
	ps->minFinalSize = 1;
	ps->maxFinalSize = 2;
	ps->initialColor[0] = 1;
	ps->initialColor[1] = 1;
	ps->initialColor[2] = 1;
	ps->initialColor[3] = 1;
	ps->finalColor[0] = 0;
	ps->finalColor[1] = 0;
	ps->finalColor[2] = 0;
	ps->finalColor[3] = 0;
	ps->minLifetime = 0.5f;
	ps->maxLifetime = 1.0f;
	ps->minTextureIndex = 21;
	ps->maxTextureIndex = 21;
	ps->minSpawnRate = 0.1f;
	ps->maxSpawnRate = 1;
	ps->minSpawnAmmount = 10;
	ps->maxSpawnAmmount = 100;
	ps->lifetime = -1;
	ps->transform.setPosition(0, 4, 0);
	gameObjects.push_back((GameObject*)ps);
	/**/

	/////////////////////////////////////UI/////////////////////////////////////////
	UserInterface* UI = new UserInterface();
	UI->transform.setPosition(0,0,0);

	Canvas* canvas = new Canvas(GetUIShader());
	canvas->SetWidth(50);
	canvas->SetHeight(53);
	//canvas->SetFullScreen(true);
	canvas->SetWindow(windowX, windowY);
	canvas->transform.setLocalPosition(25, 25, 0);
	canvas->setColor(0.0f, 0.0f, 0.0f, 0.6f);


	/**/Panel* pan = new Panel(canvas, 5.0f, 5, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.7f, 0);
	pan->setWidth(40);
	pan->setHeight(40);
	pan->setHeart(false);
	canvas->AddComponent(pan);/**/


	TextElement * textMesh = new TextElement(canvas, "Game Paused", 12.5, 47, 80.0f, 1.0, 0.0f, 0.0f, 1.0f);
	canvas->AddComponent(textMesh);

	textMesh = new TextElement(canvas, "Controls:", 20, 41, 50.0f, 5.0, 5.0f, 5.0f, 1.0f);
	canvas->AddComponent(textMesh);

	textMesh = new TextElement(canvas, "W,A,S,D - Movement", 16.0, 36.0f, 40.0f, 5.0, 5.0f, 5.0f, 0.7);
	canvas->AddComponent(textMesh);

	textMesh = new TextElement(canvas, "1,2,3,4,L,F - Cameras", 15.5f, 32.0f, 40.0f, 5.0, 5.0f, 5.0f, 0.7);
	canvas->AddComponent(textMesh);

	textMesh = new TextElement(canvas, "U - Guizmos", 20.0f, 28.0f, 40.0f, 5.0, 5.0f, 5.0f, 0.7);
	canvas->AddComponent(textMesh);

	textMesh = new TextElement(canvas, "I,O,P - Lights", 20.0f, 24.0f, 40.0f, 5.0, 5.0f, 5.0f, 0.7);
	canvas->AddComponent(textMesh);

	textMesh = new TextElement(canvas, "Q - FOG", 21.0f, 20.0f, 40.0f, 5.0, 5.0f, 5.0f, 0.7);
	canvas->AddComponent(textMesh);

	textMesh = new TextElement(canvas, "Space Bar - Handbreak", 15.0f, 16.0f, 40.0f, 5.0, 5.0f, 5.0f, 0.7);
	canvas->AddComponent(textMesh);


	canvas->transform.setParent(&(UI->transform));
	canvas->SetActive(false);
	pauseMenu = canvas;
	
	// owner, x, y, deprecated, deprecated, r, g, b, alpha, rotation 
	
	



	Canvas* canvas2 = new Canvas(GetUIShader());
	canvas2->SetWidth(80);
	canvas2->SetHeight(7);
	//canvas2->SetFullScreen(true);
	canvas->SetWindow(windowX, windowY);
	canvas2->transform.setLocalPosition(3, 90, 0);
	canvas2->setColor(1.0f, 1.0f, 1.0f, 0.0f);
	canvas2->transform.setParent(&(UI->transform));
	for (int j = 0; j < playerCar->hp; j++) {
		Panel* panel = new Panel(canvas2, j*6.2 , 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 180);
		panel->setWidth(6);
		panel->setHeight(7);
		panel->textureId = 5;
		panel->setHeart(true);
		canvas2->AddComponent(panel);
	}


	Flare* flare = new Flare(GetUIShader(), lightSource);
	flare->setFMaxSize(0.5);
	flare->setFScale(0.2);
	flare->SetActive(true);

	
	FlareElement* fe = new FlareElement((Canvas*)flare);
	fe->setFDistance(0);
	fe->setFSize(3);
	fe->setSimpleColor(1.0f,1.0f,1.0f,0.3f);
	fe->setTextureId(6);
	flare->AddComponent(fe);

	fe = new FlareElement((Canvas*)flare);
	fe->setFDistance(0.1);
	fe->setFSize(3);
	fe->setSimpleColor(1, 1, 1, 0.05);
	fe->setTextureId(7);
	flare->AddComponent(fe);

	fe = new FlareElement((Canvas*)flare);
	fe->setFDistance(0.1);
	fe->setFSize(2.5);
	fe->setSimpleColor(1, 1, 1, 0.05);
	fe->setTextureId(8);
	flare->AddComponent(fe);

	
	fe = new FlareElement((Canvas*)flare);
	fe->setFDistance(0.11);
	fe->setFSize(2.3);
	fe->setSimpleColor(1, 1, 1, 0.3);
	fe->setTextureId(9);
	flare->AddComponent(fe);


	fe = new FlareElement((Canvas*)flare);
	fe->setFDistance(0.12);
	fe->setFSize(2.5);
	fe->setSimpleColor(1, 1, 1, 0.1);
	fe->setTextureId(10);
	flare->AddComponent(fe);


	fe = new FlareElement((Canvas*)flare);
	fe->setFDistance(0.15);
	fe->setFSize(2.0);
	fe->setSimpleColor(1, 1, 1, 0.3);
	fe->setTextureId(11);
	flare->AddComponent(fe);


	fe = new FlareElement((Canvas*)flare);
	fe->setFDistance(0.16);
	fe->setFSize(1.5);
	fe->setSimpleColor(1, 1, 1, 0.3);
	fe->setTextureId(12);
	flare->AddComponent(fe);


	fe = new FlareElement((Canvas*)flare);
	fe->setFDistance(0.18);
	fe->setFSize(1);
	fe->setSimpleColor(1, 1, 1, 0.2);
	fe->setTextureId(13);
	flare->AddComponent(fe);


	fe = new FlareElement((Canvas*)flare);
	fe->setFDistance(0.2);
	fe->setFSize(2);
	fe->setSimpleColor(1, 1, 1, 0.3);
	fe->setTextureId(14);
	flare->AddComponent(fe);


	fe = new FlareElement((Canvas*)flare);
	fe->setFDistance(0.3);
	fe->setFSize(2);
	fe->setSimpleColor(1, 1, 1, 0.3);
	fe->setTextureId(15);
	flare->AddComponent(fe);

	uiElements.push_back(UI);
	uiElements.push_back(flare);
	
	for (GameObject* obj : gameObjects) {
		obj->updateCurrentScene(this);
	}
	for (GameObject* obj : uiElements) {
		obj->updateCurrentScene(this);
	}

	
	Scene::init(shaderIndex);
	Scene::initUI(GetUIShader()->getProgramIndex());

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
void CarScene::loadMap()
{


	float map[3072] = { 0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f,0.21568627450980393f,0.5803921568627451f,0.43137254901960786f };
	for(int i = 0; i < 32; i++)
	{
		for(int j = 0; j < 32; j++)
		{
			int index = (i  * 96 + j*3);
			if(map[index] == 1 && map[index + 1] == 0  && map[index + 2] == 0)
			{
				RoadLimit* cube = new RoadLimit();
				cube->transform.setPosition(i-16, 0.2, j-16);
				cube->setColor(1.0f, 0.5f, 0.5f,1.0f);
				cube->textureId = 19;
				cube->normalMapTextureId = 19;
				AABB* aabb = new AABB(cube);
				cube->AddComponent(aabb);

				gameObjects.push_back((GameObject*)cube);
				gameObjects.push_back((GameObject*)aabb->cube);
			}
		}
	}
}

void CarScene::spawnTrees(float mapBounds, float treeOffset, int n_trees)
{
	mapBounds = mapBounds * 100;
	treeOffset = treeOffset * 100;
	for(int i = 0; i < n_trees; i++)
	{
		float x, y;
		float rnd = randomRange(0, 100);
		if(rnd < 25)
		{
			x = randomRange(-mapBounds - treeOffset, -mapBounds);
			y = randomRange(-mapBounds - treeOffset, mapBounds + treeOffset);
		}
		else if (rnd < 50)
		{
			x = randomRange(mapBounds, mapBounds + treeOffset);
			y = randomRange(-mapBounds - treeOffset, mapBounds + treeOffset);
		}
		else if (rnd < 75)
		{
			y = randomRange(-mapBounds - treeOffset, -mapBounds);
			x = randomRange(-mapBounds - treeOffset, mapBounds + treeOffset);
		}
		else
		{
			y = randomRange(mapBounds, mapBounds + treeOffset);
			x = randomRange(-mapBounds - treeOffset, mapBounds + treeOffset);
		}
		x = x / 100;
		y = y / 100;
		Billboard* tree = new Billboard(true);
		float scale = randomRange(100, 400) / 50;
		tree->transform.setPosition(x, scale/2, y);
		tree->transform.setScale(scale, scale, scale);
		tree->textureId = 16;
		gameObjects.push_back((GameObject*)tree);
	}
}
/** /
void CarScene::restart()
{
	player->transform.globalTransform.setPosition(0,0.1f,0);
	player->rigidbody->setVelocitiesZero();
}
/**/
