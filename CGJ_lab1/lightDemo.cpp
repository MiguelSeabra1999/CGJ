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
#include"CarScene.h"

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
vector< GameObject*> myTransparentGameObjects;
PlayerCar* player;

//External array storage defined in AVTmathLib.cpp



GLint pvm_uniformId;
GLint vm_uniformId;
GLint normal_uniformId;
GLint tex_loc, tex_loc1, tex_loc2;
GLint fogginess_uniformId;
GLint fogColor_uniformId;
//################################ FOG ###########################
float fogginess = 0.1f;
float fogColor[4] = { 0.5,0.6,0.7,1 };
bool useFog = true;
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
//Camera* currentCam;
bool mouseLock = false;
CarScene* carScene;

map<char, char> keys = {
	{ 'w', false },
	{ 'a', false },
	{ 's', false },
	{ 'd', false },
	{ 'q', false },
	{ ' ', false}

};

// Camera constants and values for easy definition
float positionTopDownCamera[3] = { 0.0f, 50.0f, 0.0f };
float followCameraPerspectiveArguments[8] = { 
	WinX, // window width
	WinY, // window height
	53.13f, // angle
	0.1f, //near 
	1000.0f, //far
};

float followCameraOrthoArguments[8] = {
	WinX, //window width
	WinY, // window height
	-2.0f, // left
	2.0f, // right
	-2.0f, // bottom
	2.0f, // top
	-10.0f, //near 
	10.0f, //far
};

float fixedCameraPerspectiveArguments[8] = {
	WinX, // window width
	WinY, // window height
	53.13f, // angle
	0.1f, //near 
	1000.0f, //far
};

float fixedCameraOrthoArguments[8] = {
	WinX, //window width
	WinY, // window height
	-30.0f, // left
	30.0f, // right
	-30.0f, // bottom
	30.0f, // top
	-150.0f, //near 
	150.0f, //far
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
	
	WinX = w;
	WinY = h;
	carScene->currentCam->SetWidthHeightProj(WinX, WinY);
	carScene->currentCam->UpdateProjection();
}


// ------------------------------------------------------------
//
// Render stufff
//

void renderScene(void) {
	if (carScene != nullptr) carScene->timeUtil->updateCycle();
	GLint loc;

	FrameCount++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	carScene->currentCam->UpdateProjection();
	
	loadIdentity(VIEW);
	loadIdentity(MODEL);
	// set the camera using a function similar to gluLookAt
	lookAt(carScene->currentCam->lookAt[0], carScene->currentCam->lookAt[1], carScene->currentCam->lookAt[2], carScene->currentCam->lookAt[3], carScene->currentCam->lookAt[4], carScene->currentCam->lookAt[5], carScene->currentCam->lookAt[6], carScene->currentCam->lookAt[7], carScene->currentCam->lookAt[8]);

	// use our shader
	glUseProgram(shader.getProgramIndex());

	if(useFog)
		glUniform1f(fogginess_uniformId, fogginess);
	else
		glUniform1f(fogginess_uniformId, 0);
	glUniform4fv(fogColor_uniformId, 1, fogColor);
	int objId=0; //id of the object mesh - to be used as index of mesh: Mymeshes[objID] means the current mesh

	//the glyph contains background colors and non-transparent for the actual character pixels. So we use the blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//############ UPDATE SCENE ####################;
	carScene->updateAndDraw();
	//glDepthMask(GL_TRUE);

	if (!shader.isProgramValid()) {
		printf("Program Not Valid!\n");
		exit(1);
	}
	
	//Render text (bitmap fonts) in screen coordinates. So use ortoghonal projection with viewport coordinates.
	glDisable(GL_DEPTH_TEST);
	//the glyph contains background colors and non-transparent for the actual character pixels. So we use the blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	int m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);

	//Update light positions
	for (int i = 0; i < GameObject::n_lights; i++)
	{
		multMatixTransposeByVector(GameObject::lights[i]->light->eye_coords_direction, mMatrix[VIEW], GameObject::lights[i]->light->direction);
		multMatixTransposeByVector(GameObject::lights[i]->light->eye_coords_position, mMatrix[VIEW], GameObject::lights[i]->light->position);
	}

	carScene->sendLightsToShader();
	//viewer at origin looking down at  negative z direction
	pushMatrix(MODEL);
	loadIdentity(MODEL);
	pushMatrix(PROJECTION);
	loadIdentity(PROJECTION);
	pushMatrix(VIEW);
	loadIdentity(VIEW);
	ortho(m_viewport[0], m_viewport[0] + m_viewport[2] - 1, m_viewport[1], m_viewport[1] + m_viewport[3] - 1, -1, 1);
	
	RenderText(shaderText, "Controls:",10.0f, 700.0f, 0.5f, 1.0, 1.0f, 1.0f);
	RenderText(shaderText, "Car: WASD, Space", 10.0f, 680.0f, 0.5f, 1.0, 1.0f, 1.0f);
	RenderText(shaderText, "Fog: Q", 10.0f, 660.0f, 0.5f, 1.0, 1.0f, 1.0f);
	RenderText(shaderText, "Lights: I,O,P", 10.0f, 640.0f, 0.5f, 1.0, 1.0f, 1.0f);
	RenderText(shaderText, "Camera: 1,2,3,4", 10.0f, 620.0f, 0.5f, 1.0, 1.0f, 1.0f);
	RenderText(shaderText, "Lerp: L", 10.0f, 600.0f, 0.5f, 1.0, 1.0f, 1.0f);
	RenderText(shaderText, "Follow: F", 10.0f, 580.0f, 0.5f, 1.0, 1.0f, 1.0f);
	popMatrix(PROJECTION);
	popMatrix(VIEW);
	popMatrix(MODEL);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D,0);
	glutSwapBuffers();
}
void toggleFogginess()
{
	if (useFog)
	{
	
		glClearColor(0,0,0, 1.0f);
	}
	else
	{
	
		glClearColor(fogColor[0], fogColor[1], fogColor[2], 1.0f);
	}
	useFog = !useFog;
}
void createGameObjects();
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
	case 'r':case'R':
		/**/
		carScene->destroy();
		carScene->loadTextures();
		createGameObjects();
		/**/
		//carScene->restart();
		break;
	case 'c':
		//printf("Camera Spherical Coordinates (%f, %f, %f)\n", alpha, beta, r);
		break;
	case 'm': glEnable(GL_MULTISAMPLE); break;
	case 'n': glDisable(GL_MULTISAMPLE); break;
	case 'w':case 'W':
		if(state != keys['w'])
		{
			if(carScene->currentCam->GetLerp())
				mouseLock = state;
			player->forward(state);
			keys['w'] = state;
			if (carScene->currentCam->GetMovingAttr()) {
				carScene->currentCam->SetPlayerMoving(state);
			}
		}
		break;
	case 's':case 'S':
		if (state != keys['s'])
		{
			if (carScene->currentCam->GetLerp())
				mouseLock = state;

			player->backward(state);
			keys['s'] = state;
			if (carScene->currentCam->GetMovingAttr()) {
				carScene->currentCam->SetPlayerMoving(state);
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

	case 'l':case 'L':
		if (state != keys['f'])
		{
			if (carScene->currentCam->GetMovingAttr()) {
				carScene->currentCam->SetLerp(!carScene->currentCam->lerp);
			}
		}
		break;
	case 'f':case 'F':
		if (state != keys['f'])
		{
			carScene->currentCam->SetFollow(!carScene->currentCam->follow);
		}
		break;
	case '1':
		if (state != keys['1'])
		{
			carScene->changeMainCamera('1');
			carScene->currentCam->SetCameraCharacteristics(CamType_t::perspective_t, followCameraPerspectiveArguments, WinX, WinY);
		}
		break;
	case '2':
		if (state != keys['2'])
		{
			carScene->changeMainCamera('2');
			carScene->currentCam->SetCameraCharacteristics(CamType_t::ortho_t, followCameraOrthoArguments, WinX, WinY);
		}
		break;
	case '3':
		if (state != keys['3'])
		{
			carScene->changeMainCamera('3');
			carScene->currentCam->SetCameraCharacteristics(CamType_t::perspective_t, fixedCameraPerspectiveArguments, WinX, WinY);

		}
		break;
	case '4':
		if (state != keys['4'])
		{
			carScene->changeMainCamera('4');
			carScene->currentCam->SetCameraCharacteristics(CamType_t::ortho_t, fixedCameraOrthoArguments, WinX, WinY);
		}
		break;
	case 'q':case'Q':
		if(state != keys['q'])
		{
			toggleFogginess();
			break;
		}
	case 'u':case'U':
		if (state != keys['u'])
		{
			carScene->useGizmos = !carScene->useGizmos;
			//cout << carScene->useGizmos << endl;
			break;
		}
	case 'i':case'I':
		if (state != keys['i'])
		{
			GameObject::turnLightOfTypeOff(LightType::directional);
			break;
		}
		break;

	case 'o': case 'O':

		if (state != keys['o']) {
			GameObject::turnLightOfTypeOff(LightType::spot);
			break;
		}
		break;

	case 'p': case 'P':

		if (state != keys['p']) {
			GameObject::turnLightOfTypeOff(LightType::point);
			break;
		}
		break;

		
	case 'y': case 'Y':
		/**/
		if (state != keys['y']) {
			cout << "init = " << carScene->timeUtil->GetInitTime() << endl;
			cout << "delta = " << carScene->timeUtil->GetTimeSinceLastFrame() << endl;
			cout << "frame = " << carScene->timeUtil->GetTimeOfLastFrame() << endl;
			cout << "current = " << carScene->timeUtil->GetTimeSinceInit() << endl;
			break;
		}
		/**/
		break;
	case ' ':
		if (state != keys[' '])
		{
			player->handbreak(state);
			keys[' '] = state;
		}
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
		}
		else {
		}
		tracking = 0;
	
	}

	
}

// Track mouse motion while buttons are pressed

void processMouseMotion(int xx, int yy)
{

	float deltaX, deltaY;
	float rAux = 0.0f;
	if((!mouseLock) && player->velocity==0 || !carScene->currentCam->lerp) {
	
		deltaX = xx - startX;
		deltaY = yy - startY;

		startX = xx;
		startY = yy;
	
		// left mouse button: move camera
		if (tracking == 1 && carScene->currentCam->GetMovingAttr()) {
			alpha -= (deltaX * 0.003f);
			beta += (deltaY* 0.003f);
		}
		carScene->currentCam->alpha = alpha;
		carScene->currentCam->beta = beta;
	
	}


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
	glBindAttribLocation(shader.getProgramIndex(), TEXTURE_COORD_ATTRIB, "texCoord");

	glLinkProgram(shader.getProgramIndex());

	pvm_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_pvm");
	vm_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_viewModel");
	normal_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_normal");
	fogginess_uniformId = glGetUniformLocation(shader.getProgramIndex(), "fogginess");
	



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
	carScene = new CarScene();
	carScene->init(shader.getProgramIndex());
	player = carScene->player;

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
	carScene->loadTextures();
	// some GL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glClearColor(fogColor[0],fogColor[1],fogColor[2], 1.0f);
	glDepthMask(GL_TRUE);
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
	//glutMouseWheelFunc ( mouseWheel ) ;
	

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




