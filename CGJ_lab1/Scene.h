
#include "GameObjectLib.h"
// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>
// GLUT is the toolkit to interface with the OS
#include <GL/freeglut.h>
#include "PhysicsEngine.h"
#include "ComponentLib.h"
#include "TimeUtil.h"
#include "AVTmathLib.h"



namespace GameObjectSpace
{
	class Scene
	{
	public:
		PlayerCar* player;
		bool paused = false;
		bool useGizmos;
		bool restartScene = false;
		float windowX = 0.0f, windowY = 0.0f;
		vector<GameObject*> gameObjects;
		vector<GameObject*> uiElements;
		vector<GameObject*> gameObjectsForDeletion;//this is necessary because you cant remove an object from gameOjects during the update loop cause you would chage the vector while iterating it
		vector<GameObject*> gameObjectsForCreation;
		Canvas* pauseMenu = nullptr;
		Canvas* gameOverMenu = nullptr;
	
		GLuint shaderIndex;
		Camera* currentCam;
		Camera* secondCam;
		Camera* thirdCam;
		PhysicsEngine* physicsEngine;
		static TimeUtil* timeUtil;
		bool rearView = false;
		bool useShadows = false;
		bool gameOver = false;
		Material* shadowMaterial = new Material();

		virtual void init(unsigned int _shaderIndex);
		void initShadowMaterial();
		void initUI(unsigned int shaderID);
		void update();
		void draw(bool reversed);
		void updateAndDrawUI(int st);

		void sendLightsToShader();
		virtual void changeMainCamera(unsigned char code);
		void destroy();
		virtual void restart();
		void destroyQueuedGameObjects();
		void createQueuedGameObjects();

		void instatiate(GameObject* obj, float* pos);
		void SetUIShader(VSShaderLib * s) { UIShader = s; }
		void SetWindow(float x, float y) { windowX = x; windowY = y; }
		VSShaderLib * GetUIShader() { return UIShader; }
		virtual void loadTextures(){}
		void UpdateFlarePositions();

		void lightsStep();
		
	private:
		VSShaderLib * UIShader;

	
	};
}