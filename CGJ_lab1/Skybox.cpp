#include "Skybox.h"
#include "ComponentLib.h"
using namespace GameObjectSpace;



Skybox::Skybox() :GameObject()
{
	GameObject::isSkybox = true;
	cubeMap_loc = glGetUniformLocation(shaderProgramIndex, "cubeMap");
}
void Skybox::initDraw(GLuint myShaderProgramIndex)
{
	GameObject::initDraw(myShaderProgramIndex);
	MyMesh amesh;

	amesh = createCube();

	GameObject::initMaterial();
	amesh.mat = *material;
	myMeshes.push_back(amesh);

}
void Skybox::BindTexture()
{
	GameObject::BindTexture();
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *(GameObject::textureIds[textureId]));

}
/**/
void Skybox::draw(bool reversed)
{
	//cubeMap_loc = glGetUniformLocation(shaderProgramIndex, "cubeMap");
//	glUniform1i(cubeMap_loc, 0);
/** /	PrepareShader();
	//GameObject::draw();
	BindTexture();*/
	cubeMap_loc = glGetUniformLocation(shaderProgramIndex, "cubeMap");
	glUniform1i(cubeMap_loc, 4);

	//it won't write anything to the zbuffer; all subsequently drawn scenery to be in front of the sky box. 
	glDepthMask(GL_FALSE);
	glFrontFace(GL_CW); // set clockwise vertex order to mean the front
	GameObject::draw(reversed);
	/** /pushMatrix(MODEL);
	pushMatrix(VIEW);  //se quiser anular a translação

	//  Fica mais realista se não anular a translação da câmara 
	// Cancel the translation movement of the camera - de acordo com o tutorial do Antons
	mMatrix[VIEW][12] = 0.0f;
	mMatrix[VIEW][13] = 0.0f;
	mMatrix[VIEW][14] = 0.0f;

	scale(MODEL, 200.0f, 200.0f, 200.0f);


	// send matrices to OGL
	glUniformMatrix4fv(model_uniformId, 1, GL_FALSE, mMatrix[MODEL]); //Transformação de modelação do cubo unitário para o "Big Cube"
	computeDerivedMatrix(PROJ_VIEW_MODEL);
	glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);

	glBindVertexArray(myMeshes[0].vao);
	glDrawElements(myMeshes[0].type, myMeshes[0].numIndexes, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	popMatrix(MODEL);
	popMatrix(VIEW);*/

	glFrontFace(GL_CCW); // restore counter clockwise vertex order to mean the front
	glDepthMask(GL_TRUE);
}

/**/