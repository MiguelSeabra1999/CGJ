#include "Panel.h"
#include "Canvas.h"
#include "Scene.h"
using namespace GameObjectSpace;

void Panel::update()
{
    updateHeart();
    updatePositions();
    updateScales();
    updateColors();
    updateWidthHeight();
    updateRotation();
    updateStencilTypes();
}

void Panel::updateHeart() {
    if (heart == true) {
        int hp = owner->currentScene->player->hp;
        if (hp >= 0) {
            if (hp + 1 == mesh_index) {
                isAct = false;
            }
        }
    }


}

void Panel::updatePositions()
{
    Canvas* ownerAux = (Canvas*)owner;
    float * pos = ownerAux->meshPositions.at(mesh_index);
    pos[0] = ownerAux->transform.globalTransform.pos[0] + position[0];
    pos[1] = ownerAux->transform.globalTransform.pos[1] + position[1];
}

void Panel::updateScales()
{
    Canvas* ownerAux = (Canvas*)owner;
    float* sc = ownerAux->meshScales.at(mesh_index);
    sc[0] = scale[0];
    sc[1] = scale[1];
}

void Panel::updateWidthHeight()
{
    Canvas* ownerAux = (Canvas*)owner;
    float* w_h = ownerAux->meshWidthHeight.at(mesh_index);
    w_h[0] = width;
    w_h[1] = height;
}

void Panel::updateRotation()
{
    Canvas* ownerAux = (Canvas*)owner;
    float* rot = ownerAux->meshRotations.at(mesh_index);
    *rot = rotation + (ownerAux->rotation);
}

void Panel::updateStencilTypes() {
    Canvas* ownerAux = (Canvas*)owner;
    int* st = ownerAux->stencilTypes.at(mesh_index);
    *st = stencilType;
}

void Panel::updateColors()
{
    (*owner->getMyMeshes())[mesh_index].mat.diffuse[0] = simpleColor[0];
    (*owner->getMyMeshes())[mesh_index].mat.diffuse[1] = simpleColor[1];
    (*owner->getMyMeshes())[mesh_index].mat.diffuse[2] = simpleColor[2];
    (*owner->getMyMeshes())[mesh_index].mat.diffuse[3] = simpleColor[3];
}

void Panel::init()
{
    MyMesh * amesh = new MyMesh();
    Material* mat = new Material();

	Canvas* ownerAux = ((Canvas*)owner);

    vector<struct MyMesh> * aux = ownerAux->getMyMeshes();

    initMaterial(mat, simpleColor[0], simpleColor[1], simpleColor[2], simpleColor[3]);
    (* amesh).mat = *mat;
    (*aux).push_back(*amesh);

	float* pos = new float[2];
	ownerAux->meshPositions.push_back(pos);

    mesh_index = getIndex(ownerAux->meshPositions, pos);

    float* sc = new float[2];
    ownerAux->meshScales.push_back(sc);

    float* w_h = new float[2];
    ownerAux->meshWidthHeight.push_back(w_h);

    float* rot = new float;
    *rot = rotation;
    ownerAux->meshRotations.push_back(rot);

    int* st = new int;
    *st = stencilType;
    ownerAux->stencilTypes.push_back(st);

    bool* act = new bool;
    *act = isAct;
    ownerAux->meshActives.push_back(act);

    updatePositions();
    updateScales();
    updateWidthHeight();
    updateRotation();
    updateStencilTypes();
    ownerAux->meshTextures.push_back(&textureId);
    ownerAux->generateMesh(mesh_index);
}

void Panel::initMaterial(Material * m,float r, float g, float b, float a) {
    m->diffuse[0] = r;
    m->diffuse[1] = g;
    m->diffuse[2] = b;
    m->diffuse[3] = a;
}


int Panel::getIndex(vector<float*> v, float * K)
{
    auto it = find(v.begin(), v.end(), K);
    if (it != v.end())
    {
        int index = it - v.begin();
        return index;
    }
    else {
        return -1;
    }
}
