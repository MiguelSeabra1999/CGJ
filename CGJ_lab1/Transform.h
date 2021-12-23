#include <iostream>
#include "AVTmathLib.h"

using namespace std;

class SimpleTransform
{
public:
	float pos[3];
	float rot[3];
	float scale[3];
	//reference vectors
	float right[4];
	float forward[4];
	float up[4];



	void setPosition(float x, float y, float z)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}

	void translate(float x, float y, float z)
	{
		pos[0] += x;
		pos[1] += y;
		pos[2] += z;
	}
	void setRotation(float x, float y, float z)
	{
		rot[0] = x;
		rot[1] = y;
		rot[2] = z;
		updateReferencePoints();
	}
	void rotate(float x, float y, float z)
	{
		rot[0] += x;
		rot[1] += y;
		rot[2] += z;
		ClampRotations();
		updateReferencePoints();
	}
	void setScale(float x, float y, float z)
	{
		scale[0] = x;
		scale[1] = y;
		scale[2] = z;
	}
	void applyScale(float x, float y, float z)
	{
		scale[0] += x;
		scale[1] += y;
		scale[2] += z;
	}

	void initZero()
	{
		setPosition(0, 0, 0);
		setRotation(0,0,0);
		setScale(1, 1, 1);
		updateReferencePoints();


		right[0] = 1;
		right[1] = 0;
		right[2] = 0;
		right[3] = 1;
		float rotationMatrix[16];

		genRotationMatrix_Y(rotationMatrix, 90);

		multMatixByVector(right, rotationMatrix, right);
		//cout << "|" << right[0] << "---" << right[1] << "---" << right[2] << "|\n";
	}

	float ClampAngle(float angle)
	{
		while(angle < 0 || angle >= 360)
		{
			if(angle < 0)
			{
				angle += 360;
			}
			else if(angle >= 360)
			{
				angle -= 360;
			}
		}
		return angle;
	}
	void ClampRotations()
	{
		rot[0] = ClampAngle(rot[0]);
		rot[1] = ClampAngle(rot[1]);
		rot[2] = ClampAngle(rot[2]);
	}


	/*
	*  Adds other to recipient
	*/
	void SumTransform( SimpleTransform* a, SimpleTransform* b)
	{ 
		pos[0] = a->pos[0] + b->pos[0];
		pos[1] = a->pos[1] + b->pos[1];
		pos[2] = a->pos[2] + b->pos[2];

		/*rot[0] = a->rot[0] + b->rot[0];
		rot[1] = a->rot[1] + b->rot[1];
		rot[2] = a->rot[2] + b->rot[2];
		ClampRotations();*/

		scale[0] = a->scale[0] * b->scale[0];
		scale[1] = a->scale[1] * b->scale[1];
		scale[2] = a->scale[2] * b->scale[2];
	}

	void updateReferencePoints()
	{
		right[0] = 1; 
		right[1] = 0; 
		right[2] = 0;
		right[3] = 1;
		forward[0] = 0; 
		forward[1] = 0;	
		forward[2] = 1;
		forward[3] = 1;
		up[0] = 0; 
		up[1] = 1; 
		up[2] = 0;
		up[3] = 1;

		float rotationMatrix[16];
		genRotationMatrix_X(rotationMatrix, rot[0]);
		multMatixByVector(right, rotationMatrix, right);
		genRotationMatrix_Y(rotationMatrix, rot[1]);
		multMatixByVector(right, rotationMatrix, right);
		genRotationMatrix_Z(rotationMatrix, rot[2]);
		multMatixByVector(right, rotationMatrix, right);

		genRotationMatrix_X(rotationMatrix, rot[0]);
		multMatixByVector(forward, rotationMatrix, forward);
		genRotationMatrix_Y(rotationMatrix, rot[1]);
		multMatixByVector(forward, rotationMatrix, forward);
		genRotationMatrix_Z(rotationMatrix, rot[2]);
		multMatixByVector(forward, rotationMatrix, forward);

		genRotationMatrix_X(rotationMatrix, rot[0]);
		multMatixByVector(up, rotationMatrix, up);
		genRotationMatrix_Y(rotationMatrix, rot[1]);
		multMatixByVector(up, rotationMatrix, up);
		genRotationMatrix_Z(rotationMatrix, rot[2]);
		multMatixByVector(up, rotationMatrix, up);
	}


};

class Transform
{
	public:
		Transform* parent = nullptr;
		Transform* son = nullptr;
		void* owner;
		SimpleTransform localTransform;
		SimpleTransform globalTransform;

		void initZero()
		{
			localTransform.initZero();
			globalTransform.initZero();
		}

		void setParent(Transform* newParent)
		{
			parent = newParent;
			newParent->son = this;

			updateLocalTransform();
		
		}

		void setOwner(void * myOwner) {
			owner = myOwner;
		}

		void updateLocalTransform()
		{

			if(parent != nullptr)
				globalTransform.SumTransform(&localTransform, &(parent->globalTransform));

			//cout << "transform " << globalTransform.pos[0] << " " << globalTransform.pos[1] << " " << globalTransform.pos[2] << " /n";
		}

		
		void setPosition(float x, float y, float z)
		{
			globalTransform.setPosition(x, y, z);
		}
		void setRotation(float x, float y, float z)
		{
			globalTransform.setRotation(x, y, z);
		}
		void setScale(float x, float y, float z)
		{
			globalTransform.setScale(x, y, z);
		}
		void setLocalPosition(float x, float y, float z)
		{
			localTransform.setPosition(x, y, z);
		}
		void setLocalRotation(float x, float y, float z)
		{
			localTransform.setRotation(x, y, z);
		}
		void setLocalScale(float x, float y, float z)
		{
			localTransform.setScale(x, y, z);
		}
};
