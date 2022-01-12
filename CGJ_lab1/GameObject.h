#pragma once
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
	class Component;
	class Scene;
	class GameObject {
	public:
		Scene* currentScene = nullptr;
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
		float emissive[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		float shininess = 100.0f;
		int shaderIndex;
		static vector<GLuint*> textureIds;
		int textureId = -1;
		int secondTextureId = -1;

		GameObject();
		Component* GetComponent(const char* type);
		static int initTexture(const char* textureName);
		virtual void update();
		virtual void start();
		virtual void initDraw(GLuint myShaderProgramIndex);
		void draw();
		void transparentDraw();
		void opaqueDraw();
		void initMaterial();
		void setColor(float r, float g, float b, float alpha);
		void sendMaterialToShader(int i);
		void sendLightToShader(int i);
		void SendLightsToShader();
		void updateSons();
		void drawOpaqueSons();
		void drawTransparentSons();
		void startAndInitDrawSons();
		void AddComponent(Component* comp);
		void BindTexture();
		virtual void OnCollisionEnter(){}
		virtual void OnTriggerEnter() {}

	protected:
		vector<struct MyMesh> myMeshes;
		GLint pvm_uniformId;
		GLint vm_uniformId;
		GLint normal_uniformId;
		GLuint shaderProgramIndex;
		GLint model_uniformId;
		GLint view_uniformId;
		//GLuint textureID_uniformId;
		GLint useTexture_uniformId;
		GLint useTexture_two_uniformId;
		GLint tex_loc;
		GLint tex_loc1;

	};
}