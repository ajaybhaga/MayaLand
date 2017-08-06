#include "Tile.h"

Tile::Tile(World *W, float x, float y, float z, float h) : StaticObject(W, h, (h == 0.f), true)
{
    position.x = x;
    position.y = y;
    position.z = z;

    setSize(Conf::TILE_SIZE);
}

void Tile::draw()
{
    if (getHeight() == 0)
    {
        glColor4f(0.9f, 0.9f, 0.9f, 1.f);
    }
    else
    {
        //glColor4f(0.4f, 0.4f, 0.4f, 1.f);
        glColor4f(Object::getR(), Object::getG(), Object::getB(), 1.f);
    }

    Object::draw();
}

void Tile::generateColour() {
    int n;
    // Generate colour
    n = rand () % 10;
    r = n * 0.1f;
    n = rand () % 10;
    g = n * 0.1f;
    n = rand () % 10;
    b = n * 0.1f;
}
