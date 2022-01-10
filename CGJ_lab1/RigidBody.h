#pragma once
#include "AVTmathLib.h"
#include "Transform.h"
#include "ComponentLib.h"
#include "Collider.h"

namespace GameObjectSpace
{
	class Collider;
	class RigidBody : public Component
	{
	public:
		float velocity[3];
		float acceleration[3];
		float angularVelocity[3];
		float angularAcceleration[3];
		float allForces[3];
		Transform* transform;
		bool applyVelocity = true;
		float mass = 1;
		float inverseMass = 1;
		static vector<RigidBody*> allRigidBodies;
		Collider* collider;

		RigidBody(GameObject* owner);
		void init();

		void update();

		void setVelocity(float x, float y, float z);
		void setAngularVelocity(float x, float y, float z);
		void setAcceleration(float x, float y, float z);
		void setAngularAcceleration(float x, float y, float z);
		void addVelocity(float x, float y, float z);
		void addAngularVelocity(float x, float y, float z);
		void addAcceleration(float x, float y, float z);
		void addAngularAcceleration(float x, float y, float z);

		void setVelocity(float* vec);
		void setAngularVelocity(float* vec);
		void setAcceleration(float* vec);
		void setAngularAcceleration(float* vec);
		void addVelocity(float* vec);
		void addAngularVelocity(float* vec);
		void addAcceleration(float* vec);
		void addAngularAcceleration(float* vec);
		
		void addForce(float* force);
		void addForce(float* force, float scalingFactor);
		void addForce(float x, float y, float z);
		void setAllForcesZero();
		const char* GetType();
		void setMass(float new_mass);
		
	};
}