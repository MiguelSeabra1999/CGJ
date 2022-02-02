#pragma once
#include "ComponentLib.h"
//#include "Panel.h"

namespace GameObjectSpace
{
	class Panel;
	class TextElement :public Component
	{

	public:
		Panel* pan;
		const char* text;
		float simpleColor[4] = { 1.0f };
		float position[3] = { 0.0f };
		string font;
		float x = 0, y = 0, sc = 0;
		int stencilType = 0;

		TextElement(GameObject* owner) :Component(owner) {
			;
		}
		TextElement(GameObject* owner, const char * t, float x, float y, float scale, float r, float g, float b, float alpha):TextElement(owner) {
			setText(t);
			setPosition(x, y, scale);
			setSimpleColor(r, g, b, alpha);
		}
		void setPanel(Panel* p) { pan = p; };
		void update() override;
		void init() override;
		const char* GetType() override { return "TextElement"; }
		void setText(const char* t) { text = t; }
		void setSimpleColor(float r, float g, float b, float a) { simpleColor[0] = r, simpleColor[1] = g, simpleColor[2] = b;  simpleColor[3] = a;}
		void setPosition(float x, float y, float scale) { position[0] = x, position[1] = y, position[2] = scale; }
		void setActive(bool b);
		void Draw(int t);
		bool isTextElement() override { return true; }
		void setStencilType(int t) { stencilType = t;  }
	};
}