#include "GameObject.h"

using namespace GameObjectSpace;

vector<Light*> GameObject::lights;
int GameObject::n_lights;

GameObject::GameObject()
{
	pvm_uniformId = 0;
	vm_uniformId = 0;
	normal_uniformId = 0;
	shaderProgramIndex = 0;
	transform.initZero();
	material = new Material;
}

void GameObject::update()
{
	prevTime = currentTime;
	//time_t now = time(nullptr);

	currentTime = static_cast<long int> (time(NULL));
	deltaTime = currentTime - prevTime;
	int mode = 0;
	//cout << currentTime << endl;


	int n = components.size();
	for(int i = 0; i < n; i++)
	{
		
		if(components[i]->getTextureMode()!=0)
			mode = components[i]->getTextureMode();
		
		components[i]->update();
	}	
	int texMode_uniformId = -1;
		
	texMode_uniformId = glGetUniformLocation(shaderProgramIndex, "texType");
	glUniform1i(texMode_uniformId, mode); //modulate Phong color with texel color
	cout << "MODE == " << mode << endl;
	
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
		sendMaterialToShader(i);


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
				

		// send matrices to OGL
		computeDerivedMatrix(PROJ_VIEW_MODEL);
		
		glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
		glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
		computeNormalMatrix3x3();
		glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);

		//SendLightsToShader();

		// Render mesh
		glBindVertexArray(myMeshes[i].vao);

				
		glDrawElements(myMeshes[i].type, myMeshes[i].numIndexes, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		popMatrix(MODEL);
	
	}

}

void GameObject::SendLightsToShader()
{
	for (int j = 0; j < n_lights; j++)
	{
		sendLightToShader(j);
	}
}

void GameObject::initMaterial()
{
	memcpy(material->diffuse, diff, 4 * sizeof(float));
	memcpy(material->specular, spec, 4 * sizeof(float));
	memcpy(material->emissive, emissive, 4 * sizeof(float));
	material->shininess = shininess;
	material->texCount = texcount;
}
void GameObject::setColor(float r, float g, float b, float alpha)
{
	diff[0] = amb[0] = r;
	diff[1] = amb[1] = g;
	diff[2] = amb[2] = b;
	diff[3] = amb[3] = alpha;

}

void GameObject::sendMaterialToShader(int i)
{
	GLint loc;
	loc = glGetUniformLocation(shaderProgramIndex, "mat.ambient");
	glUniform4fv(loc, 1, myMeshes[i].mat.ambient);
	loc = glGetUniformLocation(shaderProgramIndex, "mat.diffuse");
	glUniform4fv(loc, 1, myMeshes[i].mat.diffuse);
	loc = glGetUniformLocation(shaderProgramIndex, "mat.specular");
	glUniform4fv(loc, 1, myMeshes[i].mat.specular);
	loc = glGetUniformLocation(shaderProgramIndex, "mat.shininess");
	glUniform1f(loc, myMeshes[i].mat.shininess);

}

void GameObject::sendLightToShader(int i)
{
	GLint loc;

	loc = glGetUniformLocation(shaderProgramIndex,(const GLchar*) ("lights[" + to_string(i) + "].position").c_str());
	glUniform4fv(loc, 1, lights[i]->eye_coords_position);

	loc = glGetUniformLocation(shaderProgramIndex, (const GLchar*)("lights[" + to_string(i) + "].color").c_str());
	glUniform4fv(loc, 1, lights[i]->color);

	loc = glGetUniformLocation(shaderProgramIndex, (const GLchar*)("lights[" + to_string(i) + "].direction").c_str());
	glUniform4fv(loc, 1, lights[i]->eye_coords_direction);

	loc = glGetUniformLocation(shaderProgramIndex, (const GLchar*)("lights[" + to_string(i) + "].cos_angle").c_str());
	glUniform1f(loc, lights[i]->cos_angle);

	loc = glGetUniformLocation(shaderProgramIndex, (const GLchar*)("lights[" + to_string(i) + "].type").c_str());
	glUniform1i(loc, lights[i]->type);

	loc = glGetUniformLocation(shaderProgramIndex, (const GLchar*)("lights[" + to_string(i) + "].constant").c_str());
	glUniform1f(loc, lights[i]->constant);

	loc = glGetUniformLocation(shaderProgramIndex, (const GLchar*)("lights[" + to_string(i) + "].linear").c_str());
	glUniform1f(loc, lights[i]->linear);

	loc = glGetUniformLocation(shaderProgramIndex, (const GLchar*)("lights[" + to_string(i) + "].quadratic").c_str());
	glUniform1f(loc, lights[i]->quadratic);

	loc = glGetUniformLocation(shaderProgramIndex, "n_lights");
	glUniform1i(loc, n_lights);
	
}





