#include "Cursor.h"

using namespace std;

Cursor::Cursor(World *W) : DynamicObject(W, 10.f, true)
{
    speed = 200.f;

    position.x = 512.f;
    position.z = 512.f;

    setSize(64.f);
}

void Cursor::onNotify(unsigned const int type)
{
    if (type == World::ON_MOUSE_LEFT_DOWN)
    {
     //   setPath(world->mouseX, world->mouseY);
    }
}

void Cursor::draw()
{
    glColor4f(1.f, 0.8f, 0.f, 1.f);

    Object::draw();
}

void Cursor::update(float time)
{
    move(time);
}
