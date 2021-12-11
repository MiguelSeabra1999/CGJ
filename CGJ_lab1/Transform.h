class SimpleTransform
{
public:
	float pos[3];
	float rot[3];
	float scale[3];


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
	}
	void rotate(float x, float y, float z)
	{
		rot[0] += x;
		rot[1] += y;
		rot[2] += z;
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

		rot[0] = a->rot[0] + b->rot[0];
		rot[1] = a->rot[1] + b->rot[1];
		rot[2] = a->rot[2] + b->rot[2];
		ClampRotations();

		scale[0] = a->scale[0] * b->scale[0];
		scale[1] = a->scale[1] * b->scale[1];
		scale[2] = a->scale[2] * b->scale[2];
	}

};

class Transform
{
	public:
		Transform* parent = nullptr;
		Transform* son = nullptr;
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
		void updateLocalTransform()
		{
			if(parent != nullptr)
				globalTransform.SumTransform(&localTransform, &(parent->globalTransform));
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
