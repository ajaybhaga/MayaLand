#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "../DynamicObject.h"
#include "../../World.h"

#include <iostream>

class Player : public DynamicObject
{
    public:

        Player(World *W);

        virtual void draw();
        virtual void update(float time);
        virtual void onNotify(unsigned const int type);
        virtual void drawOutline();

    protected:
        Vector3 rotation;

    private:
        void onMouseLeftDown();       
};

#endif

