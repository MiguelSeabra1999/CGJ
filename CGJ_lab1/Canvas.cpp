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
	pos[0] = transform.globalTransform.pos[0];
	pos[1] = transform.globalTransform.pos[1];

	meshPositions.push_back(pos);

	float * scale = new float[2];
	scale[0] = 1.0f;
	scale[1] = 1.0f;
	meshScales.push_back(scale);

	float * w_h = new float[2];
	w_h[0] = width;
	w_h[1] = height;
	meshWidthHeight.push_back(w_h);

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
	GameObject::update();


}

void Canvas::SetScale(float x, float y)
{
	scale_x = x;
	scale_y = y;
}

void Canvas::DrawUI() {
	GameObject::DrawUI();
	// activate corresponding render state	

	
	
	glUseProgram(shaderIndex);

	computeDerivedMatrix(PROJ_VIEW_MODEL);
	glUniformMatrix4fv(glGetUniformLocation(shaderIndex, "m_pvm"), 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);

	


	// iterate through all characters
	//cout << "start" << endl;
	
	for (int i = 0; i<myMeshes.size();i++)
	{
		GLint texId = *(meshTextures[i]);
		if (texId != -1)
			glActiveTexture(GL_TEXTURE0); //no frag shader o uniform sampler foi carregado com TU0
		//cout << "ole= " << i << endl;
		glBindVertexArray(myMeshes[i].vao);
		glUniform4f(glGetUniformLocation(shaderIndex, "textColor"), myMeshes[i].mat.diffuse[0], myMeshes[i].mat.diffuse[1], myMeshes[i].mat.diffuse[2], myMeshes[i].mat.diffuse[3]);
		if (texId != -1)
			glUniform1i(glGetUniformLocation(shaderIndex, "isText"), 1);
		else
			glUniform1i(glGetUniformLocation(shaderIndex, "isText"), 0);
		float xpos = meshPositions[i][0];
		float ypos = meshPositions[i][1];
		//cout << "x,y =" << xpos << ", " << ypos << endl;
		float w = meshWidthHeight[i][0];
		float h = meshWidthHeight[i][1];
		//cout << "w,h =" << w << ", " << h << endl;

		float scale_x_aux = meshScales[i][0];
		float scale_y_aux = meshScales[i][1];
		//cout << "scx,scy =" << scale_x_aux << ", " << scale_x_aux << endl;
		// update VBO for each character
		float vertices[6][4] = {
			{ (xpos)*scale_x_aux,     (ypos + h)*scale_y_aux,   0.0f, 0.0f },
			{ (xpos)*scale_x_aux,     (ypos)*scale_y_aux,       0.0f, 1.0f },
			{ (xpos + w)*scale_x_aux, (ypos)*scale_y_aux,       1.0f, 1.0f },

			{ (xpos)*scale_x_aux,     (ypos + h)*scale_y_aux,   0.0f, 0.0f },
			{ (xpos + w)*scale_x_aux, (ypos)*scale_y_aux,       1.0f, 1.0f },
			{ (xpos + w)*scale_x_aux, (ypos + h)*scale_y_aux,   1.0f, 0.0f }
		};

		/** /for (int j = 0; j < 6; j++) {
			cout << "vertices text = " << vertices[j][0] << ", " << vertices[j][1] << ", " << vertices[j][2] << ", " << vertices[j][3] << ", " << endl;
		
		}
		cout << "over" << endl;/**/
		// render glyph texture over quad
		if(texId!=-1)
			glBindTexture(GL_TEXTURE_2D, *(GameObject::textureIds[texId]));
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, myMeshes[i].vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);



}