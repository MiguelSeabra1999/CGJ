#include "TextElement.h"
#include "UserInterface.h"

using namespace GameObjectSpace;
using namespace std;

void TextElement::update()
{	
	//change this
	// use local position
	RenderText(((UserInterface*)owner)->shader, "Controls:", 10.0f, 700.0f, 0.5f, 1.0, 1.0f, 1.0f);
	//RenderText(((UserInterface*)owner)->shader, text, position[0], position[1], position[2], simpleColor[0], simpleColor[1], simpleColor[2]);

}

void TextElement::init()
{
}
