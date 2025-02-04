#pragma once
#pragma comment(lib, "DevIL.lib")
#pragma comment(lib, "ILU.lib")
// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>
// GLUT is the toolkit to interface with the OS
#include <GL/freeglut.h>
#include <IL/il.h>
// Use Very Simple Libs
#include "VSShaderlib.h"
#include "AVTmathLib.h"
#include "VertexAttrDef.h"
#include "geometry.h"
#include "avtFreeType.h"
#include "Texture.h"
#include "Texture_Loader.h"
//#include "ComponentLib.h"
#include "ComponentLib.h"
#include <ctime>
#include "Light.h"

using namespace std;


extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];
/// The normal matrix
extern float mNormal3x3[9];

namespace GameObjectSpace {
	class GameObject {
	public:
		long int currentTime;
		long int prevTime = 0;
		long int deltaTime = 0;
		Transform transform;
		vector<Component*> components;
		static vector<Light*> lights;
		static int n_lights;
		Material* material = nullptr;
		float amb[4] = { 0.2f, 0.15f, 0.1f, 1.0f };
		float diff[4] = { 0.8f, 0.6f, 0.4f, 1.0f };
		float spec[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
		float emissive[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float shininess = 100.0f;
		int texcount = 0;
		int texMode_uniformId;

		GameObject();
		virtual void update();
		virtual void start();
		virtual void initDraw(GLuint myShaderProgramIndex);
		void draw();
		void initMaterial();
		void setColor(float r, float g, float b, float alpha);
		void sendMaterialToShader(int i);
		void sendLightToShader(int i);
		void SendLightsToShader();
		void updateAndDrawSons();
		void startAndInitDrawSons();
		void AddComponent(Component* comp);

	protected:
		vector<struct MyMesh> myMeshes;
		GLint pvm_uniformId;
		GLint vm_uniformId;
		GLint normal_uniformId;
		GLuint shaderProgramIndex;
		GLint model_uniformId;
		GLint view_uniformId;
	};
}