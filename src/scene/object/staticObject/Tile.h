#ifndef DEF_TILE
#define DEF_TILE

#include "../StaticObject.h"
#include "../../World.h"
#include "../../../resources/Conf.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class Tile : public StaticObject
{
    public:

        Tile(World *W, float x, float y, float z, float h);

        virtual void draw();
        virtual void generateColour();

    private:
        float r, g, b; // Object colour
};

#endif

