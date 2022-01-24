#pragma once
#include "GameObjectLib.h"
#include "GameObject.h"

namespace GameObjectSpace {

	class Canvas: public GameObject
	{
	public:
		float width = 0.0f, height = 0.0f;
		bool fullScreen = false;
		float rotation = 0.0f;
		float scale_x=1.0f, scale_y = 1.0f;
		bool isUI = false;
		vector<float*> meshScales;
		vector<float*> meshWidthHeight;
		vector<float*> meshPositions;
		vector<GLint*> meshTextures;
		vector<GLfloat*> meshRotations;
		float windowX = 0.0f, windowY = 0.0f;

		VSShaderLib * shader;
		Canvas():GameObject() {
			;
		}
		Canvas(VSShaderLib *shaderUI) :Canvas() {
		SetUIShader(shaderUI);
		}
		void SetUIGlobalPosition(float x, float y);
		void SetUILocalPosition(float x, float y);
		void initDraw(GLuint shader) override;
		void generateMesh(int i);
		void update();
		void SetScale(float x, float y);
		void DrawUI() override;
		void SetUI(bool u) override { isUI = u; }
		bool GetUI() override { return isUI;  }
		void SetUIShader(VSShaderLib* s) { shader = s; shaderIndex = s->getProgramIndex(); }
		bool GetFullScreen() override { return fullScreen; }
		void SetFullScreen(bool f) { fullScreen = f; }
		void SetWidth(float w) override {  width = w;  }
		void SetHeight(float h) override{ height = h; }
		void SetRotation(float r) { rotation = r; }
		void SetWindow(float x, float y) { windowX = x, windowY = y; }
		void updateWindow(float x, float y) override { SetWindow(x, y); }
		//private:
		//void start() override;
	};
}