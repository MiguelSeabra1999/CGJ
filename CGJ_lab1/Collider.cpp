#include "Collider.h"
using namespace GameObjectSpace;
using namespace std;

		vector<Collider*> Collider::allColliders;
		Collider::Collider()
		{
			Component::Component();
			Collider::allColliders.push_back(this);
		}
		void Collider::update()
		{
		}
		void Collider::init()
		{

		}
		bool Collider::checkCollision(Collider* other, Collision* Collision)
		{
			return false;
		}
		ColliderType Collider::getColliderType()
		{
			return ColliderType::None;
		}
		/*//Returns if there is any collision, adds collisions to list, start is 0 to check all colliders
		bool Collider::checkCollisions(vector<Collider*> hits, int start)
		{
			bool hitSomething = false;
			int n = Collider::allColliders.size();
			for (int i = start; i < n; i++)
			{
				if (Collider::allColliders[i] != this)
					if (Collider::allColliders[i]->checkCollision(this))
					{
						hits.push_back(Collider::allColliders[i]);
						hitSomething = true;
					}
			}
			return hitSomething;
	

		}
		bool Collider::checkCollisions(vector<Collider*> hits)
		{
			return checkCollisions(hits, 0);
		}*/
		//void Collider::resolveCollisionAABB(AABB* box) {}
	/*	void Collider::checkAllCollisions()
		{


			vector<Collider*> hits;
			checkCollisions(hits);

			//resolve collisions
			int n_hits = hits.size();
			if (n_hits > 0)
			{
				for (int j = 0; j < n_hits; j++)
				{
					if (inverseMass != 0 && hits[j]->inverseMass != 0)
					{
						if (hits[j]->getColliderType() == ColliderType::AABB)
							resolveCollisionAABB((AABB*)hits[j]);
					}
				}
			}


		}
		*/
		/** /void Collider::correctPossition(float x, float y, float z)
		{

		}
		/**/



	AABB::AABB()
		{
			Collider::Collider();

		}
		bool AABB::checkCollisionAABB(AABB* other, Collision* Collision)
		{
			if (pos[0] < other->pos[0] + other->dim[0] &&
				pos[0] + dim[0] > other->pos[0] &&
				pos[1] < other->pos[1] + other->dim[1] &&
				pos[1] + dim[1] > other->pos[1] &&
				pos[2] < other->pos[2] + other->dim[2] &&
				pos[2] + dim[2] > other->pos[2])
			{
				return true;
			}
			return false;
		}
		bool AABB::checkCollision(Collider* other, Collision* Collision)
		{
			if (other->getColliderType() == ColliderType::AABB)
			{
				return checkCollisionAABB((AABB*)other,  Collision);
			}
			return false;
		}
		/*bool AABB::resolveCollision(Collider* other)
		{
			if (other->getColliderType() == ColliderType::AABB)
			{
				return checkCollisionAABB((AABB*)other);
			}
			return false;
		}*/
		ColliderType AABB::getColliderType()
		{
			return ColliderType::AABB;
		}
		/*void AABB::resolveCollisionAABB(AABB* other)
		{
			//find easiest direction to project to

			int dir[3] = { 1,0,0 };
			float minDist = 10000;
			//each projection is a possible translation that solves the collision
			float projectionRight = abs(pos[0] - other->pos[0] + other->dim[0]);
			minDist = projectionRight;
			float projectionLeft = abs(pos[0] + dim[0] - other->pos[0]);
			if (projectionLeft < minDist)
			{
				dir[0] = -1; dir[1] = 0; dir[2] = 0;
				minDist = projectionLeft;
			}

			float projectionUp = abs(pos[1] - other->pos[1] + other->dim[1]);
			if (projectionUp < minDist)
			{
				dir[0] = 0; dir[1] = 1; dir[2] = 0;
				minDist = projectionUp;
			}
			float projectionDown = abs(pos[1] + dim[1] - other->pos[1]);
			if (projectionDown < minDist)
			{
				dir[0] = -1; dir[1] = -1; dir[2] = 0;
				minDist = projectionDown;
			}

			float projectionForward = abs(pos[2] - other->pos[2] + other->dim[2]);
			if (projectionForward < minDist)
			{
				dir[0] = 0; dir[1] = 0; dir[2] = -1;
				minDist = projectionForward;
			}
			float projectionBack = abs(pos[2] + dim[2] - other->pos[2]);
			if (projectionBack < minDist)
			{
				dir[0] = 0; dir[1] = 0; dir[2] = -1;
				minDist = projectionBack;
			}

			float nudge = 0.01;
			float correction[3] = { dir[0] * minDist + nudge, dir[1] * minDist + nudge , dir[2] * minDist + nudge };

			//selfcorrection = inverseMass / (both inverse masses)     *      correction
			// other correction = other inverse mass / (both inverse masses)    * correction
			float thisCorrectionPercent = inverseMass / (inverseMass + other->inverseMass);
			correctPossition(thisCorrectionPercent * correction[0], thisCorrectionPercent * correction[1], thisCorrectionPercent * correction[2]);
			float otherCorrectionPercent = 1 - thisCorrectionPercent;
			correctPossition(-1 * otherCorrectionPercent * correction[0], -1 * otherCorrectionPercent * correction[1], -1 * otherCorrectionPercent * correction[2]);

		}*/

	
