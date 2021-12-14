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
		//RigidBody* rigidbody;

		GameObject()
		{
			transform.initZero();
;
		}

        virtual void update()
		{
			/*if(rigidbody != nullptr)
				rigidbody->physicsUpdate();*/
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
			inputDir[0] = 0;
			inputDir[1] = 0;
		}
		void start()
		{

		}
		void update()
		{
			GameObject::update();
			GameObject::transform.globalTransform.translate(inputDir[0]*speed, 0, 0);
			GameObject::transform.globalTransform.rotate(0,inputDir[1] * speed * 100,0);
			//GameObject::transform.globalTransform.rotate(10,0,0);
		}
		void initDraw(GLuint myShaderProgramIndex)
		{
		}
		void forward(bool state)
		{
			cout << "press:" << state;
			if(state)
				inputDir[0] -= 1;
			else
				inputDir[0] += 1;
		}
		void backward(bool state)
		{
			if (state)
				inputDir[0] += 1;
			else
				inputDir[0] -= 1;
		}
		void left(bool state)
		{
			if (state)
				inputDir[1] += 1;
			else
				inputDir[1] -= 1;
		}
		void right(bool state)
		{
			if (state)
				inputDir[1] -= 1;
			else
				inputDir[1] += 1;
		}
	private:
		float inputDir[2];
		float speed = 0.01f;
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
		GameObject::transform.localTransform.rotate(0, 5, 0);
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
class Cube : public GameObject
{
public:
	Cube()
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


		amesh = createCube();
		memcpy(amesh.mat.diffuse, diff, 4 * sizeof(float));
		memcpy(amesh.mat.specular, spec, 4 * sizeof(float));
		memcpy(amesh.mat.emissive, emissive, 4 * sizeof(float));
		amesh.mat.shininess = shininess;
		amesh.mat.texCount = texcount;
		myMeshes.push_back(amesh);


	}
};