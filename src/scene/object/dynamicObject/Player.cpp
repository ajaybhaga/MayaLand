#include "Player.h"

using namespace std;

Player::Player(World *W) : DynamicObject(W, 30.f, true)
{
    speed = 200.f;

    Object::setDynamicGenerate();

    position.x = 512.f;
    position.z = 512.f;
    setSize(64.f);
}

void Player::onNotify(unsigned const int type)
{
    if (type == World::ON_MOUSE_LEFT_DOWN)
    {
        setPath(world->mouseX, world->mouseY);
    }
}

void Player::draw()
{    
    glColor4f(Object::getR(), Object::getG(), Object::getB(), 1.f);

    Object::draw();
}

void Player::update(float time)
{
    move(time);
}
