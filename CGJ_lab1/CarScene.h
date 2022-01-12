#pragma once
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

		
		void loadTextures();

		void init(GLuint shaderIndex);

		void changeMainCamera(unsigned char code);
		void loadMap();
		//void restart();

	};
}