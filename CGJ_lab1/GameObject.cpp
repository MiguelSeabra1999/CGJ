#include "GameObject.h"
#include "Texture_Loader.h"
#include "Scene.h"
#include "LightSource.h"
using namespace GameObjectSpace;

vector<LightSource*> GameObject::lights{};
int GameObject::n_lights = 0;
vector<GLuint*> GameObject::textureIds{};

GameObject::GameObject()
{
	pvm_uniformId = 0;
	vm_uniformId = 0;
	normal_uniformId = 0;
	shaderProgramIndex = 0;
	material = new Material;
	n_lights = lights.size();
	transform.initZero();
	transform.setOwner(this);


}
Component* GameObject::GetComponent(const char* type)
{
	int n = components.size();
	for(int i = 0; i < n; i++)
	{
		if (components[i]->GetType() == type)
			return components[i];
	}
	return nullptr;
}

int GameObject::initTexture(const char* textureName)
{
	GLuint* id = new GLuint;
	glGenTextures(1, id);
	Texture2D_Loader(id, textureName, 0);
	GameObject::textureIds.push_back(id);
	return GameObject::textureIds.size()-1;
}
int GameObject::initCubeMapTexture()
{
	GLuint* id = new GLuint;
	glGenTextures(1, id);
	const char* filenames[] = { "posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg" };
	TextureCubeMap_Loader(id, filenames, 0);
	GameObject::textureIds.push_back(id);
	return GameObject::textureIds.size() - 1;
}


void GameObject::BindTexture()
{
	if (textureId != -1) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *(GameObject::textureIds[textureId]));
		if (secondTextureId != -1) {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, *(GameObject::textureIds[secondTextureId]));
		}
		if (normalMapTextureId != -1) {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, *(GameObject::textureIds[normalMapTextureId]));

		}
	}
	else {
		glBindTexture(GL_TEXTURE_2D, 0);
		if (normalMapTextureId != -1) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, *(GameObject::textureIds[normalMapTextureId]));

		}
	}



}

void GameObject::update()
{

	int n = components.size();
	for(int i = 0; i < n; i++)
	{
		components[i]->update();
	}
					
	//transform.updateLocalTransform();
	updateSons();
}
void GameObject::updateSons()
{
	int n_sons = transform.sons.size();

	for (int i = 0; i < n_sons; i++)
	{
		Transform* sonTransform = transform.sons.at(i);
		GameObject* sonObject = (GameObject*)(sonTransform->gameObject);
		sonObject->update();

	}
}
void GameObject::drawTransparentSons(bool reversed)
{
	
	int n_sons = transform.sons.size();
	for (int i = 0; i < n_sons; i++)
	{
		
		glDepthMask(GL_FALSE);
		Transform* sonTransform = transform.sons.at(i);
		GameObject* sonObject = (GameObject*)(sonTransform->gameObject);
		if (sonObject->diff[3] < 1)
		{
			
			//sonObject->SendLightsToShader();
			//sonObject->update();
			sonObject->transparentDraw(reversed);
		}
		glDepthMask(GL_TRUE);
	}
}
void GameObject::drawOpaqueSons(bool reversed)
{
	int n_sons = transform.sons.size();
	
	for (int i = 0; i < n_sons; i++)
	{
		Transform* sonTransform = transform.sons.at(i);
		GameObject* sonObject = (GameObject*)(sonTransform->gameObject);
		if(sonObject->diff[3] >= 1)
		{
			//sonObject->SendLightsToShader();
			//sonObject->update();
			sonObject->opaqueDraw(reversed);
		}
	}
	//glDepthMask(GL_FALSE);

	//glDepthMask(GL_TRUE);

}
void GameObjectSpace::GameObject::drawUISons(int st)
{
	int n_sons = transform.sons.size();

	for (int i = 0; i < n_sons; i++)
	{
		Transform* sonTransform = transform.sons.at(i);
		GameObject* sonObject = (GameObject*)(sonTransform->gameObject);
		sonObject->DrawUI(st);

	}
	//glDepthMask(GL_FALSE);

	//glDepthMask(GL_TRUE);
}



void GameObject::turnLightOfTypeOff(LightType t) {
	for (int j = 0; j < GameObject::lights.size(); j++) {
		LightSource* l2 = GameObject::lights[j];
		if (l2->lightType == t) {
			l2->on = !l2->on;
			if (l2->on) {
				GameObject::n_lights++;
				if (l2->lightType == LightType::point || l2->lightType == LightType::spot || l2->lightType == LightType::directional) {
					l2->emissive[0] = l2->oldColor[0];
					l2->emissive[1] = l2->oldColor[1];
					l2->emissive[2] = l2->oldColor[2];
					l2->GameObject::initMaterial();
				}
			}
			else {
				GameObject::n_lights--;
				if (l2->lightType == LightType::point || l2->lightType == LightType::spot || l2->lightType == LightType::directional) {
					l2->setOldColor(l2->material->emissive[0], l2->material->emissive[1], l2->material->emissive[2], l2->material->emissive[3]);
					l2->emissive[0] = 0.0f;
					l2->emissive[1] = 0.0f;
					l2->emissive[2] = 0.0f;
					l2->initMaterial();
				}
			}
		}
	}

};

void GameObject::SetActive(bool act) {
	int n_sons = transform.sons.size();
	isActive = act;

	for (Component* comp : components) {
		comp->setActive(act);
	}
	for (int i = 0; i < n_sons; i++)
	{
		Transform* sonTransform = transform.sons.at(i);
		GameObject* sonObject = (GameObject*)(sonTransform->gameObject);
		sonObject->SetActive(act);

	}
}


void GameObject::startAndInitDrawSons()
{
	int n_sons = transform.sons.size();

	for (int i = 0; i < n_sons; i++)
	{

		Transform* sonTransform = transform.sons.at(i);
		GameObject* sonObject = (GameObject*)(sonTransform->gameObject);
		sonObject->start();
		sonObject->initDraw(shaderProgramIndex);
	}

}
void GameObject::start() {  }

void GameObject::initDraw(GLuint myShaderProgramIndex)
{
	shaderProgramIndex = myShaderProgramIndex;
	startAndInitDrawSons();
	int n = components.size();
	for (int i = 0; i < n; i++)
	{
		components[i]->init();
	}
}

void GameObject:: opaqueDraw(bool reversed)
{
	
	if (diff[3] >= 1)
		draw(reversed);
	drawOpaqueSons(reversed);
}
void GameObject::transparentDraw(bool reversed)
{
	if (diff[3] < 1)
		draw(reversed);
	drawTransparentSons(reversed);
}


void GameObject::DrawUI(int st) {
	//updateTransforms();
	updateWindow(currentScene->windowX, currentScene->windowY);
	drawUISons(st);
}




void GameObject::draw(bool reversed)
{

	if (!IsActive())
		return;
//	glFrontFace(GL_CW); // set clockwise vertex order to mean the front

	if(reversed)
		glFrontFace(GL_CW);

	PrepareShader();
	int n_sons = transform.sons.size();

	if (textureId != -1)
		BindTexture();

	pushMatrix(MODEL);

	if (reversed) {
		float aux[3] = { 1, -1, 1 };
		scale(MODEL, aux);
	}

	updateTransforms();
	int myMeshesLen = myMeshes.size();
	for (int i = 0; i < myMeshesLen; i++)
	{
		sendMaterialToShader(i);
		// send matrices to OGL
		computeDerivedMatrix(PROJ_VIEW_MODEL);

		glUniformMatrix4fv(model_uniformId, 1, GL_FALSE, mMatrix[MODEL]);
		glUniformMatrix4fv(view_uniformId, 1, GL_FALSE, mMatrix[VIEW]);
		glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
		glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);



		computeNormalMatrix3x3();
		glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);

		//SendLightsToShader();

		// Render mesh
		glBindVertexArray(myMeshes[i].vao);


		glDrawElements(myMeshes[i].type, myMeshes[i].numIndexes, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	popMatrix(MODEL);
	if (reversed)
		glFrontFace(GL_CCW);
	//drawSons();
//	glFrontFace(GL_CCW); // restore counter clockwise vertex order to mean the front
}

void GameObject::PrepareShader()
{
	GLint billboard_uniformId = glGetUniformLocation(shaderProgramIndex, "isBillboard");
	GLint useNormalMap_uniformId = glGetUniformLocation(shaderProgramIndex, "useNormalMap");
	GLint isSkybox_uniformId = glGetUniformLocation(shaderProgramIndex, "isSkybox");

	pvm_uniformId = glGetUniformLocation(shaderProgramIndex, "m_pvm");
	vm_uniformId = glGetUniformLocation(shaderProgramIndex, "m_viewModel");
	model_uniformId = glGetUniformLocation(shaderProgramIndex, "m_model");
	normal_uniformId = glGetUniformLocation(shaderProgramIndex, "m_normal");
	view_uniformId = glGetUniformLocation(shaderProgramIndex, "m_view");
	useTexture_uniformId = glGetUniformLocation(shaderProgramIndex, "useTexture");
	useTexture_two_uniformId = glGetUniformLocation(shaderProgramIndex, "useTexture2");
	tex_loc = glGetUniformLocation(shaderProgramIndex, "texmap");
	tex_loc1 = glGetUniformLocation(shaderProgramIndex, "texmap1");
	normalMap_loc = glGetUniformLocation(shaderProgramIndex, "normalMap");

	GLint loc = 0;
	
	glUniform1i(billboard_uniformId, isBillboard);
	
	glUniform1i(isSkybox_uniformId, isSkybox);

	if (textureId == -1) {
		glUniform1i(tex_loc, 0);
		glUniform1i(useTexture_uniformId, false);
	}
	else {
		glUniform1i(tex_loc, 0);
		glUniform1i(useTexture_uniformId, true);
	}

	if (secondTextureId == -1) {
		glUniform1i(tex_loc1, 0);
		glUniform1i(useTexture_two_uniformId, false);
	}
	else {
		glUniform1i(tex_loc1, 1);
		glUniform1i(useTexture_two_uniformId, true);
	}
	if (normalMapTextureId == -1)
	{
		glUniform1i(normalMap_loc, 0);
		glUniform1i(useNormalMap_uniformId, false);
	}
	else
	{
		if (textureId == -1)
			glUniform1i(normalMap_loc, 0);
		else
			glUniform1i(normalMap_loc, 1);
		glUniform1i(useNormalMap_uniformId, true);
	}
}

void GameObject::updateTransforms() {

	/**/
	if (transform.parent != nullptr)
	{
		memcpy(mMatrix[MODEL], transform.parent->mModel, 16 * sizeof(float));
		float t[3];
		multVectors(t, transform.localTransform.pos, transform.parent->globalTransform.scale, 3);
		translate(MODEL, t);
	}
	else
	{
		translate(MODEL, transform.globalTransform.pos);
	}

	rotate(MODEL, transform.globalTransform.rot[0], 1, 0, 0);
	rotate(MODEL, transform.globalTransform.rot[1], 0, 1, 0);
	rotate(MODEL, transform.globalTransform.rot[2], 0, 0, 1);
	memcpy(transform.mModel, mMatrix[MODEL], 16 * sizeof(float));



	scale(MODEL, transform.globalTransform.scale);



	if (transform.parent != nullptr)
	{
		float t2[4] = { 0,0,0,1 };
		float result[4];
		multMatixTransposeByVector(result, mMatrix[MODEL], t2);
		transform.globalTransform.setPosition(result[0], result[1], result[2]);
	}
}

void GameObjectSpace::GameObject::updateCurrentScene(Scene* sc)
{
	currentScene = sc;
	int n_sons = transform.sons.size();

	for (int i = 0; i < n_sons; i++)
	{

		Transform* sonTransform = transform.sons.at(i);
		GameObject* sonObject = (GameObject*)(sonTransform->gameObject);
		sonObject->updateCurrentScene(sc);
	}
}


bool GameObject::GetLight() {
	return false;
}

/**/
void GameObject::SendLightsToShader()
{
	int i = 0;
	for (int j = 0; j < lights.size(); j++)
	{
		if (lights[j]->on == true) {
			sendLightToShader(i, j);
			i++;
		}
	}
	GLint loc = glGetUniformLocation(shaderProgramIndex, "n_lights");
	glUniform1i(loc, i);
}
/**/
void GameObject::initMaterial()
{

	memcpy(material->diffuse, diff, 4 * sizeof(float));
	memcpy(material->specular, spec, 4 * sizeof(float));
	memcpy(material->emissive, emissive, 4 * sizeof(float));
	material->shininess = shininess;
	material->roughness = roughness;
	material->reflective = reflective;
	int sizeMeshes = myMeshes.size();
	for (int i = 0; i < sizeMeshes; i++) {
		memcpy(myMeshes[i].mat.diffuse, diff, 4 * sizeof(float));
		memcpy(myMeshes[i].mat.specular, spec, 4 * sizeof(float));
		memcpy(myMeshes[i].mat.emissive, emissive, 4 * sizeof(float));
		myMeshes[i].mat.shininess = shininess;
	}
	//material->texCount = texcount;
}
void GameObject::setColor(float r, float g, float b, float alpha)
{
	diff[0] = amb[0] = r;
	diff[1] = amb[1] = g;
	diff[2] = amb[2] = b;
	diff[3] = amb[3] = alpha;
}

void GameObject::setOldColor(float r, float g, float b, float alpha)
{
	oldColor[0] = r;
	oldColor[1] = g;
	oldColor[2] = b;
	oldColor[3] = alpha;
}

void GameObject::sendMaterialToShader(int i)
{
	GLint loc;
	loc = glGetUniformLocation(shaderProgramIndex, "mat.ambient");
	glUniform4fv(loc, 1, myMeshes[i].mat.ambient);
	loc = glGetUniformLocation(shaderProgramIndex, "mat.diffuse");
	glUniform4fv(loc, 1, myMeshes[i].mat.diffuse);
	loc = glGetUniformLocation(shaderProgramIndex, "mat.emissive");
	glUniform4fv(loc, 1, myMeshes[i].mat.emissive);
	loc = glGetUniformLocation(shaderProgramIndex, "mat.specular");
	glUniform4fv(loc, 1, myMeshes[i].mat.specular);
	loc = glGetUniformLocation(shaderProgramIndex, "mat.shininess");
	glUniform1f(loc, myMeshes[i].mat.shininess);
	loc = glGetUniformLocation(shaderProgramIndex, "mat.roughness");
	glUniform1f(loc, myMeshes[i].mat.roughness);
	loc = glGetUniformLocation(shaderProgramIndex, "mat.reflective");
	glUniform1f(loc, myMeshes[i].mat.reflective);

}

void GameObject::sendLightToShader(int i, int j)
{
	GLint loc;

	loc = glGetUniformLocation(shaderProgramIndex,(const GLchar*) ("lights[" + to_string(i) + "].position").c_str());
	glUniform4fv(loc, 1, lights[j]->light->eye_coords_position);

	loc = glGetUniformLocation(shaderProgramIndex, (const GLchar*)("lights[" + to_string(i) + "].color").c_str());
	glUniform4fv(loc, 1, lights[j]->light->color);

	loc = glGetUniformLocation(shaderProgramIndex, (const GLchar*)("lights[" + to_string(i) + "].direction").c_str());
	glUniform4fv(loc, 1, lights[j]->light->eye_coords_direction);

	loc = glGetUniformLocation(shaderProgramIndex, (const GLchar*)("lights[" + to_string(i) + "].cos_angle").c_str());
	glUniform1f(loc, lights[j]->light->cos_angle);

	loc = glGetUniformLocation(shaderProgramIndex, (const GLchar*)("lights[" + to_string(i) + "].type").c_str());
	glUniform1i(loc, (int)lights[j]->lightType);

	loc = glGetUniformLocation(shaderProgramIndex, (const GLchar*)("lights[" + to_string(i) + "].constant").c_str());
	glUniform1f(loc, lights[j]->light->constant);

	loc = glGetUniformLocation(shaderProgramIndex, (const GLchar*)("lights[" + to_string(i) + "].linear").c_str());
	glUniform1f(loc, lights[j]->light->linear);

	loc = glGetUniformLocation(shaderProgramIndex, (const GLchar*)("lights[" + to_string(i) + "].quadratic").c_str());
	glUniform1f(loc, lights[j]->light->quadratic);


	
}

void GameObject::AddComponent(Component* comp)
{
	GameObject::components.push_back(comp);
}
void GameObject::destroy()
{
	currentScene->gameObjectsForDeletion.push_back(this);
}
void GameObject::reallyDestroy()//this is necessary because you cant remove an object from gameOjects during the update loop cause you would chage the vector while iterating it
{
	if (transform.parent != nullptr)
	{
		int n2 = transform.parent->sons.size();
		for (int j = 0; j < n2; j++)
		{
			if (transform.parent->sons[j] == &transform)
			{
				transform.parent->sons.erase(transform.parent->sons.begin() + j);
				break;
			}
		}
		return;
	}
	int n = currentScene->gameObjects.size();
	for(int i = 0; i < n;i++)
	{
		if(currentScene->gameObjects[i] == this)
		{
			currentScene->gameObjects.erase(currentScene->gameObjects.begin() + i);

			break;
		}
	}
}



