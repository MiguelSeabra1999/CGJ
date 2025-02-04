#include"Scene.h"
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

		void init(GLuint shaderIndex)
		{
			Collider* col;
			//##############################  Car  ###############################################
			PlayerCar* playerCar = new PlayerCar();
			playerCar->transform.setScale(.2, .2, .2);
			playerCar->transform.setPosition(0, .1, 0);
			gameObjects.push_back((GameObject*)playerCar);
			player = playerCar;
			col = new Collider();
			playerCar->AddComponent(col);

			// ------- body --------

			Cube* cube;
			cube = new Cube();
			cube->transform.setLocalScale(3, .6, 1.7);
			cube->transform.setLocalPosition(.5, .2, 0);
			cube->transform.setParent(&(playerCar->transform));
			cube->setColor(1.0f, 0.0f, 0.0f, 0.1f);


			cube = new Cube();
			cube->transform.setLocalScale(1.4, .6, 1.7);
			cube->transform.setLocalPosition(.69, .775, 0);
			cube->transform.setParent(&(playerCar->transform));
			cube->setColor(1.0f, 0.0f, 0.0f, 0.1f);


			cube = new Cube();
			cube->transform.setLocalScale(.8, .8, 1.7);
			cube->transform.setLocalPosition(1.4, .5, 0);
			cube->transform.setRotation(0, 0, 45);
			cube->transform.setParent(&(playerCar->transform));
			cube->setColor(1.0f, 0.0f, 0.0f, 0.1f);

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

			cube = new Cube();
			cube->transform.setScale(mapSize, 5, 1);
			cube->transform.setPosition(0, 0, mapSize / 2);
			cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
			col = new Collider();
			cube->AddComponent(col);
			gameObjects.push_back((GameObject*)cube);

			cube = new Cube();
			cube->transform.setScale(mapSize, 5, 1);
			cube->transform.setPosition(0, 0, -mapSize / 2);
			cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
			col = new Collider();
			cube->AddComponent(col);
			gameObjects.push_back((GameObject*)cube);

			cube = new Cube();
			cube->transform.setScale(1, 5, mapSize);
			cube->transform.setPosition(mapSize / 2, 0, 0);
			cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
			col = new Collider();
			cube->AddComponent(col);
			gameObjects.push_back((GameObject*)cube);

			cube = new Cube();
			cube->transform.setScale(1, 5, mapSize);
			cube->transform.setPosition(-mapSize / 2, 0, 0);
			cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
			col = new Collider();
			cube->AddComponent(col);
			gameObjects.push_back((GameObject*)cube);

			Orange* orange = new Orange(mapSize);
			orange->transform.setPosition(1, .5, 0);
			col = new Collider();
			cube->AddComponent(col);
			gameObjects.push_back((GameObject*)orange);

			//#################### Cameras ##############################
			FollowCamera* followCamera = new FollowCamera(&(player->transform), CamType_t::perspective_t, followCameraPerspectiveArguments);
			followCamera->transform.setParent(&(playerCar->transform));

			cameras.push_back((Camera*)followCamera);
			gameObjects.push_back((GameObject*)followCamera);

			FixedTopDownCamera* fixedCamera = new FixedTopDownCamera(positionTopDownCamera, CamType_t::perspective_t, fixedCameraPerspectiveArguments);
			fixedCamera->transform.setParent(&(playerCar->transform));
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
	};
}