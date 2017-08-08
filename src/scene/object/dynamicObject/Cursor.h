#ifndef CURSOR_H
#define CURSOR_H

#include "../DynamicObject.h"
#include "../../World.h"

#include <iostream>

class Cursor : public DynamicObject
{
public:

    Cursor(World *W);

    virtual void draw();
    virtual void update(float time);
    virtual void onNotify(unsigned const int type);
    virtual void drawOutline();

protected:
    Vector3 rotation;
    Vector3 anchor;

private:

    void onMouseLeftDown();

};

#endif // CURSOR_H
