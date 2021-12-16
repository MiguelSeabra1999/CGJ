#include "PlayerCar.h"


using namespace GameObjectSpace;



	PlayerCar::PlayerCar()
	{
		GameObject::GameObject();
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

	}
	void PlayerCar::update()
	{
		GameObject::update();


		velocity += acceleration;
		if (acceleration == 0)
		{
			if (velocity > 0)
			{
				velocity -= friction;
				if (velocity < 0)
					velocity = 0;
			}
			else if (velocity < 0)
			{
				velocity += friction;
				if (velocity > 0)
					velocity = 0;
			}
		}

		if (velocity > maxSpeed)
			velocity = maxSpeed;
		if (velocity < -maxSpeed)
			velocity = -maxSpeed;


		GameObject::transform.globalTransform.translate(-1 * transform.globalTransform.right[0] * velocity, 0, -1 * transform.globalTransform.right[2] * velocity);
		//cout <<   "" << -1 * transform.globalTransform.right[0] * velocity << "," << 0 <<  "," << -1 * transform.globalTransform.right[2] * velocity << " \n";
		//GameObject::transform.globalTransform.translate(inputDir[0]*speed, 0, 0);
		if (velocity >= 0)
			GameObject::transform.globalTransform.rotate(0, inputDir[1] * speed * 100, 0);
		else
			GameObject::transform.globalTransform.rotate(0, -inputDir[1] * speed * 100, 0);

	}
	void PlayerCar::initDraw(GLuint myShaderProgramIndex)
	{

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
	
