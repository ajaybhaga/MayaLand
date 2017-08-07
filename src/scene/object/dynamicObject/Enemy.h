#ifndef DEF_ENEMY
#define DEF_ENEMY

#include "../DynamicObject.h"
#include "../../World.h"

#include <iostream>

class Enemy : public DynamicObject
{
    public:

        Enemy(World *W);

        virtual void draw();
        virtual void update(float time);
        virtual void drawOutline();
};
#endif

