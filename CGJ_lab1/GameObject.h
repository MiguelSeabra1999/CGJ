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
#include "ComponentLib.h"
#include <ctime>
//.obj importer stuff
#include "assimp/Importer.hpp"	//OO version Header!
#include "assimp/scene.h"
#include "meshFromAssimp.h"
using namespace std;


extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

/// The normal matrix
extern float mNormal3x3[9];



namespace GameObjectSpace {
	class Component;
	class Scene;
	class LightSource;
	enum class LightType;
	class GameObject {
	public:
		Scene* currentScene = nullptr;
		Transform transform;
		vector<Component*> components;
		static vector<LightSource*> lights;
		static int n_lights;
		Material* material = nullptr;
		float oldColor[4] = { 0.0f };
		float amb[4] = { 0.2f, 0.15f, 0.1f, 1.0f };
		float diff[4] = { 0.8f, 0.6f, 0.4f, 1.0f };
		float spec[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
		float emissive[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		float shininess = 100.0f;
		float reflective = 0;
		float roughness = 0;
		int shaderIndex;
		static vector<GLuint*> textureIds;
		int textureId = -1;
		int secondTextureId = -1;
		int normalMapTextureId = -1;
		bool isBillboard = false;
		bool isSkybox = false;
		bool castShadows = true;

		string name = "GameObject";

		GameObject();
		Component* GetComponent(const char* type);
		static int initTexture(const char* textureName);
		static int initCubeMapTexture();
		virtual void update();
		virtual void start();
		virtual void initDraw(GLuint myShaderProgramIndex);
		virtual void draw(bool reversed);
		void draw();
		void PrepareShader();
		void RenderObject();
		void DrawShadow();
		void transparentDraw(bool reversed);
		void opaqueDraw(bool reversed);
		void initMaterial();
		void setColor(float r, float g, float b, float alpha);
		void setOldColor(float r, float g, float b, float alpha);
		void sendMaterialToShader(int i);
		void sendLightToShader(int i, int j);
		void SendLightsToShader();
		void updateSons();
		void drawOpaqueSons(bool reversed);
		void drawTransparentSons(bool reversed);
		void startAndInitDrawSons();
		void AddComponent(Component* comp);
		virtual void BindTexture();
		virtual void OnCollisionEnter(Component* other) {}
		static void turnLightOfTypeOff(LightType t);
		virtual bool GetLight();
		virtual void OnTriggerEnter(Component* other) {}
		void destroy();
		void reallyDestroy();//this is necessary because you cant remove an object from gameOjects during the update loop cause you would chage the vector while iterating it
		//void Instantiate(GameObject* obj, float* pos);
		virtual bool GetFullScreen() { return false; }
		virtual bool GetUI() { return false; }
		virtual void SetUI(bool u) { }
		virtual void DrawUI(int st);
		virtual void drawUISons(int st);
		virtual void SetWidth(float x) {};
		virtual void SetHeight(float x) {};
		virtual void SetActive(bool active);
		virtual bool IsActive() { return isActive; }
		//virtual void drawUISons();
		virtual vector<struct MyMesh>* getMyMeshes() { return &myMeshes; }
		void updateTransforms();
		void updateCurrentScene(Scene* sc);
		virtual void updateWindow(float x, float y){}
		virtual bool IsFlare() { return false; }
		virtual string GetType() { return "None"; }
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
		GLint normalMap_loc;
		bool isActive = true;

	};
}