
#include "AVTmathLib.h"
#include "Transform.h"
#include "Component.h"
//#include "ComponentLib.h"
namespace GameObjectSpace
{
	
	class RigidBody : public Component
	{
	public:
		float velocity[3];
		float acceleration[3];
		float angularVelocity[3];
		float angularAcceleration[3];
		Transform* transform;
		bool applyVelocity = true;
		float mass;

		RigidBody(Transform* objectTransform)
		{
			init();
			transform = objectTransform;

		}

		void init()
		{
			mass = 1;
			setVelocity(0, 0, 0);
			setAngularVelocity(0, 0, 0);
			setAcceleration(0, 0, 0);
			setAngularAcceleration(0, 0, 0);
		}

		void update()
		{
			addVectors(velocity, velocity, acceleration, 3);
			addVectors(angularVelocity, angularVelocity, angularAcceleration, 3);
			if (applyVelocity)
			{
				addVectors(transform->globalTransform.pos, transform->globalTransform.pos, velocity, 3);
				addVectors(transform->globalTransform.rot, transform->globalTransform.rot, angularVelocity, 3);
			}
		}

		void setVelocity(float x, float y, float z)
		{
			velocity[0] = x;
			velocity[1] = y;
			velocity[2] = z;
		}
		void setAngularVelocity(float x, float y, float z)
		{
			angularVelocity[0] = x;
			angularVelocity[1] = y;
			angularVelocity[2] = z;
		}
		void setAcceleration(float x, float y, float z)
		{
			acceleration[0] = x;
			acceleration[1] = y;
			acceleration[2] = z;
		}
		void setAngularAcceleration(float x, float y, float z)
		{
			angularAcceleration[0] = x;
			angularAcceleration[1] = y;
			angularAcceleration[2] = z;
		}
		void addVelocity(float x, float y, float z)
		{
			velocity[0] += x;
			velocity[1] += y;
			velocity[2] += z;
		}
		void addAngularVelocity(float x, float y, float z)
		{
			angularVelocity[0] += x;
			angularVelocity[1] += y;
			angularVelocity[2] += z;
		}
		void addAcceleration(float x, float y, float z)
		{
			acceleration[0] += x;
			acceleration[1] += y;
			acceleration[2] += z;
		}
		void addAngularAcceleration(float x, float y, float z)
		{
			angularAcceleration[0] += x;
			angularAcceleration[1] += y;
			angularAcceleration[2] += z;
		}

		void setVelocity(float* vec)
		{
			velocity[0] = vec[0];
			velocity[1] = vec[1];
			velocity[2] = vec[2];
		}
		void setAngularVelocity(float* vec)
		{
			angularVelocity[0] = vec[0];
			angularVelocity[1] = vec[1];
			angularVelocity[2] = vec[2];
		}
		void setAcceleration(float* vec)
		{
			acceleration[0] = vec[0];
			acceleration[1] = vec[1];
			acceleration[2] = vec[2];
		}
		void setAngularAcceleration(float* vec)
		{
			angularAcceleration[0] = vec[0];
			angularAcceleration[1] = vec[1];
			angularAcceleration[2] = vec[2];
		}
		void addVelocity(float* vec)
		{
			velocity[0] += vec[0];
			velocity[1] += vec[1];
			velocity[2] += vec[2];
		}
		void addAngularVelocity(float* vec)
		{
			angularVelocity[0] += vec[0];
			angularVelocity[1] += vec[1];
			angularVelocity[2] += vec[2];
		}
		void addAcceleration(float* vec)
		{
			acceleration[0] += vec[0];
			acceleration[1] += vec[1];
			acceleration[2] += vec[2];
		}
		void addAngularAcceleration(float* vec)
		{
			angularAcceleration[0] += vec[0];
			angularAcceleration[1] += vec[1];
			angularAcceleration[2] += vec[2];
		}
	};
}