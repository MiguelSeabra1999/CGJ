#include "TextElement.h"
#include "Canvas.h"

using namespace GameObjectSpace;
using namespace std;

void TextElement::update()
{	
	//change this
	// use local position
	float x= 0, y=0;
	if (pan!=nullptr) {

		Canvas* ownerAux = (Canvas*)pan->owner;
		float* pos = ownerAux->meshPositions.at(pan->mesh_index);
		x = ownerAux->transform.globalTransform.pos[0] + pan->position[0];
		y = ownerAux->transform.globalTransform.pos[1] + pan->position[1];
	}
	else {
		x = (*owner).transform.globalTransform.pos[0];
		y = (*owner).transform.globalTransform.pos[1];
	}

	RenderText(*((Canvas*)owner)->shader, text, x + position[0], y + position[1], position[2], simpleColor[0], simpleColor[1], simpleColor[2], simpleColor[3]);

}

void TextElement::init()
{
}
