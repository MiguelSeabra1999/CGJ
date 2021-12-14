//
// CGJ: Phong Shading and Text rendered with FreeType library
// The text rendering was based on https://learnopengl.com/In-Practice/Text-Rendering
// This demo was built for learning purposes only.
// Some code could be severely optimised, but I tried to
// keep as simple and clear as possible.
//
// The code comes with no warranties, use it at your own risk.
// You may use it, or parts of it, wherever you want.
// 
// Author: Jo�o Madeiras Pereira
//

/*
gluttimerfunr = 1000/60
refresh 0
glutposredisplay

*/

#include <math.h>
#include <iostream>
#include <sstream>
#include <string>


#include "Classes.h"
#include "GameObject.cpp"

using namespace std;

#define CAPTION "CGJ Demo: Phong Shading and Text rendered with FreeType"
int WindowHandle = 0;
int WinX = 1024, WinY = 768;

unsigned int FrameCount = 0;

//shaders
VSShaderLib shader;  //geometry
VSShaderLib shaderText;  //render bitmap text

//File with the font
const string font_name = "fonts/arial.ttf";

//Vector with meshes
vector<struct MyMesh> myMeshes;
//Vector with GameObjects
vector< GameObject*> myGameObjects;
PlayerCar* player;

//External array storage defined in AVTmathLib.cpp



GLint pvm_uniformId;
GLint vm_uniformId;
GLint normal_uniformId;
GLint lPos_uniformId;
GLint tex_loc, tex_loc1, tex_loc2;
	
// Camera Position
float camX, camY, camZ;

// Mouse Tracking Variables
int startX, startY, tracking = 0;

// Camera Spherical Coordinates
float alpha = 39.0f, beta = 51.0f;
float r = 10.0f;

// Frame counting and FPS computation
long myTime,timebase = 0,frame = 0;
char s[32];
float lightPos[4] = {4.0f, 6.0f, 2.0f, 1.0f};

map<char, char> keys = {
	{ 'w', false },
	{ 'a', false },
	{ 's', false },
	{ 'd', false }
};

void timer(int value)
{
	std::ostringstream oss;
	oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
    FrameCount = 0;
    glutTimerFunc(1000, timer, 0);
}

void refresh(int value)
{
	glutTimerFunc(1000/60, refresh, 0);
	glutPostRedisplay();

}

// ------------------------------------------------------------
//
// Reshape Callback Function
//

void changeSize(int w, int h) {

	float ratio;
	// Prevent a divide by zero, when window is too short
	if(h == 0)
		h = 1;
	// set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// set the projection matrix
	ratio = (1.0f * w) / h;
	loadIdentity(PROJECTION);
	perspective(53.13f, ratio, 0.1f, 1000.0f);
}


// ------------------------------------------------------------
//
// Render stufff
//

void renderScene(void) {

	GLint loc;

	FrameCount++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// load identity matrices
	loadIdentity(VIEW);
	loadIdentity(MODEL);
	// set the camera using a function similar to gluLookAt
	lookAt(camX, camY, camZ, 0,0,0, 0,1,0);
	// use our shader
	glUseProgram(shader.getProgramIndex());

		//send the light position in eye coordinates
		//glUniform4fv(lPos_uniformId, 1, lightPos); //efeito capacete do mineiro, ou seja lighPos foi definido em eye coord 

		float res[4];
		multMatrixPoint(VIEW, lightPos,res);   //lightPos definido em World Coord so is converted to eye space
		glUniform4fv(lPos_uniformId, 1, res);

	int objId=0; //id of the object mesh - to be used as index of mesh: Mymeshes[objID] means the current mesh
	int count = myGameObjects.size();

	for (int i = 0; i < count; i++)
	{
		(*myGameObjects[i]).update();
		(*myGameObjects[i]).draw();
		if (!shader.isProgramValid()) {
			printf("Program Not Valid!\n");
			exit(1);	
		}
	}

	//Render text (bitmap fonts) in screen coordinates. So use ortoghonal projection with viewport coordinates.
	glDisable(GL_DEPTH_TEST);
	//the glyph contains background colors and non-transparent for the actual character pixels. So we use the blending
	glEnable(GL_BLEND);  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	int m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);

	//viewer at origin looking down at  negative z direction
	pushMatrix(MODEL);
	loadIdentity(MODEL);
	pushMatrix(PROJECTION);
	loadIdentity(PROJECTION);
	pushMatrix(VIEW);
	loadIdentity(VIEW);
	ortho(m_viewport[0], m_viewport[0] + m_viewport[2] - 1, m_viewport[1], m_viewport[1] + m_viewport[3] - 1, -1, 1);
	RenderText(shaderText, "This is a sample text", 25.0f, 25.0f, 1.0f, 0.5f, 0.8f, 0.2f);
	RenderText(shaderText, "CGJ Light and Text Rendering Demo", 440.0f, 570.0f, 0.5f, 0.3, 0.7f, 0.9f);
	popMatrix(PROJECTION);
	popMatrix(VIEW);
	popMatrix(MODEL);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glutSwapBuffers();
}

// ------------------------------------------------------------
//
// Events from the Keyboard
//
void processKeys(unsigned char key, int xx, int yy, bool state)
{
	switch (key) {

	case 27:
		glutLeaveMainLoop();
		break;

	case 'c':
		printf("Camera Spherical Coordinates (%f, %f, %f)\n", alpha, beta, r);
		break;
	case 'm': glEnable(GL_MULTISAMPLE); break;
	case 'n': glDisable(GL_MULTISAMPLE); break;
	case 'w':
		if(state != keys['w'])
		{
			player->forward(state);
			keys['w'] = state;
		}
		break;
	case 's':
		if (state != keys['s'])
		{
			player->backward(state);
			keys['s'] = state;
		}
		break;
	case 'a':
		if (state != keys['a'])
		{
			player->left(state);
			keys['a'] = state;
		}
		break;
	case 'd':
		if (state != keys['d'])
		{
			player->right(state);
			keys['d'] = state;
		}
		break;

	}
}
void processKeysDown(unsigned char key, int xx, int yy)
{
	processKeys(key, xx, yy, true);
}
void processKeysUp(unsigned char key, int xx, int yy)
{
	processKeys(key, xx, yy, false);
}



// ------------------------------------------------------------
//
// Mouse Events
//

void processMouseButtons(int button, int state, int xx, int yy)
{
	// start tracking the mouse
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
	}

	//stop tracking the mouse
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha -= (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			r += (yy - startY) * 0.01f;
			if (r < 0.1f)
				r = 0.1f;
		}
		tracking = 0;
	}
}

// Track mouse motion while buttons are pressed

void processMouseMotion(int xx, int yy)
{

	int deltaX, deltaY;
	float alphaAux, betaAux;
	float rAux;

	deltaX =  - xx + startX;
	deltaY =    yy - startY;

	// left mouse button: move camera
	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0f)
			betaAux = 85.0f;
		else if (betaAux < -85.0f)
			betaAux = -85.0f;
		rAux = r;
	}
	// right mouse button: zoom
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r + (deltaY * 0.01f);
		if (rAux < 0.1f)
			rAux = 0.1f;
	}

	camX = rAux * sin(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
	camZ = rAux * cos(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
	camY = rAux *   						       sin(betaAux * 3.14f / 180.0f);

//  uncomment this if not using an idle or refresh func
//	glutPostRedisplay();
}


void mouseWheel(int wheel, int direction, int x, int y) {

	r += direction * 0.1f;
	if (r < 0.1f)
		r = 0.1f;

	camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camY = r *   						     sin(beta * 3.14f / 180.0f);

//  uncomment this if not using an idle or refresh func
//	glutPostRedisplay();
}

// --------------------------------------------------------
//
// Shader Stuff
//


GLuint setupShaders() {

	// Shader for models
	bool usingPhong = true;
	shader.init();
	if(usingPhong)
	{
		shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/pointlight.vert");
		shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/pointlight.frag");
	}
	else
	{
		shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/gouraud.vert");
		shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/gouraud.frag");
	}
	// set semantics for the shader variables
	glBindFragDataLocation(shader.getProgramIndex(), 0, "colorOut");
	glBindAttribLocation(shader.getProgramIndex(), VERTEX_COORD_ATTRIB, "position");
	glBindAttribLocation(shader.getProgramIndex(), NORMAL_ATTRIB, "normal");
	glLinkProgram(shader.getProgramIndex());
	//glBindAttribLocation(shader.getProgramIndex(), TEXTURE_COORD_ATTRIB, "texCoord");

	pvm_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_pvm");
	vm_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_viewModel");
	normal_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_normal");
	lPos_uniformId = glGetUniformLocation(shader.getProgramIndex(), "l_pos");
	tex_loc = glGetUniformLocation(shader.getProgramIndex(), "texmap");
	tex_loc1 = glGetUniformLocation(shader.getProgramIndex(), "texmap1");
	tex_loc2 = glGetUniformLocation(shader.getProgramIndex(), "texmap2");
	
	printf("InfoLog for Per Fragment Phong Lightning Shader\n%s\n\n", shader.getAllInfoLogs().c_str());

	// Shader for bitmap Text
	shaderText.init();
	shaderText.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/text.vert");
	shaderText.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/text.frag");

	glLinkProgram(shaderText.getProgramIndex());
	printf("InfoLog for Text Rendering Shader\n%s\n\n", shaderText.getAllInfoLogs().c_str());
	
	return(shader.isProgramLinked() && shaderText.isProgramLinked());
}

// ------------------------------------------------------------
//
// Model loading and OpenGL setup
//
void createGameObjects()
{
	PlayerCar* playerCar = new PlayerCar();
	playerCar->transform.setScale(.2, .2, .2);
	myGameObjects.push_back((GameObject*)playerCar);
	player = playerCar;


	Cube* cube = new Cube();
	cube->transform.setLocalScale(3,.6,1.7);
	cube->transform.setLocalPosition(.5,.2,0);
	cube->transform.setParent(&(playerCar->transform));
	myGameObjects.push_back((GameObject*)cube);

	cube = new Cube();
	cube->transform.setLocalScale(1.4, .6, 1.7);
	cube->transform.setLocalPosition(.69, .775, 0);
	cube->transform.setParent(&(playerCar->transform));
	myGameObjects.push_back((GameObject*)cube);

	cube = new Cube();
	cube->transform.setLocalScale(.8, .8, 1.7);
	cube->transform.setLocalPosition(1.4, .5, 0);
	cube->transform.setRotation(0, 0, 45);
	cube->transform.setParent(&(playerCar->transform));
	myGameObjects.push_back((GameObject*)cube);

	
	Wheel* wheel = new Wheel();
	wheel->transform.setLocalPosition(-0.5, 0, 1);
	wheel->transform.setRotation(90, 0, 0);
	wheel->transform.setLocalScale(0.3, 0.3, 0.3);
	wheel->transform.setParent(&(playerCar->transform));
	myGameObjects.push_back((GameObject*)wheel);

	wheel = new Wheel();
	wheel->transform.setLocalPosition(-0.5, 0, -1);
	wheel->transform.setRotation(90,0, 0);
	wheel->transform.setLocalScale(0.3, 0.3, 0.3);
	wheel->transform.setParent(&(playerCar->transform));
	myGameObjects.push_back((GameObject*)wheel);

	wheel = new Wheel();
	wheel->transform.setLocalPosition(1.5, 0, 1);
	wheel->transform.setRotation(90, 0, 0);
	wheel->transform.setLocalScale(0.3, 0.3, 0.3);
	wheel->transform.setParent(&(playerCar->transform));
	myGameObjects.push_back((GameObject*)wheel);

	wheel = new Wheel();
	wheel->transform.setLocalPosition(1.5, 0, -1);
	wheel->transform.setRotation(90, 0, 0);
	wheel->transform.setLocalScale(0.3, 0.3, 0.3);
	wheel->transform.setParent(&(playerCar->transform));
	myGameObjects.push_back((GameObject*)wheel);


	float mapSize = 30;
	cube = new Cube();
	cube->transform.setScale(mapSize, 1, mapSize);
	cube->transform.setPosition(0, -1, 0);
	myGameObjects.push_back((GameObject*)cube);

	cube = new Cube();
	cube->transform.setScale(mapSize, 5, 1);
	cube->transform.setPosition(0,0, mapSize/2);
	myGameObjects.push_back((GameObject*)cube);

	cube = new Cube();
	cube->transform.setScale(mapSize, 5, 1);
	cube->transform.setPosition(0, 0, -mapSize / 2);
	myGameObjects.push_back((GameObject*)cube);

	cube = new Cube();
	cube->transform.setScale( 1,5 , mapSize);
	cube->transform.setPosition(mapSize / 2, 0, 0);
	myGameObjects.push_back((GameObject*)cube);

	cube = new Cube();
	cube->transform.setScale(1, 5, mapSize);
	cube->transform.setPosition(-mapSize / 2, 0, 0);
	myGameObjects.push_back((GameObject*)cube);

	

}

void init()
{
	MyMesh amesh;

	/* Initialization of DevIL */
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		printf("wrong DevIL version \n");
		exit(0);
	}
	ilInit();

	/// Initialization of freetype library with font_name file
	freeType_init(font_name);

	// set the camera position based on its spherical coordinates
	camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camY = r *   						     sin(beta * 3.14f / 180.0f);

	createGameObjects();

	int count = myGameObjects.size();
	for(int i = 0; i < count; i++)
	{
		(*myGameObjects[i]).initDraw(shader.getProgramIndex());
		(*myGameObjects[i]).start();
	}

	// some GL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}


// ------------------------------------------------------------
//
// Main function
//


int main(int argc, char **argv) {

//  GLUT initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA|GLUT_MULTISAMPLE);

	glutInitContextVersion (4, 3);
	glutInitContextProfile (GLUT_CORE_PROFILE );
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);

	glutInitWindowPosition(100,100);
	glutInitWindowSize(WinX, WinY);
	WindowHandle = glutCreateWindow(CAPTION);


//  Callback Registration
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	glutTimerFunc(0, timer, 0);
	//glutIdleFunc(renderScene);  // Use it for maximum performance
	glutTimerFunc(0, refresh, 0);    //use it to to get 60 FPS whatever

//	Mouse and Keyboard Callbacks
	glutKeyboardFunc(processKeysDown);
	glutKeyboardUpFunc(processKeysUp);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	glutMouseWheelFunc ( mouseWheel ) ;
	

//	return from main loop
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

//	Init GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	printf ("Vendor: %s\n", glGetString (GL_VENDOR));
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("Version: %s\n", glGetString (GL_VERSION));
	printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));

	if (!setupShaders())
		return(1);

	init();

	//  GLUT main loop
	glutMainLoop();

	return(0);
}



