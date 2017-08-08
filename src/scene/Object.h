#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "Light.h"
#include "../graphics/Polygon.h"
#include "../graphics/Point.h"
#include "../math/Vector3.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class World;

class Object
{
    public:

        Object(World *W, float h, bool s);

        virtual void init();
        virtual void draw();
        virtual void drawOutline();

        void setDynamicGenerate();
        void generateColour();
        void setSize(float s);
        void setPoints(Vector3 v1, Vector3 v2);
        void setPosition(float x, float y, float z);
        void updateShadows(Light *l);
        void drawShadow(Light *l);

        bool shadowEnabled();

        float getX();
        float getY();
        float getZ();
        float getHeight();
        float getSize();       

        float getR();
        float getG();
        float getB();

    protected:

        World *world;

        Vector3 position;

        float height;
        float size;

        Point p1, p2, p3, p4, p5, p6, p7, p8;

        Polygon shape;

        bool shadow;
        bool dynamicGenerate;
        float r, g, b; // Object colour

    private:


};

#endif

