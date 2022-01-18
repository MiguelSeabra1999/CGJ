#pragma once
#include "ComponentLib.h"

namespace GameObjectSpace
{
	
	class TextElement :public Component
	{

	public:
		const char* text;
		float simpleColor[4] = { 0.0f };
		float position[3] = { 0.0f };
		string font;
		TextElement(GameObject* owner) :Component(owner) {
			;
		}
		TextElement(GameObject* owner, const char * t, float x, float y, float scale, float r, float g, float b):TextElement(owner) {
			setText(t);
			setPosition(x, y, scale);
			setSimpleColor(r, g, b);
		}

		void update() override;
		void init() override;
		const char* GetType() override { return "TextElement"; }
		void setText(const char* t) { text = t; }
		void setSimpleColor(float r, float g, float b) { simpleColor[0] = r, simpleColor[1] = g, simpleColor[0] = b; }
		void setPosition(float x, float y, float scale) { position[0] = x, position[1] = y, position[2] = scale; }
	};
}