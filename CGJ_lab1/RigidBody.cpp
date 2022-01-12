#pragma once
#include "RigidBody.h"

//#include "ComponentLib.h"
using namespace GameObjectSpace;
vector<RigidBody*> RigidBody::allRigidBodies;
RigidBody::RigidBody(GameObject* owner) :Component(owner)
{
	transform = &(owner->transform);
	init();
	RigidBody::allRigidBodies.push_back(this);
	
	collider = (Collider*)owner->GetComponent("Collider");
	if (collider != nullptr)
	{
		collider->rigidbody = this;
	}
}
void RigidBody::init()
{
	mass = 1;
	setVelocity(0, 0, 0);
	setAngularVelocity(0, 0, 0);
	setAcceleration(0, 0, 0);
	setAngularAcceleration(0, 0, 0);
	setAllForcesZero();
}

void RigidBody::update()
{
/** /	addVectors(velocity, velocity, acceleration, 3);
	addVectors(angularVelocity, angularVelocity, angularAcceleration, 3);
	if (applyVelocity)
	{
		addVectors(transform->globalTransform.pos, transform->globalTransform.pos, velocity, 3);
		addVectors(transform->globalTransform.rot, transform->globalTransform.rot, angularVelocity, 3);
	}/**/
}

const char* RigidBody::GetType()
{
	return "RigidBody";
}

void RigidBody::setVelocity(float x, float y, float z)
{
	velocity[0] = x;
	velocity[1] = y;
	velocity[2] = z;
}
void RigidBody::setAngularVelocity(float x, float y, float z)
{
	angularVelocity[0] = x;
	angularVelocity[1] = y;
	angularVelocity[2] = z;
}
void RigidBody::setAcceleration(float x, float y, float z)
{
	acceleration[0] = x;
	acceleration[1] = y;
	acceleration[2] = z;
}
void RigidBody::setAngularAcceleration(float x, float y, float z)
{
	angularAcceleration[0] = x;
	angularAcceleration[1] = y;
	angularAcceleration[2] = z;
}
void RigidBody::addVelocity(float x, float y, float z)
{
	velocity[0] += x;
	velocity[1] += y;
	velocity[2] += z;
}
void RigidBody::addAngularVelocity(float x, float y, float z)
{
	angularVelocity[0] += x;
	angularVelocity[1] += y;
	angularVelocity[2] += z;
}
void RigidBody::addAcceleration(float x, float y, float z)
{
	acceleration[0] += x;
	acceleration[1] += y;
	acceleration[2] += z;
}
void RigidBody::addAngularAcceleration(float x, float y, float z)
{
	angularAcceleration[0] += x;
	angularAcceleration[1] += y;
	angularAcceleration[2] += z;
}

void RigidBody::setVelocity(float* vec)
{
	velocity[0] = vec[0];
	velocity[1] = vec[1];
	velocity[2] = vec[2];
}
void RigidBody::setAngularVelocity(float* vec)
{
	angularVelocity[0] = vec[0];
	angularVelocity[1] = vec[1];
	angularVelocity[2] = vec[2];
}
void RigidBody::setAcceleration(float* vec)
{
	acceleration[0] = vec[0];
	acceleration[1] = vec[1];
	acceleration[2] = vec[2];
}
void RigidBody::setAngularAcceleration(float* vec)
{
	angularAcceleration[0] = vec[0];
	angularAcceleration[1] = vec[1];
	angularAcceleration[2] = vec[2];
}
void RigidBody::addVelocity(float* vec)
{
	velocity[0] += vec[0];
	velocity[1] += vec[1];
	velocity[2] += vec[2];
}
void RigidBody::addAngularVelocity(float* vec)
{
	angularVelocity[0] += vec[0];
	angularVelocity[1] += vec[1];
	angularVelocity[2] += vec[2];
}
void RigidBody::addAcceleration(float* vec)
{
	acceleration[0] += vec[0];
	acceleration[1] += vec[1];
	acceleration[2] += vec[2];
}
void RigidBody::addAngularAcceleration(float* vec)
{
	angularAcceleration[0] += vec[0];
	angularAcceleration[1] += vec[1];
	angularAcceleration[2] += vec[2];
}

void RigidBody::addForce(float* force)
{
	addForce(force[0], force[1], force[2]);
}
void RigidBody::addForce(float* force, float scalingFactor)
{
	addForce(force[0]* scalingFactor, force[1]* scalingFactor, force[2]* scalingFactor);
}
void RigidBody::addForce(float x, float y, float z)
{
	allForces[0] += x;
	allForces[1] += y;
	allForces[2] += z;
}
void RigidBody::setAllForcesZero()
{
	allForces[0] = 0;
	allForces[1] = 0;
	allForces[2] = 0;
}
void RigidBody::setVelocitiesZero()
{
	velocity[0] = 0;
	velocity[1] = 0;
	velocity[2] = 0;
}
void RigidBody::setMass(float new_mass)
{
	inverseMass = 1 / new_mass;
	mass = new_mass;

}
void RigidBody::addImpulse(float* force)
{
	velocity[0] += force[0];
	velocity[1] += force[1];
	velocity[2] += force[2];
}
void RigidBody::addImpulse(float* force, float scalingFactor)
{
	velocity[0] += scalingFactor*force[0];
	velocity[1] += scalingFactor*force[1];
	velocity[2] += scalingFactor*force[2];
}
void RigidBody::addImpulse(float x, float y, float z)
{
	velocity[0] += x;
	velocity[1] += y;
	velocity[2] += z;
}