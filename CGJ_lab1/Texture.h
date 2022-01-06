#pragma once
#include "Component.h"
#include <GL/glew.h>
#include "Texture_Loader.h"
#include <iostream>
#include <sstream>
#include <string>




namespace GameObjectSpace
{
	enum class BlendType {
		none_t,
		modulate_multiply_t,
		modulate_subtract_t,
		modulate_add_t
	};
	class Texture :public Component
	{

	public:
		unsigned int textureId;
		int * texMode_uniformId;
		GLint activeTex = -1;
		BlendType blendType = BlendType::modulate_multiply_t;
		Texture(const char * texName, BlendType t, int * texMode_uniformId);
		char * texName;


		void update();
		void init();

		void SetActiveTex();

		int getTextureMode() override {
			return (int)blendType;
		} ;

		

	};
}