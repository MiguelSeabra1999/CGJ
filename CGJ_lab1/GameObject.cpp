#include "GameObject.h"

using namespace GameObjectSpace;



GameObject::GameObject()
{
	pvm_uniformId = 0;
	vm_uniformId = 0;
	normal_uniformId = 0;
	shaderProgramIndex = 0;
	transform.initZero();

}

void GameObject::update()
{
	int n = components.size();
	for(int i = 0; i < n; i++)
	{
		components[i]->update();
	}
					
	transform.updateLocalTransform();
}
void GameObject::start(){}

void GameObject::initDraw(GLuint myShaderProgramIndex)
{
	shaderProgramIndex = myShaderProgramIndex;
}
void GameObject::draw()
{
	pvm_uniformId = glGetUniformLocation(shaderProgramIndex, "m_pvm");
	vm_uniformId = glGetUniformLocation(shaderProgramIndex, "m_viewModel");
	normal_uniformId = glGetUniformLocation(shaderProgramIndex, "m_normal");
		
	GLint loc;
	int myMeshesLen = myMeshes.size();
	for (int i = 0; i < myMeshesLen; i++)
	{
		// send the material
		loc = glGetUniformLocation(shaderProgramIndex, "mat.ambient");
		glUniform4fv(loc, 1, myMeshes[i].mat.ambient);
		loc = glGetUniformLocation(shaderProgramIndex, "mat.diffuse");
		glUniform4fv(loc, 1, myMeshes[i].mat.diffuse);
		loc = glGetUniformLocation(shaderProgramIndex, "mat.specular");
		glUniform4fv(loc, 1, myMeshes[i].mat.specular);
		loc = glGetUniformLocation(shaderProgramIndex, "mat.shininess");
		glUniform1f(loc, myMeshes[i].mat.shininess);
		pushMatrix(MODEL);



				

		if (transform.parent != nullptr)
		{
			translate(MODEL, transform.parent->globalTransform.pos);
					
			rotate(MODEL, transform.parent->globalTransform.rot[0], 1, 0, 0);
			rotate(MODEL, transform.parent->globalTransform.rot[1], 0, 1, 0);
			rotate(MODEL, transform.parent->globalTransform.rot[2], 0, 0, 1);

			float t[3];
			multVectors(t, transform.localTransform.pos, transform.parent->globalTransform.scale, 3);
			translate(MODEL, t );
		}else
		{
			translate(MODEL, transform.globalTransform.pos);
		}
				
		scale(MODEL, transform.globalTransform.scale);

		rotate(MODEL, transform.globalTransform.rot[0], 1, 0, 0);
		rotate(MODEL, transform.globalTransform.rot[1], 0, 1, 0);
		rotate(MODEL, transform.globalTransform.rot[2], 0, 0, 1);

		//scale(MODEL, transform.localTransform.scale);


					

		//translate(MODEL, transform.localTransform.pos);
				
				

		// send matrices to OGL
		computeDerivedMatrix(PROJ_VIEW_MODEL);
		glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
		glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
		computeNormalMatrix3x3();
		glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);

		// Render mesh
		glBindVertexArray(myMeshes[i].vao);

				
		glDrawElements(myMeshes[i].type, myMeshes[i].numIndexes, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		popMatrix(MODEL);
	}
}





