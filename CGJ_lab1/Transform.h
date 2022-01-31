#pragma once
#include <iostream>
#include "AVTmathLib.h"

using namespace std;
namespace GameObjectSpace 
{
	class GameObject;// you have to declare this class exist to have a pointer to ir later on, since this script does not include "GameObject.h".
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
		void translate(float* pos)
		{
			translate(pos[0], pos[1], pos[2]);
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
			setRotation(0, 0, 0);
			setScale(1, 1, 1);
			updateReferencePoints();

		}

		float ClampAngle(float angle)
		{
			while (angle < 0 || angle >= 360)
			{
				if (angle < 0)
				{
					angle += 360;
				}
				else if (angle >= 360)
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
		void SumTransform(SimpleTransform* a, SimpleTransform* b)
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
			right[3] = 0;
			forward[0] = 0;
			forward[1] = 0;
			forward[2] = 1;
			forward[3] = 0;
			up[0] = 0;
			up[1] = 1;
			up[2] = 0;
			up[3] = 0;

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
			//sometimes float erros lead to unormalized vectors
			normalize(right);
			normalize(forward);
			normalize(up);
		}


	};

	class Transform
	{
	public:
		Transform* parent = nullptr;
		vector<Transform*> sons;
		GameObject* gameObject;
		SimpleTransform localTransform;
		SimpleTransform globalTransform;
		float mModel[16];

		void initZero()
		{
			localTransform.initZero();
			globalTransform.initZero();
		}

		void setParent(Transform* newParent)
		{
			parent = newParent;
			newParent->sons.push_back(this);

			updateLocalTransform();

		}

		void setOwner(GameObject* myOwner) {
			gameObject = myOwner;
		}


		void updateLocalTransform()
		{

			if (parent != nullptr)
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

		void lookAtCylindrical(Transform* other)
		{
			float toOther[3];
			float myPos[3];

			memcpy(myPos, globalTransform.pos, sizeof(float) * 3);
			multVectorConstant(myPos, myPos, -1);
			addVectors(toOther, other->globalTransform.pos, myPos, 3);
			toOther[1] = 0;
			normalize(toOther);
			float forwardAux[3];
			memcpy(forwardAux, globalTransform.forward, sizeof(float) * 3);
			forwardAux[1] = 0;
			normalize(forwardAux);
			float angleCosine = dotProduct(toOther, forwardAux);
			float upAux[3];
			crossProduct(upAux, toOther, forwardAux);
			float angle = acos(angleCosine) * RADTODEG;
			globalTransform.rotate(0, angle * -1 * upAux[1], 0);
		}

		void lookAt(Transform* other)
		{
			lookAtCylindrical(other);
			float toOther[3];
			float myPos[3];

			memcpy(myPos, globalTransform.pos, sizeof(float) * 3);
			multVectorConstant(myPos, myPos, -1);
			addVectors(toOther, other->globalTransform.pos, myPos, 3);
			toOther[0] = 0;
			normalize(toOther);
			float forwardAux[3];
			memcpy(forwardAux, globalTransform.forward, sizeof(float) * 3);
			forwardAux[0] = 0;
			normalize(forwardAux);
			float angleCosine = dotProduct(toOther, forwardAux);
			float upAux[3];
			crossProduct(upAux, toOther, forwardAux);
			float angle = acos(angleCosine) * RADTODEG;
			globalTransform.rotate(angle * -1 * upAux[0],0, 0);

			memcpy(myPos, globalTransform.pos, sizeof(float) * 3);
			multVectorConstant(myPos, myPos, -1);
			addVectors(toOther, other->globalTransform.pos, myPos, 3);
			toOther[2] = 0;
			normalize(toOther);
			forwardAux[3];
			memcpy(forwardAux, globalTransform.forward, sizeof(float) * 3);
			forwardAux[2] = 0;
			normalize(forwardAux);
			angleCosine = dotProduct(toOther, forwardAux);
			upAux[3];
			crossProduct(upAux, toOther, forwardAux);
			angle = acos(angleCosine) * RADTODEG;
			globalTransform.rotate(0, 0, angle * -1 * upAux[2]);
		}
	};
}
