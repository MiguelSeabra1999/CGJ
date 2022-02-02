
#include "GameObjectLib.h"
// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>
// GLUT is the toolkit to interface with the OS
#include <GL/freeglut.h>
#include "PhysicsEngine.h"
#include "ComponentLib.h"
#include "TimeUtil.h"




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
	
		GLuint shaderIndex;
		Camera* currentCam;
		PhysicsEngine* physicsEngine;
		static TimeUtil* timeUtil;

		virtual void init(unsigned int _shaderIndex);
		void initUI(unsigned int shaderID);
		void update();
		void draw();
		void updateAndDrawUI();

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

	private:
		VSShaderLib * UIShader;

	
	};
}