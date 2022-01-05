
#include "GameObjectLib.h"
// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>
// GLUT is the toolkit to interface with the OS
#include <GL/freeglut.h>
using namespace GameObjectSpace;
class Scene
{
public:
	vector<GameObject*> gameObjects;
	vector<GameObject*> transparentGameObjects;
	
	Camera* currentCam;

	virtual void init(GLuint shaderIndex)
	{
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


	void updateAndDraw()
	{
		int count = gameObjects.size();
		for (int i = 0; i < count; i++)
		{
			
			//(*myGameObjects[i]).SendLightsToShader();
			(*gameObjects[i]).update();
			(*gameObjects[i]).draw();

		}
		glDepthMask(GL_FALSE);
		count = transparentGameObjects.size();
		for (int i = 0; i < count; i++)
		{
			//(*myTransparentGameObjects[i]).SendLightsToShader();
			(*transparentGameObjects[i]).update();
			(*transparentGameObjects[i]).draw();

		}
		glDepthMask(GL_TRUE);
	}
	void sendLightsToShader()
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

	virtual void changeMainCamera(unsigned char code){}

};