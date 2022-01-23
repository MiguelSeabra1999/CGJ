#include "PlayerCar.h"
#include "Scene.h"

using namespace GameObjectSpace;



	PlayerCar::PlayerCar()
	{
		 //GameObject::GameObject();
		inputDir[0] = 0;
		inputDir[1] = 0;
		velocity = 0.0f;
		acceleration = 0.0f;


		/*rigidbody = new RigidBody(&(GameObject::transform));
		rigidbody->applyVelocity = false;
		GameObject::components.push_back(rigidbody);*/
	}
	void PlayerCar::start()
	{
		GameObject::start();
		rigidbody = (RigidBody*)GetComponent("RigidBody");
		memcpy(startingPos, transform.globalTransform.pos, 3 * sizeof(float));
		memcpy(startingRot, transform.globalTransform.rot, 3 * sizeof(float));
	}
	void PlayerCar::update()
	{


		//velocity = length(rigidbody->velocity);
			
		if (velocity > 0)
		{
			if(handbreaking)
				GameObject::transform.globalTransform.rotate(0, -inputDir[1] * ((1 + handbrakeTurnPercent) * turnSpeed * currentScene->physicsEngine->deltaTime), 0);
			else
				GameObject::transform.globalTransform.rotate(0, -inputDir[1] * turnSpeed * currentScene->physicsEngine->deltaTime, 0);
		}
		else
		{
			if(handbreaking)
				GameObject::transform.globalTransform.rotate(0, inputDir[1] * ((1+handbrakeTurnPercent)*turnSpeed * currentScene->physicsEngine->deltaTime), 0);
			else
				GameObject::transform.globalTransform.rotate(0, inputDir[1] * turnSpeed * currentScene->physicsEngine->deltaTime, 0);
		}
		float rot[16];
		genRotationMatrix_Y(rot,0.5f* inputDir[1] * currentScene->physicsEngine->deltaTime);
		multMatixByVector(rigidbody->velocity,rot, rigidbody->velocity);
	
		//rigidbody->addForce(-1 * transform.globalTransform.right[0] * velocity, 0, -1 * transform.globalTransform.right[2] * velocity);
		if (handbreaking)
			rigidbody->addForce(-1 * transform.globalTransform.right[0] * (acceleration - 0.001), 0, -1 * transform.globalTransform.right[2] * acceleration);
		else
			rigidbody->addForce(-1 * transform.globalTransform.right[0] * acceleration, 0, -1 * transform.globalTransform.right[2] * acceleration);
		GameObject::update();
	}

	void PlayerCar::forward(bool state)
	{

		if (state)
		{
			acceleration += forwardAcceleration;
			//inputDir[0] -= 1;
		}

		else
		{
			acceleration -= forwardAcceleration;
			//inputDir[0] += 1;
		}

	}
	void PlayerCar::backward(bool state)
	{
		if (state)
		{
			acceleration -= backAcceleration;
			//inputDir[0] += 1;
		}

		else
		{
			acceleration += backAcceleration;
			//inputDir[0] -= 1;
		}
	}
	void PlayerCar::left(bool state)
	{
		if (state)
			inputDir[1] += 1;
		else
			inputDir[1] -= 1;
	}
	void PlayerCar::right(bool state)
	{
		if (state)
			inputDir[1] -= 1;
		else
			inputDir[1] += 1;
	}

	void PlayerCar::OnCollisionEnter()
	{
		velocity = 0;
	}
	

	void PlayerCar::OnTriggerEnter()
	{
		respawn();
		//currentScene->restart();
	}
	void PlayerCar::handbreak(bool state)
	{
		handbreaking = state;
		
	}

	void PlayerCar::respawn()
	{
		hp -= 1;
		memcpy(transform.globalTransform.pos, startingPos, 3 * sizeof(float));
		memcpy(transform.globalTransform.rot, startingRot, 3 * sizeof(float));
		rigidbody->setVelocitiesZero();
		if(hp <= 0)
		{
			cout << "restart";
			currentScene->restart();
		}
		else {

		}
	}