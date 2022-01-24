#include "TextElement.h"
#include "Canvas.h"

using namespace GameObjectSpace;
using namespace std;

void TextElement::update()
{	
	//change this
	// use local position
	float x= 0, y=0, sc=0;
	Canvas* ownerAux = nullptr;
	if (pan!=nullptr) {

		ownerAux = (Canvas*)pan->owner;
		float* pos = ownerAux->meshPositions.at(pan->mesh_index);
		x = ownerAux->transform.globalTransform.pos[0] + pan->position[0];
		y = ownerAux->transform.globalTransform.pos[1] + pan->position[1];
	}
	else {
		ownerAux = (Canvas*)owner;
		x = (*owner).transform.globalTransform.pos[0];
		y = (*owner).transform.globalTransform.pos[1];
	}


	x = (x+position[0]) / 100.0f * ownerAux->windowX;
	y = (y+position[1]) / 100.0f * ownerAux->windowY;
	sc = position[2] / 100 * (ownerAux->windowX/1000);
	cout << sc << endl;
	if(isActive)
		RenderText(*((Canvas*)owner)->shader, text, x, y, sc, simpleColor[0], simpleColor[1], simpleColor[2], simpleColor[3]);

}

void TextElement::init()
{
}

void TextElement::setActive(bool b) {
	Component::setActive(b);
}
