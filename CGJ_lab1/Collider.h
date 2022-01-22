#pragma once

#include "AVTmathLib.h"
#include "ComponentLib.h"
#include "RigidBody.h"

namespace GameObjectSpace
{
	class Scene;
	enum class ColliderType {
		None,
		AABB
	};

	class AABB;
	class Collision;
	class RigidBody;

	class Collider :public Component
	{

	public:
		GameObject* cube;
		RigidBody* rigidbody;
		float restitution = 1;
		bool isTrigger = false;
		bool isActive = true;
		static vector<Collider*> allColliders;
		Collider(GameObject * owner);

		virtual void update();
		virtual void init();
		virtual bool checkCollision(Collider* other, Collision** Collision);
		virtual ColliderType getColliderType();

		//Returns if there is any collision, adds collisions to list, start is 0 to check all colliders
		/** /
		bool checkCollisions(vector<Collider*> hits, int start);
		bool checkCollisions(vector<Collider*> hits);
		//virtual void resolveCollisionAABB(AABB* box);
		void checkAllCollisions();
		/**/
		//void correctPossition(float x, float y, float z);
		const char* GetType();

	};

	class AABB : public Collider
	{
	public:
		float pos[3]; //the corner that has the largest X and lowest Z and Y
		float dim[3];
		
		
		AABB(GameObject * owner);
		void setDim(float x, float y, float z);
		bool checkCollisionAABB(AABB* other, Collision** Collision);
		bool checkCollision(Collider* other, Collision** Collision);
		bool CheckInBound(float pos, float dim, float otherPos, float otherDim);
		ColliderType getColliderType();
		void update();
		void CalcPenetration(AABB* other, float* penetration);
		//void resolveCollisionAABB(AABB* other);
		

	};
}