
#include "GameObjectLib.h"
// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>
// GLUT is the toolkit to interface with the OS
#include <GL/freeglut.h>
#include "PhysicsEngine.h"
#include "ComponentLib.h"
namespace GameObjectSpace
{
	
	class Scene
	{
	public:
		bool useGizmos;
		vector<GameObject*> gameObjects;
		vector<GameObject*> transparentGameObjects;
		GLuint shaderIndex;
		Camera* currentCam;
		PhysicsEngine* physicsEngine;

		virtual void init(GLuint _shaderIndex)
		{
			shaderIndex = _shaderIndex;
			useGizmos = false;
			physicsEngine = new PhysicsEngine();
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
			
			physicsEngine->update();
			int count = gameObjects.size();
			for (int i = 0; i < count; i++)
			{
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

		virtual void changeMainCamera(unsigned char code) {}
		void destroy()
		{
			Collider::allColliders.clear();
			RigidBody::allRigidBodies.clear();
			gameObjects.clear();
		}
		virtual void restart()
		{
			destroy();
			init(shaderIndex);
		}
	};
}