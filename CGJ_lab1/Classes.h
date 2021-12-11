/*#include <GL/glew.h>
// GLUT is the toolkit to interface with the OS
#include <GL/freeglut.h>
#include <IL/il.h>
// Use Very Simple Libs
#include "VSShaderlib.h"
#include "AVTmathLib.h"
#include "VertexAttrDef.h"
#include "geometry.h"
#include "avtFreeType.h"
class GameObject {
public:

	virtual void update();
	virtual void start();
	virtual void initDraw(GLuint myShaderProgramIndex);
	void draw(GLuint shaderProgramIndex);

};
class PlayerCar : public GameObject
{
public:
	PlayerCar();
	void start();
	void update();
	void draw();
	void initDraw();
};*/