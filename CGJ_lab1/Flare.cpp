#include "Flare.h"
#include "LightSource.h"

using namespace GameObjectSpace;


void Flare::render_flare(int lx, int ly, int* m_viewport) {  //lx, ly represent the projected position of light on viewport


	glUseProgram(shaderIndex);

	int     dx, dy;          // Screen coordinates of "destination"
	int     px, py;          // Screen coordinates of flare element
	int		cx, cy;
	float    maxflaredist, flaredist, flaremaxsize, flarescale, scaleDistance;
	int     width, height, alpha;    // Piece parameters;
	int     i;
	float	diffuse[4];
	
	GLint loc;

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int screenMaxCoordX = m_viewport[0] + m_viewport[2] - 1;
	int screenMaxCoordY = m_viewport[1] + m_viewport[3] - 1;

	//viewport center
	cx = m_viewport[0] + (int)(0.5f * (float)m_viewport[2]) - 1;
	cy = m_viewport[1] + (int)(0.5f * (float)m_viewport[3]) - 1;

	// Compute how far off-center the flare source is.
	maxflaredist = sqrt(cx * cx + cy * cy);
	flaredist = sqrt((lx - cx) * (lx - cx) + (ly - cy) * (ly - cy));
	scaleDistance = (maxflaredist - flaredist) / maxflaredist;
	flaremaxsize = (int)(m_viewport[2] * fMaxSize);
	flarescale = (int)(m_viewport[2] * fScale);

	// Destination is opposite side of centre from source

	dx = clampi(cx + (cx - lx), m_viewport[0], screenMaxCoordX);
	dy = clampi(cy + (cy - ly), m_viewport[1], screenMaxCoordY);

	//cout << "destination = " << dx << ", " << dy << endl;


	
	int count = components.size();

	

		
	if (lx > m_viewport[0] && lx < m_viewport[2]  && ly >m_viewport[1] && ly< m_viewport[3]) {
		for (i = 0; i < count; i++)
		{
			if (components[i]->isFlareElement() && components[i]->isActive()) {
				// Position is interpolated along line between start and destination.
				FlareElement* flare = (FlareElement*)components[i];
				px = (int)((1.0f - flare->getFDistance()) * lx + flare->getFDistance() * dx);
				py = (int)((1.0f - flare->getFDistance()) * ly + flare->getFDistance() * dy);
				//px = clampi(px, m_viewport[0], screenMaxCoordX);
				//py = clampi(py, m_viewport[1], screenMaxCoordY);

				// Piece size are 0 to 1; flare size is proportion of screen width; scale by flaredist/maxflaredist.
				width = (int)(scaleDistance * flarescale * flare->getFSize());

				// Width gets clamped, to allows the off-axis flaresto keep a good size without letting the elements get big when centered.
				if (width > flaremaxsize)  width = flaremaxsize;

				height = (int)((float)m_viewport[3] / (float)m_viewport[2] * (float)width);
				memcpy(diffuse, myMeshes[i].mat.diffuse, 4 * sizeof(float));
				diffuse[3] *= (1.0f-scaleDistance);   //scale the alpha channel
				if (width > 1 && scaleDistance >0.3f)
				{
				
					pushMatrix(MODEL);
					translate(MODEL, (float)(px - width * 0.0f), (float)(py - height * 0.0f), 0.0f);
					//cout << "flare pos = " << (float)(px - width * 0.0f) << ", " << (float)(py - height * 0.0f) << endl;
					scale(MODEL, (float)width, (float)height, 1);
					//cout << "flare scale = " << (float)(width) << ", " << (float)(height) << endl;
					//cout << "vao = " << myMeshes[i].vao << endl;
					computeDerivedMatrix(PROJ_VIEW_MODEL);
					glUniformMatrix4fv(glGetUniformLocation(shaderIndex, "m_pvm"), 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
					GLint texId = *(meshTextures[i]);
					if (texId != -1)
						glActiveTexture(GL_TEXTURE0); //no frag shader o uniform sampler foi carregado com TU0
				
					 

					glBindVertexArray(myMeshes[i].vao);

					glUniform4f(glGetUniformLocation(shaderIndex, "textColor"), diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
					glUniform3f(glGetUniformLocation(shaderIndex, "lightPos"), lightSrc->transform.globalTransform.pos[0], lightSrc->transform.globalTransform.pos[1], lightSrc->transform.globalTransform.pos[2]);
					glUniform4f(glGetUniformLocation(shaderIndex, "lightColor"), lightSrc->light->color[0], lightSrc->light->color[1], lightSrc->light->color[2], lightSrc->light->color[3]);


					if (texId != -1)
						glUniform1i(glGetUniformLocation(shaderIndex, "isText"), 3);
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
					if (texId != -1)
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
		}
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

void Flare::DrawUI() {
	GameObject::DrawUI();

	int m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	render_flare(flarePos[0], flarePos[1], m_viewport);
}

void Flare::initDraw(GLuint shader) {
	GameObject::initDraw(shader);
}
