#include "Transform.h"
#include "AVTmathLib.h"
class RigidBody
{
	public:
		float velocity[3];
		float angularVelocity[3];
		Transform* transform;
		
		void physicsUpdate()
		{
			addVectors(transform->globalTransform.pos, transform->globalTransform.pos, velocity, 3);
		}
}