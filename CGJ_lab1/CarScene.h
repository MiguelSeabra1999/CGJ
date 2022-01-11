#include"Scene.h"
#include "Texture_Loader.h"
namespace GameObjectSpace
{
	class CarScene : public Scene
	{
	public:
		PlayerCar* player;
		vector<Camera*> cameras;
		// Camera constants and values for easy definition
		float WinX = 1024, WinY = 768;
		float positionTopDownCamera[3] = { 0.0f, 50.0f, 0.0f };
		float followCameraPerspectiveArguments[8] = {
			WinX, // window width
			WinY, // window height
			53.13f, // angle
			0.1f, //near 
			1000.0f, //far
		};

		float followCameraOrthoArguments[8] = {
			WinX, //window width
			WinY, // window height
			-2.0f, // left
			2.0f, // right
			-2.0f, // bottom
			2.0f, // top
			-10.0f, //near 
			10.0f, //far
		};

		float fixedCameraPerspectiveArguments[8] = {
			WinX, // window width
			WinY, // window height
			53.13f, // angle
			0.1f, //near 
			1000.0f, //far
		};

		float fixedCameraOrthoArguments[8] = {
			WinX, //window width
			WinY, // window height
			-30.0f, // left
			30.0f, // right
			-30.0f, // bottom
			30.0f, // top
			-150.0f, //near 
			150.0f, //far
		};

		void loadTextures()
		{
			GameObject::initTexture("lightwood.tga");
		}

		void init(GLuint shaderIndex)
		{
		
			loadTextures();
			LoadMap();

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
			playerCar->AddComponent(rb);
			player = playerCar;
			gameObjects.push_back((GameObject*)playerCar);
			gameObjects.push_back((GameObject*)aabb->cube);
			aabb->setDim(0.8, 1, 0.2);
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

			// ------ Wheels --------

			Wheel* wheel = new Wheel();
			wheel->transform.setLocalPosition(-0.5, 0, 1);
			wheel->transform.setRotation(90, 0, 0);
			wheel->transform.setLocalScale(0.3, 0.3, 0.3);
			wheel->transform.setParent(&(playerCar->transform));

			wheel = new Wheel();
			wheel->transform.setLocalPosition(-0.5, 0, -1);
			wheel->transform.setRotation(90, 0, 0);
			wheel->transform.setLocalScale(0.3, 0.3, 0.3);
			wheel->transform.setParent(&(playerCar->transform));


			wheel = new Wheel();
			wheel->transform.setLocalPosition(1.5, 0, 1);
			wheel->transform.setRotation(90, 0, 0);
			wheel->transform.setLocalScale(0.3, 0.3, 0.3);
			wheel->transform.setParent(&(playerCar->transform));

			wheel = new Wheel();
			wheel->transform.setLocalPosition(1.5, 0, -1);
			wheel->transform.setRotation(90, 0, 0);
			wheel->transform.setLocalScale(0.3, 0.3, 0.3);
			wheel->transform.setParent(&(playerCar->transform));
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
			cube->transform.setScale(mapSize, 1, mapSize);
			cube->transform.setPosition(0, -0.5, 0);
			cube->setColor(0.0f, 0.3f, 0.0f, 1.0f);
			gameObjects.push_back((GameObject*)cube);
			//butter
			cube = new Cube();
			cube->transform.setScale(1, 1, 3);
			cube->transform.setPosition(2, 0, 2);
			cube->setColor(0.0f, 0.3f, 1.0f, 1.0f);
			aabb = new AABB(cube);
			cube->AddComponent(aabb);
			aabb->setDim(1.1, 1.1, 3.1);
			gameObjects.push_back((GameObject*)cube);
			gameObjects.push_back((GameObject*)aabb->cube);


			cube = new Cube();
			cube->transform.setScale(mapSize, 5, 1);
			cube->transform.setPosition(0, 0, mapSize / 2);
			cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
			//aabb = new AABB();
			//cube->AddComponent(aabb);
			gameObjects.push_back((GameObject*)cube);
			//gameObjects.push_back((GameObject*)aabb->cube);

			cube = new Cube();
			cube->transform.setScale(mapSize, 5, 1);
			cube->transform.setPosition(0, 0, -mapSize / 2);
			cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
			//aabb = new AABB();
			//cube->AddComponent(aabb);
			gameObjects.push_back((GameObject*)cube);
			//gameObjects.push_back((GameObject*)aabb->cube);

			cube = new Cube();
			cube->transform.setScale(1, 5, mapSize);
			cube->transform.setPosition(mapSize / 2, 0, 0);
			cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
			//aabb = new AABB();
			//cube->AddComponent(aabb);
			gameObjects.push_back((GameObject*)cube);
			//gameObjects.push_back((GameObject*)aabb->cube);

			cube = new Cube();
			cube->transform.setScale(1, 5, mapSize);
			cube->transform.setPosition(-mapSize / 2, 0, 0);
			cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
			//aabb = new AABB();
			//cube->AddComponent(aabb);
			gameObjects.push_back((GameObject*)cube);
			//gameObjects.push_back((GameObject*)aabb->cube);

			Orange* orange = new Orange(mapSize);
			orange->transform.setPosition(1, .5, 0);
			orange->setColor(1,1,1, 0.5f);
		//	aabb = new AABB();
		//	orange->AddComponent(aabb);
			gameObjects.push_back((GameObject*)orange);
		//	gameObjects.push_back((GameObject*)aabb->cube);


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
		}

		void changeMainCamera(unsigned char code)
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

		void LoadMap()
		{
			GLuint* textureArray;
			Texture2D_Loader(textureArray, "map.png", 0)
			/** /
			ILuint ImgId = 0;
			ilGenImages(1, &ImgId);
			ilBindImage(ImgId);
			ilLoadImage("map.png");
			ILint width = ilGetInteger(IL_IMAGE_WIDTH);
			ILint height = ilGetInteger(IL_IMAGE_HEIGHT);
			BYTE* pixmap = new BYTE[width * height * 3];
			ilCopyPixels(0, 0, 0, width, height, 1, IL_PNG,
				IL_BYTE, pixmap);

			for(int h = 0; h < height; h++)
			{
				for(int w = 0; w < width; w++)
				{
					
					cout << (int)pixmap[(height * width + width) * 3 ] << ", ";
				}
				cout << endl;
			}
			ilBindImage(0);
			ilDeleteImage(ImgId);
			/**/
		}
	};
}