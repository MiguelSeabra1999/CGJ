#include "Canvas.h"
using namespace GameObjectSpace;

void Canvas::SetUIGlobalPosition(float x, float y)
{
	transform.setPosition(x, y, 0.0f);
}

void Canvas::SetUILocalPosition(float x, float y)
{
	transform.setLocalPosition(x, y, 0.0f);
}

void Canvas::initDraw(GLuint shader)
{


	MyMesh * amesh = new MyMesh();
	GameObject::initMaterial();
	(*amesh).mat = *material;
	myMeshes.push_back(*amesh);
	float * pos= new float[2];
	pos[0] = GameObject::transform.globalTransform.pos[0];
	pos[1] = GameObject::transform.globalTransform.pos[1];

	meshPositions.push_back(pos);

	float * scale = new float[2];
	scale[0] = 1.0f;
	scale[1] = 1.0f;
	meshScales.push_back(scale);

	float * w_h = new float[2];
	w_h[0] = width;
	w_h[1] = height;
	meshWidthHeight.push_back(w_h);

	float * rot = new float;
	*rot = rotation;
	meshRotations.push_back(rot);

	int* stencilT = new int;
	*stencilT = stencilType;
	stencilTypes.push_back(stencilT);

	bool* act = new bool;
	*act = isActive;
	meshActives.push_back(act);

	meshTextures.push_back(&textureId);
	GameObject::initDraw(shader);
	generateMesh(0);
	

}

void Canvas::generateMesh(int i) {

	glGenVertexArrays(1, &(myMeshes[i].vao));
	glGenBuffers(1, &(myMeshes[i].vbo));
	glBindVertexArray((myMeshes[i].vao));
	glBindBuffer(GL_ARRAY_BUFFER, (myMeshes[i].vbo));
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Canvas::update()
{
	//cout << "updating ui" << endl;
	//updateActive();
	GameObject::update();


}


void Canvas::SetScale(float x, float y)
{
	scale_x = x;
	scale_y = y;
}

void Canvas::DrawUI(int stencType) {
	
	GameObject::DrawUI(stencType);
	// activate corresponding render state	

	glUseProgram(shaderIndex);


	// iterate through all characters
	//cout << "start" << endl;


	
	for (int i = 0; i<myMeshes.size();i++)
	{
		// the first mesh always belongs to the canvas, 
		// the other meshes belong to its components, if it has them
		// the only component that doesn't have them is the text, 
		// as it is rendered in a slightly different way
		if (((i == 0 && isActive) || (i!=0 && components[i-1]->isActive())) && (*(stencilTypes.at(i))) == stencType) {

			pushMatrix(MODEL);
			loadIdentity(MODEL);
			float * r = meshRotations[i];
			//percentages of screen width and height
			float xpos = (meshPositions[i][0])/100 * windowX;
			float ypos = (meshPositions[i][1])/100 * windowY;

			float w = (meshWidthHeight[i][0])/100 * windowX;
			float h = (meshWidthHeight[i][1])/100 * windowY;

			float scale_x_aux = meshScales[i][0];
			float scale_y_aux = meshScales[i][1];
	

			//drawing the poligon at position the specified center
			translate(MODEL, xpos+(w/2.0f), ypos+(h/2.0f), 0.0f);
			//rotating the model r degrees
			rotate(MODEL,*r , 0, 0 , 1);
			//using scale on the ui element
			scale(MODEL, w, h, 1);

			computeDerivedMatrix(PROJ_VIEW_MODEL);
			glUniformMatrix4fv(glGetUniformLocation(shaderIndex, "m_pvm"), 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
			GLint texId = *(meshTextures[i]);
			if (texId != -1)
				glActiveTexture(GL_TEXTURE0); //no frag shader o uniform sampler foi carregado com TU0
		
			glBindVertexArray(myMeshes[i].vao);
			glUniform4f(glGetUniformLocation(shaderIndex, "textColor"), myMeshes[i].mat.diffuse[0], myMeshes[i].mat.diffuse[1], myMeshes[i].mat.diffuse[2], myMeshes[i].mat.diffuse[3]);
			if (texId != -1)
				glUniform1i(glGetUniformLocation(shaderIndex, "isText"), 2);
			else
				glUniform1i(glGetUniformLocation(shaderIndex, "isText"), 0);

			// these vertexes are created taking into to account the earliear translation
			float vertices[6][4] = {
				{-0.5f,  0.5f, 0.0f, 0.0f  },
				{-0.5f, -0.5f, 0.0f, 1.0f  },
				{ 0.5f, -0.5f, 1.0f, 1.0f  },

				{-0.5f,  0.5f, 0.0f, 0.0f  },
				{0.5f, -0.5f, 1.0f, 1.0f  },
				{ 0.5f, 0.5f, 1.0f, 0.0f  },
			};
			if(texId!=-1)
				glBindTexture(GL_TEXTURE_2D, *(GameObject::textureIds[texId]));
			// update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, myMeshes[i].vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
		
		
			popMatrix(MODEL);
		}
	}
	for (Component* c : components) {
		if (c->isTextElement() && c->isActive()) {
			TextElement* t = (TextElement*)c;
			if(t->stencilType == stencType)
				RenderText(*shader, t->text, t->x, t->y, t->sc, t->simpleColor[0], t->simpleColor[1], t->simpleColor[2], t->simpleColor[3]);
		}
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);



}