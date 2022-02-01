#pragma once
#include "Canvas.h"

inline double clamp(const double x, const double min, const double max) {
	return (x < min ? min : (x > max ? max : x));
}

inline int clampi(const int x, const int min, const int max) {
	return (x < min ? min : (x > max ? max : x));
}

namespace GameObjectSpace {
	class Flare: public Canvas{
	public:
		float           fScale = 0.0f;     // Scale factor for adjusting overall size of flare elements.
		float           fMaxSize = 0.0f;   // Max size of largest element, as proportion of screen width (0.0-1.0)
		float flarePos[2] = { 0.0f };
		LightSource* lightSrc = nullptr;
		float m_pvm[16] = { 0.0f };

		
		Flare(VSShaderLib* shaderUI) :Canvas() {
			SetUIShader(shaderUI);
		}
		Flare(VSShaderLib* shaderUI, LightSource* l) :Flare(shaderUI) {
			lightSrc = l;
		}
		void setFScale(float f) { fScale = f; }
		void setFMaxSize(float f) { fMaxSize = f; }
		//void generateMesh(int i) override;
		void DrawUI() override;
		void initDraw(GLuint shader) override;
		void render_flare(int lx, int ly, int* m_viewport);
		bool IsFlare() override { return true; }
		Transform* getTransform() {
			return &transform;
		}


		
	
	
	};
}