#pragma once
#include "Transform.h"
#include "AVTmathLib.h"
#include "Component.h"
namespace GameObjectSpace
{

	enum class ColliderType {
		None,
		AABB
	};

	class AABB;
	class Collision;

	class Collider :public Component
	{

	public:
	
		float inverseMass = 0;
		static vector<Collider*> allColliders;
		Collider();
	
		virtual void update();
		virtual void init();
		virtual bool checkCollision(Collider* other, Collision* Collision);
		virtual ColliderType getColliderType();

		//Returns if there is any collision, adds collisions to list, start is 0 to check all colliders
		/** /
		bool checkCollisions(vector<Collider*> hits, int start);
		bool checkCollisions(vector<Collider*> hits);
		//virtual void resolveCollisionAABB(AABB* box);
		void checkAllCollisions();
		/**/
		//void correctPossition(float x, float y, float z);
		

	};

	class AABB : public Collider
	{
	public:
		float pos[3]; //the corner that has the largest X and lowest Z and Y
		float dim[3];
		
		AABB();
		bool checkCollisionAABB(AABB* other, Collision* Collision);
		bool checkCollision(Collider* other, Collision* Collision);
		ColliderType getColliderType();
		//void resolveCollisionAABB(AABB* other);
		

	};
}