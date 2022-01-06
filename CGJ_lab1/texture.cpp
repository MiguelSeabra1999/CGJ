#include "texture.h"

using namespace GameObjectSpace;

Texture::Texture(const char * texName, BlendType t, int * texMode_uniformId) {
	Texture::texName = _strdup(texName);
	Texture::blendType = t;
	Texture::texMode_uniformId = texMode_uniformId;
	init();

}

void Texture::init(){
	glGenTextures(1, &textureId);
	Texture2D_Loader(&textureId, texName, 0);


}

void Texture::update() {
	//SetActiveTex();
	//glActiveTexture(activeTex);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glUniform1i(*texMode_uniformId, (GLint)blendType);
}

void Texture::SetActiveTex() {
	if (activeTex == -1) {
		glGetIntegerv(GL_ACTIVE_TEXTURE, &activeTex);
	}
}