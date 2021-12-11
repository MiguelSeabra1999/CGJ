// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>
// GLUT is the toolkit to interface with the OS
#include <GL/freeglut.h>
#include <IL/il.h>
// Use Very Simple Libs
#include "VSShaderlib.h"
#include "AVTmathLib.h"
#include "VertexAttrDef.h"
#include "geometry.h"
#include "avtFreeType.h"
#include "Transform.h"
using namespace std;
extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

/// The normal matrix
extern float mNormal3x3[9];
class GameObject {
    public:
		Transform transform;

		GameObject()
		{
			transform.initZero();
;
		}

        virtual void update()
		{
			transform.updateLocalTransform();
		}
        virtual void start(){}
        virtual void initDraw(GLuint myShaderProgramIndex)
		{
			shaderProgramIndex = myShaderProgramIndex;
		}
        void draw()
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

				//MoveToPlace
				//rotate(MODEL, 0, transform.globalTransform.rot);
				scale(MODEL, transform.globalTransform.scale);
				
				translate(MODEL, transform.globalTransform.pos);
				

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

    protected:
        vector<struct MyMesh> myMeshes;
		GLint pvm_uniformId;
		GLint vm_uniformId;
		GLint normal_uniformId;
		GLuint shaderProgramIndex;
};



class PlayerCar : public GameObject
{
	public:
		PlayerCar()
		{
			GameObject::GameObject();
		}
		void start()
		{

		}
		void update()
		{
			GameObject::update();
			GameObject::transform.globalTransform.translate(0, 0.1, 0);
		}
		void initDraw(GLuint myShaderProgramIndex)
		{
			GameObject::initDraw(myShaderProgramIndex);
			MyMesh amesh;
			float amb[] = { 0.2f, 0.15f, 0.1f, 1.0f };
			float diff[] = { 0.8f, 0.6f, 0.4f, 1.0f };
			float spec[] = { 0.8f, 0.8f, 0.8f, 1.0f };
			float emissive[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			float shininess = 100.0f;
			int texcount = 0;

			amesh = createCube();
			memcpy(amesh.mat.diffuse, diff, 4 * sizeof(float));
			memcpy(amesh.mat.specular, spec, 4 * sizeof(float));
			memcpy(amesh.mat.emissive, emissive, 4 * sizeof(float));
			amesh.mat.shininess = shininess;
			amesh.mat.texCount = texcount;
			myMeshes.push_back(amesh);



		}
};
class Wheel : public GameObject
{
public:
	Wheel()
	{
		GameObject::GameObject();
	}
	void start()
	{

	}
	void update()
	{
		GameObject::update();
	}
	void initDraw(GLuint myShaderProgramIndex)
	{
		GameObject::initDraw(myShaderProgramIndex);
		MyMesh amesh;
		float amb[] = { 0.2f, 0.15f, 0.1f, 1.0f };
		float diff[] = { 0.8f, 0.6f, 0.4f, 1.0f };
		float spec[] = { 0.8f, 0.8f, 0.8f, 1.0f };
		float emissive[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float shininess = 100.0f;
		int texcount = 0;


		amesh = createTorus(1, 2, 10, 10);
		memcpy(amesh.mat.diffuse, diff, 4 * sizeof(float));
		memcpy(amesh.mat.specular, spec, 4 * sizeof(float));
		memcpy(amesh.mat.emissive, emissive, 4 * sizeof(float));
		amesh.mat.shininess = shininess;
		amesh.mat.texCount = texcount;
		myMeshes.push_back(amesh);


	}
};