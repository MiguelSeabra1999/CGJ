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
#include "Rigidbody.h"
using namespace std;
extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

/// The normal matrix
extern float mNormal3x3[9];
class GameObject {
    public:
		Transform transform;
		vector<Component*> components;
	

		GameObject()
		{
			transform.initZero();
;
		}

        virtual void update()
		{
			int n = components.size();
			for(int i = 0; i < n; i++)
			{
				components[i]->update();
			}
					
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
		RigidBody* rigidbody;
		float velocity;
		float acceleration;
		float backAcceleration = 0.001;
		float forwardAcceleration = 0.003;
		float maxSpeed = 0.1;
		float friction = 0.005;
		PlayerCar()
		{
			GameObject::GameObject();
			inputDir[0] = 0;
			inputDir[1] = 0;
			
			/*rigidbody = new RigidBody(&(GameObject::transform));
			rigidbody->applyVelocity = false;
			GameObject::components.push_back(rigidbody);*/
		}
		void start()
		{

		}
		void update()
		{
			GameObject::update();


			velocity += acceleration;
			if(acceleration == 0)
			{
				if (velocity > 0)
				{
					velocity -= friction;
					if (velocity < 0)
						velocity = 0;
				}
				else if(velocity < 0)
				{
					velocity += friction;
					if (velocity > 0)
						velocity = 0;
				}
			}

			if (velocity > maxSpeed)
				velocity = maxSpeed;
			if (velocity < -maxSpeed)
				velocity = -maxSpeed;
		

			GameObject::transform.globalTransform.translate(-1 * transform.globalTransform.right[0] * velocity, 0, -1 * transform.globalTransform.right[2] * velocity);
			//cout <<   "" << -1 * transform.globalTransform.right[0] * velocity << "," << 0 <<  "," << -1 * transform.globalTransform.right[2] * velocity << " \n";
			//GameObject::transform.globalTransform.translate(inputDir[0]*speed, 0, 0);
			if(velocity >= 0)
				GameObject::transform.globalTransform.rotate(0,inputDir[1] * speed * 100,0);
			else
				GameObject::transform.globalTransform.rotate(0, -inputDir[1] * speed * 100, 0);
	
		}
		void initDraw(GLuint myShaderProgramIndex)
		{

		}
		void forward(bool state)
		{
			
			if (state)
			{
				acceleration += forwardAcceleration;
				//inputDir[0] -= 1;
			}

			else
			{
				acceleration -= forwardAcceleration;
				//inputDir[0] += 1;
			}

		}
		void backward(bool state)
		{
			if (state)
			{
				acceleration -= backAcceleration;
				//inputDir[0] += 1;
			}

			else
			{
				acceleration += backAcceleration;
				//inputDir[0] -= 1;
			}
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
class Orange: public GameObject
{
public:
	float radius = 1;
	float minStartSpeed = 0.00001;
	float maxStartSpeed = 0.00003;
	float acceleration = 0.0001;
	RigidBody* rigidbody;
	
	Orange()
	{
		GameObject::GameObject();
		
		rigidbody = new RigidBody(&transform);
		GameObject::components.push_back(rigidbody);
		//random rotation
		// random velocity
		rigidbody->setVelocity(transform.globalTransform.forward);
		multVectorConstant(rigidbody->velocity, rigidbody->velocity, maxStartSpeed);
		rigidbody->setAcceleration(transform.globalTransform.forward);
		multVectorConstant(rigidbody->acceleration, rigidbody->acceleration, acceleration);
		

	}
	void start()
	{
		GameObject::start();
	}
	void update()
	{
		GameObject::update();
		GameObject::transform.globalTransform.rotate(2, 5, 3);
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


		amesh = createSphere(radius, 3);
		memcpy(amesh.mat.diffuse, diff, 4 * sizeof(float));
		memcpy(amesh.mat.specular, spec, 4 * sizeof(float));
		memcpy(amesh.mat.emissive, emissive, 4 * sizeof(float));
		amesh.mat.shininess = shininess;
		amesh.mat.texCount = texcount;
		myMeshes.push_back(amesh);


	}

};

class Camera : public GameObject
{
public:
	float lookAt[9];
	Camera()
	{
		GameObject::GameObject();
		
	}

	void update()
	{
		//not calling GameObject::update since there is no need to perform a render step, however that means we can add compontents
		
	}
	virtual void SetCameraPosition(){}
	virtual void SetCameraLookAt() {}
};
class FollowCamera : public Camera
{
public:
	SimpleTransform* targetTransform;
	float horizontalDist = 3;
	float verticalDist = 3;
	
	FollowCamera(SimpleTransform* target)
	{
		Camera::Camera();
		targetTransform = target;
		SetCameraPosition();
		SetCameraLookAt();
		//set world up
		lookAt[6] = 0;
		lookAt[7] = 1;
		lookAt[8] = 0;
		
	}
	void update()
	{
		
		//not calling GameObject::update since there is no need to perform a render step, however that means we can add compontents
		SetCameraPosition();
		SetCameraLookAt();
	}
	void SetCameraPosition()
	{
		/*lookAt[0] = targetTransform->pos[0] + targetTransform->right[0] * horizontalDist;
		lookAt[1] = targetTransform->pos[1] + verticalDist;
		lookAt[2] = targetTransform->pos[2] + targetTransform->right[2] * horizontalDist;*/
		lookAt[0] = targetTransform->pos[0];
		lookAt[1] = targetTransform->pos[1] + 1;
		lookAt[2] = targetTransform->pos[2];
	}
	void SetCameraLookAt()
	{
		/*lookAt[3] = targetTransform->pos[3];
		lookAt[4] = targetTransform->pos[4] ;
		lookAt[5] = targetTransform->pos[5] ;*/
		lookAt[3] = 0;
		lookAt[4] = 0;
		lookAt[5] = 1;
	}
};