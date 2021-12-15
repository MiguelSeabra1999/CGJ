#include "Orange.h"

using namespace OrangeSpace;



Orange::Orange()
{
	GameObject::GameObject();

	rigidbody = new RigidBody(&transform);
	GameObject::components.push_back(rigidbody);
	//random rotation
	// random velocity
	rigidbody->setVelocity(transform.globalTransform.forward);
	multVectorConstant(rigidbody->velocity, rigidbody->velocity, maxStartSpeed);
	rigidbody->setAcceleration(transform.globalTransform.forward);
	multVectorConstant(rigidbody->acceleration, rigidbody->acceleration, acceleration);


}
void Orange::start()
{
	GameObject::start();
}
void Orange::update()
{
	GameObject::update();
	GameObject::transform.globalTransform.rotate(2, 5, 3);
}
void Orange::initDraw(GLuint myShaderProgramIndex)
{
	GameObject::initDraw(myShaderProgramIndex);
	MyMesh amesh;
	float amb[] = { 0.2f, 0.15f, 0.1f, 1.0f };
	float diff[] = { 0.8f, 0.6f, 0.4f, 1.0f };
	float spec[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float emissive[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float shininess = 100.0f;
	int texcount = 0;


	amesh = createSphere(radius, 3);
	memcpy(amesh.mat.diffuse, diff, 4 * sizeof(float));
	memcpy(amesh.mat.specular, spec, 4 * sizeof(float));
	memcpy(amesh.mat.emissive, emissive, 4 * sizeof(float));
	amesh.mat.shininess = shininess;
	amesh.mat.texCount = texcount;
	myMeshes.push_back(amesh);


}


