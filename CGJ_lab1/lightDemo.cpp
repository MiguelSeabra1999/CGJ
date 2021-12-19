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


#include "GameObjectLib.h"


using namespace GameObjectSpace;






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
GLint model_uniformId;

GLint tex_loc, tex_loc1, tex_loc2;
	
// Camera Position
float camX, camY, camZ;

// Mouse Tracking Variables
int startX = WinX/2.0f, startY=WinY/2.0f, tracking = 0.0f;

// Camera Spherical Coordinates
float alpha = 0.0f, beta = 0.0f;
float r = 10.0f;

// Frame counting and FPS computation
long myTime,timebase = 0,frame = 0;
char s[32];
float lightPos[4] = {4.0f, 6.0f, 2.0f, 1.0f};
float* cameraLookAt = new float(9);
int firstCameraIndex = 0;
Camera* currentCam;

map<char, char> keys = {
	{ 'w', false },
	{ 'a', false },
	{ 's', false },
	{ 'd', false }
};

// Camera Stuff
float positionTopDownCamera[3] = { 0.0f, 50.0f, 0.0f };



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
	
	WinX = w;
	WinY = h;
	currentCam->UpdateProjection();
}


// ------------------------------------------------------------
//
// Render stufff
//

void renderScene(void) {

	GLint loc;

	FrameCount++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	currentCam->UpdateProjection();
	
	loadIdentity(VIEW);
	loadIdentity(MODEL);
	// set the camera using a function similar to gluLookAt
	lookAt(currentCam->lookAt[0], currentCam->lookAt[1], currentCam->lookAt[2], currentCam->lookAt[3], currentCam->lookAt[4], currentCam->lookAt[5], currentCam->lookAt[6], currentCam->lookAt[7], currentCam->lookAt[8]);
	//lookAt(cameraLookAt[0], cameraLookAt[1], cameraLookAt[2], cameraLookAt[3], cameraLookAt[4], cameraLookAt[5], cameraLookAt[6], cameraLookAt[7], cameraLookAt[8]);
	//lookAt(camX, camY, camZ, 0,0,0, 0,1,0);
	// use our shader
	glUseProgram(shader.getProgramIndex());

	
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
	float ratio = (1.0f * WinX) / WinY;
	float args[6] = { 0 };

	switch (key) {

	case 27:
		glutLeaveMainLoop();
		break;

	case 'c':
		printf("Camera Spherical Coordinates (%f, %f, %f)\n", alpha, beta, r);
		break;
	case 'm': glEnable(GL_MULTISAMPLE); break;
	case 'n': glDisable(GL_MULTISAMPLE); break;
	case 'w':case 'W':
		if(state != keys['w'])
		{
			player->forward(state);
			keys['w'] = state;
			if (currentCam->GetMovingAttr()) {
				currentCam->SetPlayerMoving(state);
			}
		}
		break;
	case 's':case 'S':
		if (state != keys['s'])
		{
			player->backward(state);
			keys['s'] = state;
			if (currentCam->GetMovingAttr()) {
				currentCam->SetPlayerMoving(state);
			}
		}
		break;
	case 'a':case 'A':
		if (state != keys['a'])
		{
			player->left(state);
			keys['a'] = state;
			
		}
		break;
	case 'd':case 'D':
		if (state != keys['d'])
		{
			player->right(state);
			keys['d'] = state;
			
		}
		break;
	case '1':
		if (state != keys['1'])
		{
			currentCam = (Camera*)myGameObjects[firstCameraIndex];
			currentCam->SetCameraType(CamType_t::perspective_t);
			args[0] = 53.13f; // angle
			args[1] = ratio; // ratio w/h
			args[2] = 0.1f; //near 
			args[3] = 1000.0f; //far
			currentCam->SetProjArgs(args);
			r = currentCam->GetCameraRadius();
			
		}
		break;
	case '2':
		if (state != keys['2'])
		{
			currentCam = (Camera*)myGameObjects[firstCameraIndex];
			currentCam->SetCameraType(CamType_t::ortho_t);
			args[0] = -2.0f; // left
			args[1] = 2.0f; // right
			args[2] = -2.0f / ratio; //bottom 
			args[3] = 2.0f / ratio; //up
			args[4] = -10.0f; //near
			args[5] = 10.0f; //far
			currentCam->SetProjArgs(args);
			r = currentCam->GetCameraRadius();
		}
		break;
	case '3':
		if (state != keys['3'])
		{
			currentCam = (Camera*)myGameObjects[firstCameraIndex+1];
			currentCam->SetCameraType(CamType_t::perspective_t);
			args[0] = 53.13f; // angle
			args[1] = ratio; // ratio w/h
			args[2] = 0.1f; //near 
			args[3] = 1000.0f; //far
			currentCam->SetProjArgs(args);
			r = currentCam->GetCameraRadius();
		}
		break;
	case '4':
		if (state != keys['4'])
		{
			currentCam = (Camera*)myGameObjects[firstCameraIndex+1];
			currentCam->SetCameraType(CamType_t::ortho_t);
			args[0] = -30.0f; // left
			args[1] = 30.0f; // right
			args[2] = -30.0f / ratio; //bottom 
			args[3] = 30.0f / ratio; //up
			args[4] = -150.0f; //near
			args[5] = 150.0f; //far
			currentCam->SetProjArgs(args);
			r = currentCam->GetCameraRadius();
			
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

	float deltaX, deltaY;
	float rAux = 0.0f;


	deltaX = xx - startX;
	deltaY = yy - startY;

	startX = xx;
	startY = yy;
	
	cout << "DELTA X = " << deltaX << endl;
	// left mouse button: move camera
	if (tracking == 1 && currentCam->GetMovingAttr()) {
		alpha -= (deltaX * 0.003f);
		beta += (deltaY* 0.003f);
	}
	currentCam->alpha = alpha;
	currentCam->beta = beta;

}


void mouseWheel(int wheel, int direction, int x, int y) {

	r += direction * 0.1f;
	if (r < 0.1f)
		r = 0.1f;

	camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camY = r *   						     sin(beta * 3.14f / 180.0f);
	cameraLookAt[0] = camX;
	cameraLookAt[1] = camY;
	cameraLookAt[2] = camZ;


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
	model_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_model");

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
	playerCar->transform.setPosition(0,.1,0);
	myGameObjects.push_back((GameObject*)playerCar);
	player = playerCar;


	Cube* cube = new Cube();
	cube->transform.setLocalScale(3,.6,1.7);
	cube->transform.setLocalPosition(.5,.2,0);
	cube->transform.setParent(&(playerCar->transform));
	cube->setColor(1.0f,0.0f,0.0f, 1.0f);
	myGameObjects.push_back((GameObject*)cube);

	cube = new Cube();
	cube->transform.setLocalScale(1.4, .6, 1.7);
	cube->transform.setLocalPosition(.69, .775, 0);
	cube->transform.setParent(&(playerCar->transform));
	cube->setColor(1.0f, 0.0f, 0.0f, 1.0f);
	myGameObjects.push_back((GameObject*)cube);

	cube = new Cube();
	cube->transform.setLocalScale(.8, .8, 1.7);
	cube->transform.setLocalPosition(1.4, .5, 0);
	cube->transform.setRotation(0, 0, 45);
	cube->transform.setParent(&(playerCar->transform));
	cube->setColor(1.0f, 0.0f, 0.0f, 1.0f);
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
	cube->transform.setPosition(0, -0.5, 0);
	cube->setColor(0.0f, 0.3f, 0.0f, 1.0f);
	myGameObjects.push_back((GameObject*)cube);

	cube = new Cube();
	cube->transform.setScale(mapSize, 5, 1);
	cube->transform.setPosition(0,0, mapSize/2);
	cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
	myGameObjects.push_back((GameObject*)cube);

	cube = new Cube();
	cube->transform.setScale(mapSize, 5, 1);
	cube->transform.setPosition(0, 0, -mapSize / 2);
	cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
	myGameObjects.push_back((GameObject*)cube);

	cube = new Cube();
	cube->transform.setScale( 1,5 , mapSize);
	cube->transform.setPosition(mapSize / 2, 0, 0);
	cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
	myGameObjects.push_back((GameObject*)cube);

	cube = new Cube();
	cube->transform.setScale(1, 5, mapSize);
	cube->transform.setPosition(-mapSize / 2, 0, 0);
	cube->setColor(0.0f, 0.3f, 0.3f, 1.0f);
	myGameObjects.push_back((GameObject*)cube);

	Orange* orange = new Orange(mapSize);
	orange->transform.setPosition(1, .5, 0);
	myGameObjects.push_back((GameObject*)orange);

	firstCameraIndex = myGameObjects.size();
	FollowCamera* followCamera = new FollowCamera( &(player->transform));
	myGameObjects.push_back((GameObject*)followCamera);

	FixedTopDownCamera* fixedCamera = new FixedTopDownCamera(positionTopDownCamera);
	myGameObjects.push_back((GameObject*)fixedCamera);
	
	currentCam = followCamera;
	r = currentCam->GetCameraRadius();

	//Lights
	LightSource* lightSource;
	/*lightSource = new LightSource(LightType::global);
	lightSource->light->color[0] = 0.3f;
	lightSource->light->color[1] = 0.3f;
	lightSource->light->color[2] = 0.3f;
	lightSource->light->position[1] = 3.0f;
	myGameObjects.push_back((GameObject*)lightSource);*/
	
	lightSource = new LightSource(LightType::point);
	lightSource->light->color[0] = 1;
	lightSource->light->color[1] = 1;
	lightSource->light->color[2] = 1;
	lightSource->light->position[1] = 1.0f;
	lightSource->light->linear = 0.2f;
	myGameObjects.push_back((GameObject*)lightSource);



	//GameObject::n_lights = 2;
	

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



