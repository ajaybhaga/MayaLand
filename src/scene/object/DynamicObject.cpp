#include "DynamicObject.h"

using namespace std;

DynamicObject::DynamicObject(World *W, float h, bool s) : Object(W, h, s)
{
    canMove = false;
}

void DynamicObject::init(Pathfinder *p)
{
    pathfinder = p;
}

void DynamicObject::update(float time)
{
}

void DynamicObject::remove()
{
}

void DynamicObject::onNotify(unsigned const int type)
{
}

void DynamicObject::move(float time)
{
    if (canMove == true)
    {
        Vector3 _position = Vector3(position.x, 0.0, position.z);
        Vector3 _destination = Vector3(destination.x, 0.0, destination.z);

        if (Vector3Util::dist(_position, _destination) > 5.f)
        {
            position += direction * speed * time;
        }
        else if (path.size() > 0)
        {
            setDestination(path.back());
            path.pop_back();
        }
        else
        {
            canMove = false;
        }
    }

    drawPath();
}

void DynamicObject::resetDestination()
{
    destination = position;
}

void DynamicObject::setDestination(Vector3 *d)
{
    destination = *d;
    direction = destination - position;
    Vector3Util::Normalize(direction);
    canMove = true;
}

void DynamicObject::setPath(float x, float z)
{
    resetDestination();
    path = pathfinder->getPath(position.x, position.z, x, z, getSize());
    canMove = true;

    lastPath = path;
    std::cout << "SET PATH size=" << path.size() << std::endl;
}

void DynamicObject::drawPath()
{
    std::cout << "DRAW PATH size=" << path.size() << std::endl;
    for (std::vector<Vector3*>::iterator i = path.begin(); i != path.end(); ++ i)
    {
        Vector3* v = (*i);
        std::cout << "v->x=" << v->x << " v->y=" << v->x << " v->z=" << v->x << std::endl;
        //std::vector<Vector3*> path;
    }
}


bool DynamicObject::isCanMove()
{
    return canMove;
}

