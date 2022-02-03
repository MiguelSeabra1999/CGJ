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

MyMesh cube;


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
bool mouseLock = false;
Scene* scene;

map<char, bool> keys = {
	{ 'w', false },
	{ 'a', false },
	{ 's', false },
	{ 'd', false },
	{ 'q', false },
	{'r' , false},
	{ ' ', false},
	{ 'z', false},

};

// Camera constants and values for easy definition
float positionTopDownCamera[3] = { 0.0f, 70.0f, 0.0f };
float positionTopDownCamera2[3] = { 0.0f, 5.0f, 0.0f };
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
	-200.0f, //near 
	200.0f, //far
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
	-50.0f, // left
	50.0f, // right
	-50.0f, // bottom
	50.0f, // top
	-50.0f, //near 
	50.0f, //far
};

void UIrenderStep(int f);
void lightsStep();


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

	float ratio = 1.0f;
	// Prevent a divide by zero, when window is too short
	if(h == 0)
		h = 1;
	// set the viewport to be the entire window
	glViewport(0, 0, w, h);
	
	WinX = w;
	WinY = h;
	scene->currentCam->SetWidthHeightProj(WinX, WinY);
	scene->currentCam->UpdateProjection();
	scene->SetWindow(WinX, WinY);

	glEnable(GL_STENCIL_TEST);
	//glClear(GL_STENCIL_BUFFER_BIT);

	
}


// ------------------------------------------------------------
//
// Render stufff
// 


void renderStep(Camera * currentCam, bool reversed) {

	//############ UPDATE SCENE ####################;

	loadIdentity(VIEW);
	loadIdentity(MODEL);
	// set the camera using a function similar to gluLookAt
	lookAt(currentCam->lookAt[0], currentCam->lookAt[1], currentCam->lookAt[2], currentCam->lookAt[3], currentCam->lookAt[4], currentCam->lookAt[5], currentCam->lookAt[6], currentCam->lookAt[7], currentCam->lookAt[8]);



	// use our shader
	glUseProgram(shader.getProgramIndex());

	if (useFog)
		glUniform1f(fogginess_uniformId, fogginess);
	else
		glUniform1f(fogginess_uniformId, 0);
	glUniform4fv(fogColor_uniformId, 1, fogColor);
	

	//the glyph contains background colors and non-transparent for the actual character pixels. So we use the blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//Update light positions
	for (int i = 0; i < GameObject::lights.size(); i++)
	{
		if (GameObject::lights[i]->on) {
			multMatixTransposeByVector(GameObject::lights[i]->light->eye_coords_direction, mMatrix[VIEW], GameObject::lights[i]->light->direction);
			multMatixTransposeByVector(GameObject::lights[i]->light->eye_coords_position, mMatrix[VIEW], GameObject::lights[i]->light->position);

		}
	}

	scene->sendLightsToShader();
	lightsStep();

	//############ DRAW SCENE ####################;

	if(!reversed)
	{
		if (scene->gameObjects.size() > 0)
			scene->gameObjects[0]->draw(false);
	}
	scene->draw(reversed);
	//glDepthMask(GL_TRUE);

	if (!shader.isProgramValid()) {
		printf("Program Not Valid!\n");
		exit(1);
	}

	//Render text (bitmap fonts) in screen coordinates. So use ortoghonal projection with viewport coordinates.
	glBindTexture(GL_TEXTURE_2D, 0);

}
void lightsStep() {


	//glDisable(GL_DEPTH_TEST);
	//the glyph contains background colors and non-transparent for the actual character pixels. So we use the blending
	



	// UI STUFF

	//glEnable(GL_DEPTH_TEST);
	//glDisable(GL_BLEND);
}

void UIrenderStep(int st) {
	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	pushMatrix(MODEL);
	loadIdentity(MODEL);
	int m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);

	pushMatrix(PROJECTION);
	loadIdentity(PROJECTION);
	pushMatrix(VIEW);
	loadIdentity(VIEW);
	ortho(m_viewport[0], m_viewport[0] + m_viewport[2] - 1, m_viewport[1], m_viewport[1] + m_viewport[3] - 1, -1, 1);
	scene->updateAndDrawUI(st);
	popMatrix(PROJECTION);
	popMatrix(VIEW);
	popMatrix(MODEL);
	glDisable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
}

void restartScene();
void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	if (scene->restartScene)
		restartScene();
	scene->timeUtil->updateCycle();
	GLint loc = 0;

	FrameCount++;

	scene->update();


	if (scene->rearView) {
		glEnable(GL_STENCIL_TEST);
		glEnable(GL_DEPTH_TEST);
		glClearStencil(0x0);
		glClear(GL_STENCIL_BUFFER_BIT);

		glStencilFunc(GL_ALWAYS, 0x1, 0x1);
		glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
		UIrenderStep(1);
	
		glClear(GL_DEPTH_BUFFER_BIT);
		glStencilFunc(GL_NOTEQUAL, 0x1, 0x1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		scene->secondCam->UpdateProjection();
		renderStep(scene->secondCam, false);

		glClear(GL_STENCIL_BUFFER_BIT);

		glStencilFunc(GL_ALWAYS, 0x1, 0x1);
		glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
		UIrenderStep(2);

		glClear(GL_DEPTH_BUFFER_BIT);
		glStencilFunc(GL_EQUAL, 0x1, 0x1);
		scene->thirdCam->UpdateProjection();
		renderStep(scene->thirdCam, false);
		glDisable(GL_STENCIL_TEST);


	}
	else {
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_STENCIL_BUFFER_BIT);
		glDisable(GL_STENCIL_TEST);
		
		scene->currentCam->UpdateProjection();
		renderStep(scene->currentCam, true);
		renderStep(scene->currentCam, false);
	}

	glDisable(GL_STENCIL_TEST);
	glDisable(GL_DEPTH_TEST);
	UIrenderStep(0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	
	
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
void processKeys(unsigned char key, bool state);
void restartScene()
{
	/**/
	cout << "restart" << endl;
	scene->destroy();
	scene->loadTextures();
	createGameObjects();
	/**/
	//calling already pressed key events on new scene
	map<char, bool>::iterator it;
	keys['r'] = false;
	for (it = keys.begin(); it != keys.end(); it++)
	{
		if (keys[it->first])
		{
			processKeys(it->first, true);
		}
	}
	//setting the keys to zero
	keys['r'] = true;
	for (it = keys.begin(); it != keys.end(); it++)
	{
		keys[it->first] = false;
	}
}
// ------------------------------------------------------------
//
// Events from the Keyboard
//
void processKeys(unsigned char key, bool state)
{

	switch (key) {

	case 27:
		glutLeaveMainLoop();
		break;
	case 'r':case'R':
		if (state != keys['r'])
		{
		
			restartScene();
		}
		break;
	case 'c':
		//printf("Camera Spherical Coordinates (%f, %f, %f)\n", alpha, beta, r);
		break;
	case 'm': glEnable(GL_MULTISAMPLE); break;
	case 'n': glDisable(GL_MULTISAMPLE); break;
	case 'w':case 'W':
		if(state != keys['w'])
		{
			if(scene->currentCam->GetLerp())
				mouseLock = state;
			player->forward(state);
			keys['w'] = state;
			if (scene->currentCam->GetMovingAttr()) {
				scene->currentCam->SetPlayerMoving(state);
			}
		}
		break;
	case 's':case 'S':
		if (state != keys['s'])
		{
			if (scene->currentCam->GetLerp())
				mouseLock = state;

			player->backward(state);
			keys['s'] = state;
			if (scene->currentCam->GetMovingAttr()) {
				scene->currentCam->SetPlayerMoving(state);
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
			if (scene->currentCam->GetMovingAttr()) {
				scene->currentCam->SetLerp(!scene->currentCam->lerp);
			}
		}
		break;
	case 'f':case 'F':
		if (state != keys['f'])
		{
			scene->currentCam->SetFollow(!scene->currentCam->follow);
		}
		break;
	case '1':
		if (state != keys['1'])
		{
			scene->changeMainCamera('1');
			scene->currentCam->SetCameraCharacteristics(CamType_t::perspective_t, followCameraPerspectiveArguments, WinX, WinY);
		}
		break;
	case '2':
		if (state != keys['2'])
		{
			scene->changeMainCamera('2');
			scene->currentCam->SetCameraCharacteristics(CamType_t::ortho_t, followCameraOrthoArguments, WinX, WinY);
		}
		break;
	case '3':
		if (state != keys['3'])
		{
			scene->changeMainCamera('3');
			scene->currentCam->SetCameraCharacteristics(CamType_t::perspective_t, fixedCameraPerspectiveArguments, WinX, WinY);

		}
		break;
	case '4':
		if (state != keys['4'])
		{
			scene->changeMainCamera('4');
			scene->currentCam->SetCameraCharacteristics(CamType_t::ortho_t, fixedCameraOrthoArguments, WinX, WinY);
		}
		break;
	case '5':
		if (state != keys['5'])
		{
			scene->rearView = !scene->rearView;
		}
		break;
	case 'q':case'Q':
		if(state != keys['q'])
		{
			toggleFogginess();
		}
		break;

	case 'h':case'H':
		if (state != keys['h'])
		{
			for(GameObject * obj : scene->uiElements){
				obj->SetActive(!obj->IsActive());
			}
		}
		break;
	case 'u':case'U':
		if (state != keys['u'])
		{
			scene->useGizmos = !scene->useGizmos;
			//cout << carScene->useGizmos << endl;
		}
		break;
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
			/** /for (GameObject* u : carScene->uiElements) {
				if (u->GetUI()) {
					u->SetActive(!u->IsActive());
				}
			}
			break;*/
		}
		/**/
		break;
	case ' ':
		if (state != keys[' '])
		{
			player->handbreak(state);
			keys[' '] = state;
		}
		break;
	case 'z':case'Z':
		if(state != keys['z'])
		{
			if(state)
				scene->paused = !scene->paused;
			keys['z'] = state;
			
		}
		break;	
	}	
}

void processKeysDown(unsigned char key, int xx, int yy)
{
	processKeys(key,  true);
}
void processKeysUp(unsigned char key, int xx, int yy)
{
	processKeys(key,  false);
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
	if((!mouseLock) && player->velocity==0 || !scene->currentCam->lerp) {
	
		deltaX = xx - startX;
		deltaY = yy - startY;

		startX = xx;
		startY = yy;
	
		// left mouse button: move camera
		if (tracking == 1 && scene->currentCam->GetMovingAttr()) {
			alpha -= (deltaX * 0.003f);
			beta += (deltaY* 0.003f);
		}
		scene->currentCam->alpha = alpha;
		scene->currentCam->beta = beta;
	
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
	glBindAttribLocation(shader.getProgramIndex(), TANGENT_ATTRIB, "tangent");

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
	scene = new CarScene();
	scene->SetUIShader(&shaderText);
	scene->SetWindow(WinX, WinY);
	scene->init(shader.getProgramIndex());
	player = scene->player;

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


	float amb[] = { 0.2f, 0.15f, 0.1f, 1.0f };
	float diff[] = { 0.8f, 0.6f, 0.4f, 1.0f };
	float spec[] = { 0.8f, 0.8f, 0.8f, 1.0f };

	float amb1[] = { 0.3f, 0.0f, 0.0f, 1.0f };
	float diff1[] = { 0.8f, 0.1f, 0.1f, 1.0f };
	float spec1[] = { 0.3f, 0.3f, 0.3f, 1.0f };


	float emissive[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float shininess = 100.0f;
	int texcount = 0;

	// create geometry and VAO of the cube
	cube = createCube();
	memcpy(cube.mat.ambient, amb1, 4 * sizeof(float));
	memcpy(cube.mat.diffuse, diff1, 4 * sizeof(float));
	memcpy(cube.mat.specular, spec1, 4 * sizeof(float));
	memcpy(cube.mat.emissive, emissive, 4 * sizeof(float));
	cube.mat.shininess = shininess;
	cube.mat.texCount = texcount;
	myMeshes.push_back(cube);


	scene->loadTextures();
	// some GL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glClearColor(fogColor[0],fogColor[1],fogColor[2], 1.0f);
	glDepthMask(GL_TRUE);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
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




