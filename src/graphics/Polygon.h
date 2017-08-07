#ifndef DEF_POLYGON
#define DEF_POLYGON

#include "Point.h"
#include "Triangle.h"
#include "../math/Vector3.h"

#include "../math/Vector3.h"
#include "../resources/Conf.h"

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class Polygon
{
    public:

        Polygon();

        void draw();
        void drawOutline();
        void drawShadow(Vector3 lightPosition);
        void addTriangle(Point *p1, Point *p2, Point *p3);
        std::vector<Triangle> getTriangles();
        void clear();
        void updateConnectivity();
        void updateShadows(Vector3 lightPosition);


    protected:

        std::vector<Triangle> triangles; // rename to shapeVolume
        std::vector<Point*> silhouette;
};

#endif

