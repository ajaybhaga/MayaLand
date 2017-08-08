#include "World.h"

using namespace std;

unsigned const int World::ON_MOUSE_LEFT_DOWN = 1;
unsigned const int World::ON_MOUSE_LEFT_UP = 2;

World::World()
{
}

World::~World() {
    if (heightMap)
        delete heightMap;
}

Camera World::getCamera() {
    return camera;
}

void World::draw()
{
    list<Object*> objectList;
    list<Object*> outlineObjectList;

    // Load static scene objects
    for (list<StaticObject*>::iterator i = staticObjectList.begin(); i != staticObjectList.end(); ++ i)
    {
        objectList.push_back(*i);
    }

    // Load dynamic scene objects
    for (list<DynamicObject*>::iterator i = dynamicObjectList.begin(); i != dynamicObjectList.end(); ++ i)
    {
        objectList.push_back(*i);
        outlineObjectList.push_back(*i);
    }

    // Object list is filled with static and dynamic scene objects

    camera.draw(&objectList, &outlineObjectList, &lightList);
}

void World::update(float time)
{
    for (list<DynamicObject*>::iterator i = dynamicObjectList.begin(); i != dynamicObjectList.end(); ++ i)
    {
        (*i)->update(time);
    }

    camera.update(time);
}

void World::addDynamicObject(DynamicObject *o)
{
    o->init(&pathfinder);
    dynamicObjectList.push_back(o);
}

void World::addStaticObject(StaticObject *o)
{
    o->init();
    staticObjectList.push_back(o);
    pathfinder.addStaticObject(o);
}

void World::addLight(Light *o)
{
    lightList.push_back(o);
}

void World::setFocus(Object *o)
{
    camera.setFocus(o);
}

void World::updateMousePosition(float mouseScreenX, float mouseScreenY)
{
    // Apply transformation
    mouseY = (mouseScreenY * 2.f - mouseScreenX) / 2.f;
    mouseX = mouseScreenX + mouseY;

    // Scale
    mouseY *= 2.f;
    mouseX *= 2.f;

    // Add camera offset
    mouseX += camera.getX();
    mouseY += camera.getZ();

    /*
    std::cout << "Mouse location: mouseScreenX=" << mouseScreenX << " mouseScreenY=" << mouseScreenY << std::endl;
    std::cout << "Mouse location: mouseX=" << mouseX << " mouseY=" << mouseY << std::endl;
    std::cout << "Camera offset location: cameraX=" << camera.getX() << " cameraZ=" << camera.getZ() << std::endl;
    */

}

void World::dispatch(unsigned const int type)
{
    for (list<DynamicObject*>::iterator i = dynamicObjectList.begin(); i != dynamicObjectList.end(); ++ i)
    {
        (*i)->onNotify(type);
    }
}

void World::setHeightMap(int *heightMap) {
    this->heightMap = heightMap;
}

int* World::getHeightMap() {
    return heightMap;
}
